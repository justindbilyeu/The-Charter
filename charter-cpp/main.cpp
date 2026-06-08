//
// Charter Machine — skeleton demo
//
// Demonstrates a clean single-artifact session: INIT → STRUCTURING →
// GATE_CHECK → DIVERSIFY → STRUCTURING → GATE_CHECK → CONVERGE → OUTPUT
//
// All LLM calls use MockLLMInterface. Gate results are deterministic.
// Run this to verify the FSM routing and enforcement logic before
// wiring a real LLM backend.
//

#include "charter/fsm.h"
#include "charter/gates.h"
#include "charter/coherence_controller.h"
#include "charter/session_continuity.h"
#include "charter/llm_interface.h"

#include <iostream>
#include <memory>

using namespace charter;

static void print_state(const CharterFSM& fsm) {
    std::cout << "  [FSM] " << to_string(fsm.current_state()) << "\n";
}

int main() {
    std::cout << "=== Charter Machine — skeleton demo (v2.7) ===\n\n";

    auto llm = std::make_shared<MockLLMInterface>();
    HardGates gates(llm);
    CoherenceController cc(llm);
    SessionContinuity scp;

    // -----------------------------------------------------------------------
    // Session start — Handshake
    // -----------------------------------------------------------------------
    CharterFSM fsm;
    fsm.handshake(/*loaded_from_compression=*/false);
    std::cout << "Handshake complete — charter v2.7, fresh session\n";
    print_state(fsm);

    // -----------------------------------------------------------------------
    // STRUCTURING — translate raw claim into structured artifact
    // -----------------------------------------------------------------------
    fsm.to_structuring("first claim");
    print_state(fsm);

    StructuredArtifact artifact = llm->structure_claim(
        "Daily 10-minute cold exposure reduces subjective fatigue scores "
        "by >= 20% over 30 days in healthy adults.");

    // Produce initial hypothesis set (H1 = primary claim)
    Hypothesis h1;
    h1.id = "H1";
    h1.evidence_level = EvidenceLevel::E1;
    h1.text = artifact.central_claim;
    h1.independent_variable = "cold_exposure_duration";
    h1.dependent_variable = "fatigue_score";
    h1.differing_prediction = "fatigue scores decrease >= 20% vs control";
    std::vector<Hypothesis> hypotheses = { h1 };

    ObjectionRegister objections;

    std::cout << "Artifact structured: " << artifact.id << "\n";
    std::cout << "  Central claim: " << artifact.central_claim << "\n";
    std::cout << "  Success criteria: " << artifact.success_criteria.size() << "\n\n";

    // -----------------------------------------------------------------------
    // GATE_CHECK — first pass (G3 fails in this demo — mock: g3_passes = false)
    // -----------------------------------------------------------------------
    fsm.to_gate_check();
    print_state(fsm);

    llm->g3_passes = false;  // simulate: G3 fails → DIVERSIFY
    auto gate_results = gates.evaluate(artifact);

    for (const auto& r : gate_results) {
        std::cout << "  Gate G" << (static_cast<int>(r.gate) + 1)
                  << ": " << (r.status == GateStatus::PASS ? "PASS" : "FAIL");
        if (!r.defect.empty()) std::cout << " — " << r.defect;
        std::cout << "\n";
    }

    State next = HardGates::route(gate_results);
    std::cout << "  → Routing to: " << to_string(next) << "\n\n";

    // -----------------------------------------------------------------------
    // Structural DIVERSIFY Triggers — check before entering DIVERSIFY
    // -----------------------------------------------------------------------
    auto trigger = cc.check_all_structural_triggers(artifact, objections, hypotheses);
    if (trigger.triggered)
        std::cout << "  Structural trigger " << trigger.condition << ": " << trigger.reason << "\n";

    fsm.to_diversify("G3 failure — key term 'fatigue' lacks operational definition; "
                     "Structural Trigger 1 — insufficient competing hypotheses");
    print_state(fsm);

    // -----------------------------------------------------------------------
    // PSP active — generate competing hypotheses and objections
    // -----------------------------------------------------------------------
    auto new_hypotheses = llm->generate_competing_hypotheses(artifact, hypotheses);
    hypotheses.insert(hypotheses.end(), new_hypotheses.begin(), new_hypotheses.end());
    std::cout << "  Competing hypotheses: " << hypotheses.size() << "\n";

    auto new_objections = llm->generate_objections(artifact, objections);
    objections.insert(objections.end(), new_objections.begin(), new_objections.end());
    std::cout << "  Objections generated: " << new_objections.size() << "\n";

    // Check DIVERSIFY exit criterion (v2.5)
    ObjectionRegister objections_before_div;
    std::vector<Hypothesis> hypotheses_before_div = { h1 };
    auto div_complete = cc.check_diversify_complete(
        hypotheses_before_div, hypotheses,
        objections_before_div, objections,
        /*artifact_revised_or_justified=*/true);

    std::cout << "  DIVERSIFY complete: " << (div_complete.complete ? "yes" : "no");
    if (!div_complete.complete) {
        for (const auto& u : div_complete.unmet)
            std::cout << "\n    unmet: " << u;
    }
    std::cout << "\n\n";

    // Declare completion to the FSM — required before to_structuring() from DIVERSIFY
    if (div_complete.complete)
        fsm.declare_diversify_complete();

    // -----------------------------------------------------------------------
    // Return to STRUCTURING — update artifact with operational definition
    // -----------------------------------------------------------------------
    fsm.to_structuring("DIVERSIFY complete — artifact revised with operationalized 'fatigue'");
    print_state(fsm);

    artifact.operational_definitions.push_back({
        "fatigue", "Chalder Fatigue Scale (CFS) total score", "measured at 0, 15, 30 days"
    });
    artifact.last_modified = std::chrono::system_clock::now();
    std::cout << "  Operational definition added: 'fatigue' → Chalder Fatigue Scale\n\n";

    // -----------------------------------------------------------------------
    // GATE_CHECK — second pass (all gates pass this time)
    // -----------------------------------------------------------------------
    fsm.to_gate_check();
    print_state(fsm);

    llm->g3_passes = true;
    gate_results = gates.evaluate(artifact);

    for (const auto& r : gate_results) {
        std::cout << "  Gate G" << (static_cast<int>(r.gate) + 1)
                  << ": " << (r.status == GateStatus::PASS ? "PASS" : "FAIL") << "\n";
    }

    next = HardGates::route(gate_results);
    std::cout << "  → Routing to: " << to_string(next) << "\n\n";

    // Resolve open objection before CONVERGE
    if (!objections.empty()) {
        objections[0].status = ObjectionStatus::TESTED;
        objections[0].test_result = "Selection bias controlled via randomized assignment";
        std::cout << "  Objection resolved: " << objections[0].id << "\n\n";
    }

    // -----------------------------------------------------------------------
    // CONVERGE
    // -----------------------------------------------------------------------
    fsm.to_converge(artifact, objections);
    print_state(fsm);

    // State Compression
    auto health = cc.evaluate_health(artifact, objections, fsm.consecutive_converge_count());
    AdversarialAnchor anchor = { false, DriftAssessment::NOT_ASSESSED, std::nullopt };
    std::string compression = scp.compress(
        artifact, objections, health, anchor,
        "Proceed to test execution: recruit n=100, run 30-day protocol",
        { "fatigue defined as CFS score" });
    std::cout << "  State Compression produced (" << compression.size() << " bytes)\n\n";

    // -----------------------------------------------------------------------
    // OUTPUT
    // -----------------------------------------------------------------------
    fsm.to_output();
    print_state(fsm);
    std::cout << "\nArtifact ready for test execution.\n";
    std::cout << "Session history:\n";
    for (const auto& [s, note] : fsm.history()) {
        std::cout << "  " << to_string(s);
        if (!note.empty()) std::cout << " — " << note;
        std::cout << "\n";
    }

    // -----------------------------------------------------------------------
    // Demonstrate FSM enforcement: DIVERSIFY → GATE_CHECK is illegal
    // -----------------------------------------------------------------------
    std::cout << "\n--- Enforcement demo ---\n";
    CharterFSM fsm2;
    fsm2.handshake();
    fsm2.to_structuring();
    fsm2.to_gate_check();
    fsm2.to_diversify("G3 failure");
    try {
        fsm2.to_gate_check();  // illegal — must return to STRUCTURING first
    } catch (const InvalidTransitionError& e) {
        std::cout << "Caught (expected): " << e.what() << "\n";
    }

    return 0;
}
