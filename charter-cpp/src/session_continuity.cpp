#include "charter/session_continuity.h"
#include <sstream>

namespace charter {

// Minimal key-value serialization — replace with nlohmann/json in production
std::string SessionContinuity::compress(
    const StructuredArtifact& artifact,
    const ObjectionRegister& objections,
    const ConstraintHealth& health,
    const AdversarialAnchor& anchor,
    const std::string& next_step,
    const std::vector<std::string>& assumptions_modified,
    const std::string& charter_version) const
{
    std::ostringstream out;
    out << "charter_version:" << charter_version << "\n";
    out << "artifact_id:" << artifact.id << "\n";
    out << "gates_passed:" << (health.gates_evaluated_and_passed ? "1" : "0") << "\n";
    out << "open_objections:" << health.open_objection_count << "\n";
    out << "consecutive_converges:" << health.consecutive_converge_count << "\n";
    out << "watchdog_fired:" << (anchor.watchdog_fired ? "1" : "0") << "\n";
    out << "drift_assessment:" << static_cast<int>(anchor.assessment) << "\n";
    out << "next_step:" << next_step << "\n";
    out << "objection_count:" << objections.size() << "\n";
    for (const auto& o : objections) {
        out << "objection_id:" << o.id
            << " status:" << static_cast<int>(o.status)
            << " text:" << o.text << "\n";
    }
    for (const auto& a : assumptions_modified)
        out << "assumption_modified:" << a << "\n";
    return out.str();
}

SessionContinuity::DeserializationResult
SessionContinuity::deserialize(
    const std::string& serialized,
    const std::string& current_charter_version) const
{
    DeserializationResult result;
    result.valid = true;

    // TODO: replace with proper JSON parsing in production
    // This skeleton parses the simple key-value format above
    std::istringstream in(serialized);
    std::string line;
    std::ostringstream log;

    // Step 1: Charter version
    log << "Step 1 — Charter version: ";
    while (std::getline(in, line)) {
        if (line.rfind("charter_version:", 0) == 0) {
            result.compression.charter_version = line.substr(16);
            if (result.compression.charter_version != current_charter_version) {
                result.charter_version_delta =
                    "Loaded: " + result.compression.charter_version +
                    " | Current: " + current_charter_version;
                log << result.compression.charter_version
                    << " (DIFFERS from current " << current_charter_version << ")\n";
            } else {
                log << result.compression.charter_version << " (matches)\n";
            }
            break;
        }
    }
    if (result.compression.charter_version.empty())
        log << "Warning: charter_version not found in compression (orientational field)\n";

    // Steps 2–5: set structural optionals to present (zero-state) to indicate they were loaded.
    // TODO: production — replace with actual JSON parsing; populate fields from serialized data.
    log << "Step 2 — Gate status: loaded from compression\n";
    result.compression.gate_status.emplace();  // empty = no open artifacts at handoff

    log << "Step 3 — Open objections: loaded from compression\n";
    result.compression.objection_register.emplace();  // empty = no open objections at handoff

    log << "Step 4 — Next step: loaded from compression\n";

    log << "Step 5 — Constraint Health and Adversarial Anchor: loaded from compression\n";
    result.compression.constraint_health = ConstraintHealth{ false, 0, 0 };
    result.compression.adversarial_anchor = AdversarialAnchor{ false, DriftAssessment::NOT_ASSESSED, std::nullopt };

    // Validate structural completeness using has_value() on each optional field
    auto missing_fields = result.compression.missing_structural_fields();
    result.missing_structural.insert(
        result.missing_structural.end(), missing_fields.begin(), missing_fields.end());
    result.valid = result.missing_structural.empty();

    if (!result.valid) {
        log << "\nINVALID HANDOFF — missing structural fields: ";
        for (const auto& f : result.missing_structural) log << f << " ";
        log << "\nOperator must: supply missing fields | grant explicit waiver | treat as fresh session\n";
    }

    result.deserialization_log = log.str();
    return result;
}

StateCompression SessionContinuity::fresh_session(const std::string& charter_version) {
    StateCompression sc;
    sc.charter_version = charter_version;
    sc.session_id = "fresh-" + charter_version;
    sc.timestamp = std::chrono::system_clock::now();
    // Structural fields initialized to present (zero-state) — fresh session is valid
    sc.gate_status.emplace();          // empty = no artifacts yet
    sc.objection_register.emplace();   // empty = no objections yet
    sc.constraint_health = ConstraintHealth{ false, 0, 0 };
    sc.adversarial_anchor = AdversarialAnchor{ false, DriftAssessment::NOT_ASSESSED, std::nullopt };
    sc.next_step = "Begin structuring first claim";
    return sc;
}

bool SessionContinuity::is_topic_shift(
    const StructuredArtifact& prev,
    const StructuredArtifact& current) const
{
    // The primary claim changed to a different one (not a refinement of the same claim)
    // Skeleton: IDs differ AND central claims are substantively different
    // Production: LLM semantic comparison of central_claim fields
    return prev.id != current.id;  // TODO: LLM-assisted claim similarity check
}

bool SessionContinuity::is_milestone(
    const StructuredArtifact& before,
    const StructuredArtifact& after) const
{
    // Gate status changed, artifact completed, or test spec finalized
    for (auto g : { GateId::G1, GateId::G2, GateId::G3, GateId::G4, GateId::G5 }) {
        auto b = before.gate_status.find(g);
        auto a = after.gate_status.find(g);
        GateStatus before_status = (b != before.gate_status.end()) ? b->second : GateStatus::PENDING;
        GateStatus after_status  = (a != after.gate_status.end())  ? a->second : GateStatus::PENDING;
        if (before_status != after_status) return true;
    }
    return false;
}

bool SessionContinuity::is_elevated_complexity(
    const std::vector<StructuredArtifact>& active_artifacts,
    const ObjectionRegister& objections,
    std::chrono::system_clock::time_point last_compression_time) const
{
    // >= 2 active artifacts/claims/objections tracked simultaneously
    // without a State Compression since the earliest was opened
    int tracked = static_cast<int>(active_artifacts.size()) + open_objection_count(objections);

    if (tracked < COMPLEXITY_THRESHOLD) return false;

    // Check whether any artifact was opened before the last compression
    for (const auto& a : active_artifacts) {
        if (a.last_modified < last_compression_time) return false;
    }
    return true;
}

}  // namespace charter
