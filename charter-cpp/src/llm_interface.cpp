#include "charter/llm_interface.h"
#include <algorithm>
#include <chrono>

namespace charter {

// ---------------------------------------------------------------------------
// MockLLMInterface — deterministic stubs for skeleton / unit testing
// ---------------------------------------------------------------------------

StructuredArtifact MockLLMInterface::structure_claim(const std::string& raw_claim) {
    StructuredArtifact a;
    a.id = "artifact-mock-01";
    a.central_claim = raw_claim;
    a.operational_definitions.push_back({ "effect", "measured_output", "30 days" });
    a.test_specification = { "A/B conditions", "n=100", "stop at 30 days or p<0.05" };
    a.success_criteria = {
        { "sc-1", 0.05, ThresholdDirection::LESS_THAN, 0.0, "p-value threshold" },
        { "sc-2", 0.20, ThresholdDirection::GREATER_THAN, 0.0, "minimum effect size" }
    };
    a.mechanism_status =
        "Mechanism unknown — artifact is phenomenological/predictive. "
        "Cold exposure hypothesized to reduce fatigue via ANS modulation, "
        "but causal pathway not established. "
        "Discriminating test (A/B conditions) proposed to distinguish ANS-mediated "
        "effect from placebo and regression to mean.";
    a.last_modified = std::chrono::system_clock::now();
    return a;
}

std::vector<Objection> MockLLMInterface::generate_objections(
    const StructuredArtifact& artifact,
    const ObjectionRegister& existing_objections)
{
    // Return one mock substantive objection if none of type FAILURE_MODE exist
    bool has_failure_mode = std::any_of(
        existing_objections.begin(), existing_objections.end(),
        [](const Objection& o) { return o.type == ObjectionType::FAILURE_MODE; });

    if (has_failure_mode) return {};

    Objection o;
    o.id = "obj-mock-01";
    o.claim_ref = artifact.id;
    o.text = "[mock] confounding variable not controlled — "
             "effect may be attributable to selection bias rather than treatment";
    o.type = ObjectionType::FAILURE_MODE;
    o.status = ObjectionStatus::OPEN;
    o.is_substantive = true;
    o.timestamp = std::chrono::system_clock::now();
    return { o };
}

std::vector<Hypothesis> MockLLMInterface::generate_competing_hypotheses(
    const StructuredArtifact& artifact,
    const std::vector<Hypothesis>& existing_hypotheses)
{
    if (existing_hypotheses.size() >= 2) return {};

    Hypothesis h;
    h.id = "H2";
    h.evidence_level = EvidenceLevel::E1;
    h.text = "[mock] null hypothesis: observed effect is due to regression to the mean";
    h.independent_variable = "time_since_enrollment";
    h.dependent_variable = artifact.success_criteria.empty()
        ? "measured_output"
        : artifact.success_criteria[0].description;
    h.differing_prediction = "effect diminishes over repeated measurements without intervention";
    return { h };
}

std::string MockLLMInterface::generate_watchdog_report(
    const std::vector<StructuredArtifact>& /*recent_artifacts*/,
    const ObjectionRegister& /*objections*/)
{
    return "[mock watchdog report] "
           "Three consecutive CONVERGEs observed. "
           "Recent claims appear to reinforce a single causal narrative without "
           "meaningful adversarial challenge. "
           "Competing hypothesis H2 not stress-tested against most recent artifact. "
           "Assessment: exhausted scrutiny cannot be confirmed — drift suspected.";
}

}  // namespace charter
