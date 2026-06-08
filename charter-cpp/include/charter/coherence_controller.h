#pragma once

#include "types.h"
#include "llm_interface.h"
#include <memory>
#include <string>
#include <vector>

namespace charter {

// ---------------------------------------------------------------------------
// Coherence Controller (§3)
//
// Evaluates monitoring conditions and decides CONVERGE / DIVERSIFY / RESTART.
// Also implements the Structural DIVERSIFY Triggers (v2.6) and the
// DIVERSIFY exit criterion (v2.5).
// ---------------------------------------------------------------------------

class CoherenceController {
public:
    explicit CoherenceController(std::shared_ptr<ILLMInterface> llm);

    // Evaluate the three monitoring conditions (v2.3/v2.4)
    ConstraintHealth evaluate_health(
        const StructuredArtifact& artifact,
        const ObjectionRegister& objections,
        int consecutive_converge_count) const;

    // ---------------------------------------------------------------------------
    // Structural DIVERSIFY Triggers (v2.6)
    // Any one of the three conditions mandates DIVERSIFY; CONVERGE not available.
    // ---------------------------------------------------------------------------

    struct TriggerResult {
        bool triggered;
        int condition;      // 1, 2, or 3 — first violated condition; 0 if none
        std::string reason; // human-readable explanation for session log
    };

    // Condition 1: Hypothesis Under-Specification
    // Fewer than 2 competing hypotheses with ID + evidence level + IV + DV
    // Condition 1 is partly mechanical (count, structure check) but "genuinely distinct
    // prediction" requires LLM judgment — currently checked structurally only.
    TriggerResult check_hypothesis_under_specification(
        const std::vector<Hypothesis>& hypotheses) const;

    // Condition 2: Asymmetric Risk Assessment
    // Claim advanced without objection register update OR without Failure Mode Probe entry
    // Fully mechanical: compare artifact.last_modified with objection timestamps.
    TriggerResult check_asymmetric_risk(
        const StructuredArtifact& artifact,
        const ObjectionRegister& objections) const;

    // Condition 3: Gate Omission
    // New content incorporated into artifact since last formal gate evaluation.
    // Mechanical: artifact.last_modified > artifact.last_gate_evaluation
    TriggerResult check_gate_omission(const StructuredArtifact& artifact) const;

    // Evaluate all three triggers. Returns the first triggered condition, or
    // TriggerResult{false, 0, ""} if none are met.
    TriggerResult check_all_structural_triggers(
        const StructuredArtifact& artifact,
        const ObjectionRegister& objections,
        const std::vector<Hypothesis>& hypotheses) const;

    // ---------------------------------------------------------------------------
    // CONVERGE decision
    // ---------------------------------------------------------------------------

    // CONVERGE is valid when: all gates pass, no OPEN objections,
    // at least one prior DIVERSIFY or RESTART in the session.
    // v2.5: "all gates" — no "applicable" exemption.
    struct ConvergeResult {
        bool allowed;
        std::string reason;  // why not allowed, if !allowed
    };
    ConvergeResult can_converge(
        const ConstraintHealth& health,
        bool had_prior_diversify_or_restart) const;

    // ---------------------------------------------------------------------------
    // DIVERSIFY exit criterion (v2.5 — three-part completion condition)
    // ---------------------------------------------------------------------------

    struct DiversifyCompletionResult {
        bool complete;
        std::vector<std::string> unmet;  // which of (a), (b), (c) remain unmet
    };

    // (a) >= 1 new competing hypothesis with differing prediction
    // (b) >= 1 new substantive objection logged since DIVERSIFY entry
    // (c) artifact revised or written justification provided
    DiversifyCompletionResult check_diversify_complete(
        const std::vector<Hypothesis>& hypotheses_before,
        const std::vector<Hypothesis>& hypotheses_now,
        const ObjectionRegister& objections_before,
        const ObjectionRegister& objections_now,
        bool artifact_revised_or_justified) const;

private:
    std::shared_ptr<ILLMInterface> llm_;
};

}  // namespace charter
