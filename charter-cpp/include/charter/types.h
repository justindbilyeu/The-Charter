#pragma once

#include <chrono>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace charter {

// ---------------------------------------------------------------------------
// FSM States (§3)
// ---------------------------------------------------------------------------

enum class State {
    INIT,
    STRUCTURING,
    GATE_CHECK,
    DIVERSIFY,
    CONVERGE,
    RESTART,
    OUTPUT
};

const char* to_string(State s);

// ---------------------------------------------------------------------------
// Hard Gates (§2)
// ---------------------------------------------------------------------------

enum class GateId { G1, G2, G3, G4, G5 };

enum class GateStatus { PENDING, PASS, FAIL };

// Routing consequence of a gate failure (v2.4 two-phase protocol)
enum class FailureRoute { NONE, DIVERSIFY, RESTART };

struct GateEvaluation {
    GateId gate;
    GateStatus status;
    std::string defect;       // empty if PASS
    FailureRoute route;       // meaningful only when status == FAIL
};

// Which gates are mechanical vs. require LLM semantic judgment
// G1: mechanical (count thresholds)
// G2: LLM (scope judgment)
// G3: LLM (operational definition check)
// G4: mechanical (immutability enforcement)
// G5: LLM (mechanism status check)
constexpr bool is_mechanical(GateId g) {
    return g == GateId::G1 || g == GateId::G4;
}

// ---------------------------------------------------------------------------
// Evidence Hierarchy (§5)
// ---------------------------------------------------------------------------

enum class EvidenceLevel { E1, E2, E3, E4, E5 };

// v2.7: E2 requires independent locatability + corroboration for foundational use
struct Citation {
    std::string title;
    std::string author;
    std::string access_path;  // URL, DOI, ISBN — sufficient to retrieve without researcher context
};

// v2.7: foundational = removal requires revising central claim, op-defs, or success criteria
enum class ClaimRole { FOUNDATIONAL, ORIENTATIONAL };

struct EvidenceLevelAssignment {
    std::string claim_ref;
    EvidenceLevel level;
    std::string rationale;
    std::vector<Citation> sources;
    ClaimRole role = ClaimRole::ORIENTATIONAL;

    // v2.7 E2 corroboration check: foundational E2 requires >= 2 sources
    bool satisfies_e2_corroboration() const {
        if (level != EvidenceLevel::E2) return true;
        if (role == ClaimRole::ORIENTATIONAL) return sources.size() >= 1;
        return sources.size() >= 2;  // foundational requires two independent sources
    }
};

// ---------------------------------------------------------------------------
// Structuring Contract (§1)
// ---------------------------------------------------------------------------

struct OperationalDefinition {
    std::string term;
    std::string metric;
    std::string measurement_window;
};

struct TestSpecification {
    std::string conditions;
    std::string parameters;
    std::string stopping_rules;
};

enum class ThresholdDirection { GREATER_THAN, LESS_THAN, BETWEEN };

struct SuccessCriterion {
    std::string id;           // stable key for G4 tracking
    double threshold;
    ThresholdDirection direction;
    double upper_threshold = 0.0;  // only meaningful for BETWEEN
    std::string description;
};

struct StructuredArtifact {
    std::string id;
    std::string central_claim;  // ≤3 sentences, bounded, falsifiable
    std::vector<OperationalDefinition> operational_definitions;
    TestSpecification test_specification;
    std::vector<SuccessCriterion> success_criteria;
    std::vector<EvidenceLevelAssignment> evidence;

    // Gate tracking
    std::map<GateId, GateStatus> gate_status;

    // G4 enforcement: thresholds are locked once test execution begins
    bool thresholds_locked = false;
    std::map<std::string, double> locked_thresholds;  // criterion_id -> threshold at lock time

    // G5 structural field: must be non-empty for G5 LLM evaluation to proceed.
    // Either state the proposed mechanism and distinguish it from evidence,
    // or declare mechanism unknown and identify artifact as phenomenological/
    // predictive/exploratory (charter §2 G5 — two pass conditions).
    // Empty → immediate G5 FAIL without LLM call.
    std::string mechanism_status;

    // v2.6 Structural DIVERSIFY Trigger 3: track when the artifact was last modified
    // and when gates were last formally evaluated
    std::chrono::system_clock::time_point last_modified;
    std::chrono::system_clock::time_point last_gate_evaluation;

    bool all_gates_pass() const;
    bool any_gate_pending() const;
};

// ---------------------------------------------------------------------------
// Productive Skepticism Protocol (§4)
// ---------------------------------------------------------------------------

enum class ObjectionStatus { OPEN, TESTED, UNTESTABLE };
enum class ObjectionType { CONVERGENCE, ASSUMPTION, FAILURE_MODE, SCOPE, MECHANISM };

struct Objection {
    std::string id;
    std::string claim_ref;
    std::string text;
    ObjectionType type;
    ObjectionStatus status = ObjectionStatus::OPEN;
    std::optional<std::string> test_result;
    std::optional<std::string> untestable_reasoning;
    std::chrono::system_clock::time_point timestamp;

    // v2.5: must meet §4 Calibration Rule (specific, testable, non-redundant, gate-tied)
    bool is_substantive = false;
};

using ObjectionRegister = std::vector<Objection>;

bool has_open_objections(const ObjectionRegister& reg);
int open_objection_count(const ObjectionRegister& reg);

// ---------------------------------------------------------------------------
// Hypothesis tracking (§3 Structural DIVERSIFY Trigger 1)
// ---------------------------------------------------------------------------

struct Hypothesis {
    std::string id;              // e.g., "H1", "H2" — distinct alphanumeric
    EvidenceLevel evidence_level;
    std::string text;
    std::string independent_variable;   // discriminating test: named IV
    std::string dependent_variable;     // discriminating test: named DV
    std::string differing_prediction;   // v2.5: at least one prediction differing from primary claim
};

// ---------------------------------------------------------------------------
// Coherence Controller monitoring (§3, v2.3/v2.4)
// ---------------------------------------------------------------------------

struct ConstraintHealth {
    bool gates_evaluated_and_passed;
    int open_objection_count;
    int consecutive_converge_count;
};

enum class DriftAssessment { NOT_ASSESSED, EXHAUSTED_SCRUTINY, DRIFT_SUSPECTED };

struct AdversarialAnchor {
    bool watchdog_fired = false;
    DriftAssessment assessment = DriftAssessment::NOT_ASSESSED;
    std::optional<std::string> watchdog_report;
};

// ---------------------------------------------------------------------------
// Session Continuity (§9)
// ---------------------------------------------------------------------------

// v2.5: structural fields are required; orientational fields are recommended
// Missing structural field → invalid handoff, operator must act
// Missing orientational field → declare and proceed
//
// Structural fields use std::optional<T> so that "missing" (nullopt) is
// unambiguous — an empty vector or zero-valued struct is a valid present state.
struct StateCompression {
    // Structural (required) — nullopt = missing, not present; triggers invalid handoff
    std::optional<std::vector<std::pair<std::string, GateStatus>>> gate_status;
    std::optional<ObjectionRegister> objection_register;
    std::optional<ConstraintHealth> constraint_health;
    std::optional<AdversarialAnchor> adversarial_anchor;

    // Orientational (recommended)
    std::string charter_version = "v2.7";
    std::string session_id;
    std::chrono::system_clock::time_point timestamp;
    std::vector<EvidenceLevelAssignment> active_claims;
    std::vector<std::pair<std::string, std::string>> decisions;  // {decision, reasoning}
    std::string next_step;
    std::vector<std::string> assumptions_modified;

    // Validity: all structural fields present and non-empty
    bool is_valid() const;
    std::vector<std::string> missing_structural_fields() const;
};

// ---------------------------------------------------------------------------
// DIVERSIFY Exit Token (v2.5 exit criterion — K1 token pattern)
//
// Only CoherenceController can construct this token. A caller cannot
// fabricate one — the private constructor enforces that check_diversify_complete()
// is the sole token source. Move-only: token is consumed on use, preventing replay.
// ---------------------------------------------------------------------------

class DiversifyExitToken {
    friend class CoherenceController;
public:
    DiversifyExitToken(const DiversifyExitToken&) = delete;
    DiversifyExitToken& operator=(const DiversifyExitToken&) = delete;
    DiversifyExitToken(DiversifyExitToken&&) = default;
    DiversifyExitToken& operator=(DiversifyExitToken&&) = default;

    bool is_valid() const { return unmet_.empty(); }
    const std::vector<std::string>& unmet_criteria() const { return unmet_; }

private:
    explicit DiversifyExitToken(std::vector<std::string> unmet)
        : unmet_(std::move(unmet)) {}
    std::vector<std::string> unmet_;
};

}  // namespace charter
