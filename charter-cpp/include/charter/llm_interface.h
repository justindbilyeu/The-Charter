#pragma once

#include "types.h"
#include <memory>

namespace charter {

// ---------------------------------------------------------------------------
// Abstract LLM interface
//
// This is the seam between mechanical enforcement (C++) and semantic judgment
// (LLM). C++ owns transitions, routing, and structural invariants. The LLM
// owns evaluation of meaning: is this claim bounded? are key terms defined?
// is mechanism status declared? what are competing hypotheses?
//
// Production: implement with Anthropic API (claude-sonnet-4-6 or later).
// Testing:    use MockLLMInterface below.
// ---------------------------------------------------------------------------

class ILLMInterface {
public:
    // Semantic gate evaluation (G2, G3, G5 — G1 and G4 are mechanical)
    virtual GateEvaluation evaluate_g2(const StructuredArtifact& artifact) = 0;
    virtual GateEvaluation evaluate_g3(const StructuredArtifact& artifact) = 0;
    virtual GateEvaluation evaluate_g5(const StructuredArtifact& artifact) = 0;

    // Structuring: translate raw claim into structured artifact (§1)
    virtual StructuredArtifact structure_claim(const std::string& raw_claim) = 0;

    // PSP: generate substantive objections meeting §4 Calibration Rule
    // Must not duplicate objections already in the register
    virtual std::vector<Objection> generate_objections(
        const StructuredArtifact& artifact,
        const ObjectionRegister& existing_objections) = 0;

    // PSP: generate competing hypotheses with distinct predictions
    // Each must include named IV + DV + differing prediction (§3 Trigger 1 + v2.5 exit condition)
    virtual std::vector<Hypothesis> generate_competing_hypotheses(
        const StructuredArtifact& artifact,
        const std::vector<Hypothesis>& existing_hypotheses) = 0;

    // Convergence Watchdog (§3 v2.4): generate report after 3 consecutive CONVERGEs
    // Report must include: 3 recent claims + objections; 1 new competing hypothesis
    // + discriminating test; drift vs. exhausted-scrutiny assessment
    virtual std::string generate_watchdog_report(
        const std::vector<StructuredArtifact>& recent_artifacts,
        const ObjectionRegister& objections) = 0;

    virtual DriftAssessment assess_drift(const std::string& watchdog_report) = 0;

    virtual ~ILLMInterface() = default;
};

// ---------------------------------------------------------------------------
// Mock implementation — deterministic stubs for skeleton / unit testing
// ---------------------------------------------------------------------------

class MockLLMInterface : public ILLMInterface {
public:
    // Configurable pass/fail per gate for testing
    bool g2_passes = true;
    bool g3_passes = true;
    bool g5_passes = true;
    DriftAssessment mock_drift = DriftAssessment::EXHAUSTED_SCRUTINY;

    GateEvaluation evaluate_g2(const StructuredArtifact&) override {
        return { GateId::G2,
                 g2_passes ? GateStatus::PASS : GateStatus::FAIL,
                 g2_passes ? "" : "[mock] claim scope too broad",
                 g2_passes ? FailureRoute::NONE : FailureRoute::DIVERSIFY };
    }

    GateEvaluation evaluate_g3(const StructuredArtifact&) override {
        return { GateId::G3,
                 g3_passes ? GateStatus::PASS : GateStatus::FAIL,
                 g3_passes ? "" : "[mock] key term lacks operational definition",
                 g3_passes ? FailureRoute::NONE : FailureRoute::DIVERSIFY };
    }

    GateEvaluation evaluate_g5(const StructuredArtifact&) override {
        return { GateId::G5,
                 g5_passes ? GateStatus::PASS : GateStatus::FAIL,
                 g5_passes ? "" : "[mock] mechanism status not declared",
                 g5_passes ? FailureRoute::NONE : FailureRoute::DIVERSIFY };
    }

    StructuredArtifact structure_claim(const std::string& raw_claim) override;

    std::vector<Objection> generate_objections(
        const StructuredArtifact& artifact,
        const ObjectionRegister& existing_objections) override;

    std::vector<Hypothesis> generate_competing_hypotheses(
        const StructuredArtifact& artifact,
        const std::vector<Hypothesis>& existing_hypotheses) override;

    std::string generate_watchdog_report(
        const std::vector<StructuredArtifact>& recent_artifacts,
        const ObjectionRegister& objections) override;

    DriftAssessment assess_drift(const std::string&) override {
        return mock_drift;
    }
};

}  // namespace charter
