#include "charter/coherence_controller.h"
#include <algorithm>

namespace charter {

CoherenceController::CoherenceController(std::shared_ptr<ILLMInterface> llm)
    : llm_(std::move(llm)) {}

ConstraintHealth CoherenceController::evaluate_health(
    const StructuredArtifact& artifact,
    const ObjectionRegister& objections,
    int consecutive_converge_count) const
{
    return {
        artifact.all_gates_pass(),
        open_objection_count(objections),
        consecutive_converge_count
    };
}

// Condition 1: Hypothesis Under-Specification
// Structural check: count hypotheses with all required fields present.
// NOTE: whether predictions are "genuinely distinct" is a semantic question
// deferred to LLM — the skeleton checks structure only.
CoherenceController::TriggerResult
CoherenceController::check_hypothesis_under_specification(
    const std::vector<Hypothesis>& hypotheses) const
{
    int well_formed = 0;
    for (const auto& h : hypotheses) {
        bool has_id = !h.id.empty();
        bool has_level = true;  // enum always has a value
        bool has_iv = !h.independent_variable.empty();
        bool has_dv = !h.dependent_variable.empty();
        bool has_prediction = !h.differing_prediction.empty();  // v2.5 structural requirement
        if (has_id && has_level && has_iv && has_dv && has_prediction) ++well_formed;
    }

    if (well_formed < 2) {
        return {
            true, 1,
            "Hypothesis Under-Specification: " + std::to_string(well_formed) +
                " well-formed competing hypothesis/hypotheses; >= 2 required "
                "(each needs distinct ID, evidence level, named IV, named DV, and differing prediction)"
        };
    }
    return { false, 0, "" };
}

// Condition 2: Asymmetric Risk Assessment
// Mechanical: check that at least one objection was added after the artifact's
// last modification, AND that a Failure Mode Probe-type objection exists.
CoherenceController::TriggerResult
CoherenceController::check_asymmetric_risk(
    const StructuredArtifact& artifact,
    const ObjectionRegister& objections) const
{
    // Check for objection added after last artifact modification
    bool updated_since_modification = std::any_of(
        objections.begin(), objections.end(),
        [&](const Objection& o) {
            return o.timestamp >= artifact.last_modified;
        });

    bool has_failure_mode_probe = std::any_of(
        objections.begin(), objections.end(),
        [](const Objection& o) {
            return o.type == ObjectionType::FAILURE_MODE;
        });

    if (!updated_since_modification || !has_failure_mode_probe) {
        std::string reason = "Asymmetric Risk Assessment: ";
        if (!updated_since_modification)
            reason += "claim advanced without objection register update; ";
        if (!has_failure_mode_probe)
            reason += "no Failure Mode Probe (§4) entry on record";
        return { true, 2, reason };
    }
    return { false, 0, "" };
}

// Condition 3: Gate Omission
// Mechanical: artifact modified after last gate evaluation.
CoherenceController::TriggerResult
CoherenceController::check_gate_omission(const StructuredArtifact& artifact) const {
    // last_gate_evaluation is zero-initialized — if never evaluated, treat as omission
    if (artifact.last_modified > artifact.last_gate_evaluation) {
        return {
            true, 3,
            "Gate Omission: artifact modified since last formal gate evaluation "
            "(content incorporated into artifact without re-evaluation against G1–G5)"
        };
    }
    return { false, 0, "" };
}

CoherenceController::TriggerResult
CoherenceController::check_all_structural_triggers(
    const StructuredArtifact& artifact,
    const ObjectionRegister& objections,
    const std::vector<Hypothesis>& hypotheses) const
{
    auto r1 = check_hypothesis_under_specification(hypotheses);
    if (r1.triggered) return r1;

    auto r2 = check_asymmetric_risk(artifact, objections);
    if (r2.triggered) return r2;

    auto r3 = check_gate_omission(artifact);
    if (r3.triggered) return r3;

    return { false, 0, "" };
}

CoherenceController::ConvergeResult
CoherenceController::can_converge(
    const ConstraintHealth& health,
    bool had_prior_diversify_or_restart) const
{
    if (!health.gates_evaluated_and_passed)
        return { false, "not all gates have passed" };
    if (health.open_objection_count > 0)
        return { false, std::to_string(health.open_objection_count) + " open objection(s) remain" };
    if (!had_prior_diversify_or_restart)
        return { false, "session trajectory must include at least one prior DIVERSIFY or RESTART" };
    return { true, "" };
}

CoherenceController::DiversifyCompletionResult
CoherenceController::check_diversify_complete(
    const std::vector<Hypothesis>& hypotheses_before,
    const std::vector<Hypothesis>& hypotheses_now,
    const ObjectionRegister& objections_before,
    const ObjectionRegister& objections_now,
    bool artifact_revised_or_justified) const
{
    std::vector<std::string> unmet;

    // (a) >= 1 new well-formed hypothesis with a differing prediction
    int new_hypotheses = 0;
    for (const auto& h : hypotheses_now) {
        bool is_new = std::none_of(hypotheses_before.begin(), hypotheses_before.end(),
            [&](const Hypothesis& old) { return old.id == h.id; });
        bool has_prediction = !h.differing_prediction.empty();
        if (is_new && has_prediction) ++new_hypotheses;
    }
    if (new_hypotheses < 1)
        unmet.push_back("(a) no new competing hypothesis with differing prediction");

    // (b) >= 1 new substantive objection logged
    int new_substantive = 0;
    for (const auto& o : objections_now) {
        bool is_new = std::none_of(objections_before.begin(), objections_before.end(),
            [&](const Objection& old) { return old.id == o.id; });
        if (is_new && o.is_substantive) ++new_substantive;
    }
    if (new_substantive < 1)
        unmet.push_back("(b) no new substantive objection raised and logged");

    // (c) artifact revised or written justification provided
    if (!artifact_revised_or_justified)
        unmet.push_back("(c) artifact not revised and no written justification provided");

    return { unmet.empty(), unmet };
}

}  // namespace charter
