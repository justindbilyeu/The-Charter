#pragma once

#include "types.h"
#include "llm_interface.h"
#include <memory>
#include <vector>

namespace charter {

// ---------------------------------------------------------------------------
// Hard Gates (§2) — two-phase evaluation (v2.4)
//
// Phase 1: G1 + G2 (prerequisites)
//   G1 failure → RESTART immediately; G2–G5 not evaluated
//   G2 failure → RESTART immediately; G3–G5 not evaluated
//
// Phase 2: G3, G4, G5 (validators) — only if Phase 1 passes
//   G3 failure → DIVERSIFY
//   G4 failure → RESTART
//   G5 failure → DIVERSIFY
//
// G1 and G4 are mechanical. G2, G3, G5 delegate to ILLMInterface.
// ---------------------------------------------------------------------------

class MechanicalGates {
public:
    // G1: success_criteria must contain >= 2 numeric thresholds
    static GateEvaluation evaluate_g1(const StructuredArtifact& artifact);

    // G4: thresholds must not have changed since lock time
    // Locks thresholds on first call if not already locked.
    static GateEvaluation evaluate_g4(StructuredArtifact& artifact);
};

class HardGates {
public:
    explicit HardGates(std::shared_ptr<ILLMInterface> llm);

    // Full two-phase evaluation per v2.4 protocol.
    // Returns evaluations actually performed (Phase 1 short-circuits if either fails).
    std::vector<GateEvaluation> evaluate(StructuredArtifact& artifact);

    // Determine FSM routing from a completed evaluation set.
    // Returns the highest-priority failure route, or NONE if all pass.
    // Priority: RESTART > DIVERSIFY (per v2.4: G4 failure → RESTART even after G3/G5 → DIVERSIFY)
    static State route(const std::vector<GateEvaluation>& results);

private:
    std::shared_ptr<ILLMInterface> llm_;
};

}  // namespace charter
