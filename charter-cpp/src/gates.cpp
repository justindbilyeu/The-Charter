#include "charter/gates.h"

namespace charter {

// G1: >= 2 numeric thresholds in success_criteria — fully mechanical
GateEvaluation MechanicalGates::evaluate_g1(const StructuredArtifact& artifact) {
    if (artifact.success_criteria.size() >= 2) {
        return { GateId::G1, GateStatus::PASS, "", FailureRoute::NONE };
    }
    return {
        GateId::G1, GateStatus::FAIL,
        "G1: success_criteria contains " +
            std::to_string(artifact.success_criteria.size()) +
            " threshold(s); >= 2 required",
        FailureRoute::RESTART  // G1 is a prerequisite — failure → RESTART
    };
}

// G4: thresholds must not have changed since lock time — fully mechanical
GateEvaluation MechanicalGates::evaluate_g4(StructuredArtifact& artifact) {
    if (!artifact.thresholds_locked) {
        // First evaluation — lock current thresholds
        for (const auto& c : artifact.success_criteria)
            artifact.locked_thresholds[c.id] = c.threshold;
        artifact.thresholds_locked = true;
        return { GateId::G4, GateStatus::PASS, "", FailureRoute::NONE };
    }

    // Subsequent evaluation — check for post-lock modifications
    for (const auto& c : artifact.success_criteria) {
        auto it = artifact.locked_thresholds.find(c.id);
        if (it == artifact.locked_thresholds.end()) {
            return {
                GateId::G4, GateStatus::FAIL,
                "G4: new threshold '" + c.id + "' added after lock — thresholds cannot be adjusted after results observed. Ever.",
                FailureRoute::RESTART
            };
        }
        if (it->second != c.threshold) {
            return {
                GateId::G4, GateStatus::FAIL,
                "G4: threshold '" + c.id + "' changed from " +
                    std::to_string(it->second) + " to " +
                    std::to_string(c.threshold) + " after lock",
                FailureRoute::RESTART
            };
        }
    }
    return { GateId::G4, GateStatus::PASS, "", FailureRoute::NONE };
}

// ---------------------------------------------------------------------------
// HardGates — two-phase evaluation (v2.4)
// ---------------------------------------------------------------------------

HardGates::HardGates(std::shared_ptr<ILLMInterface> llm)
    : llm_(std::move(llm)) {}

std::vector<GateEvaluation> HardGates::evaluate(StructuredArtifact& artifact) {
    std::vector<GateEvaluation> results;

    // Phase 1: Prerequisites (G1 + G2)
    auto g1 = MechanicalGates::evaluate_g1(artifact);
    results.push_back(g1);
    artifact.gate_status[GateId::G1] = g1.status;
    if (g1.status == GateStatus::FAIL) return results;  // short-circuit

    auto g2 = llm_->evaluate_g2(artifact);
    results.push_back(g2);
    artifact.gate_status[GateId::G2] = g2.status;
    if (g2.status == GateStatus::FAIL) return results;  // short-circuit

    // Phase 2: Validators (G3, G4, G5)
    auto g3 = llm_->evaluate_g3(artifact);
    results.push_back(g3);
    artifact.gate_status[GateId::G3] = g3.status;

    auto g4 = MechanicalGates::evaluate_g4(artifact);
    results.push_back(g4);
    artifact.gate_status[GateId::G4] = g4.status;

    auto g5 = llm_->evaluate_g5(artifact);
    results.push_back(g5);
    artifact.gate_status[GateId::G5] = g5.status;

    artifact.last_gate_evaluation = std::chrono::system_clock::now();
    return results;
}

State HardGates::route(const std::vector<GateEvaluation>& results) {
    // G4 failure → RESTART takes priority over G3/G5 → DIVERSIFY
    bool any_restart = false;
    bool any_diversify = false;

    for (const auto& r : results) {
        if (r.status == GateStatus::FAIL) {
            if (r.route == FailureRoute::RESTART) any_restart = true;
            if (r.route == FailureRoute::DIVERSIFY) any_diversify = true;
        }
    }

    if (any_restart)   return State::RESTART;
    if (any_diversify) return State::DIVERSIFY;
    return State::CONVERGE;
}

}  // namespace charter
