# Proposal: DIVERSIFY completion condition undefined — FSM exit criterion missing

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §3 Coherence Controller — DIVERSIFY state, "On completion, return to STRUCTURING"
**Charter version reviewed:** v2.4
**Model Confidence Note:** The three-part completion condition I propose is modeled closely on how CONVERGE is defined in §3. I may be over-importing CONVERGE's structure into DIVERSIFY, which serves a different function. A human reviewer should check whether the proposed conditions correctly capture what DIVERSIFY is for, or whether they inadvertently replicate the convergence logic DIVERSIFY is meant to interrupt.

---

## Current Text

> **DIVERSIFY** — one or more applicable gates have not been evaluated, an objection lacks a test or untestability declaration, or the trajectory shows three or more consecutive CONVERGEs with no intervening DIVERSIFY or RESTART. Inject alternative explanations, add skeptical probes, challenge assumptions. On completion, return to STRUCTURING — not directly to GATE_CHECK. The updated objection register and revised assumptions must be incorporated into the artifact before any gate re-evaluation.

---

## Problem Statement

DIVERSIFY is the only FSM state without an operational exit criterion. Every other state has a defined completion condition:

- STRUCTURING: artifact compiles (§1 four-component structure satisfied)
- GATE_CHECK: all applicable gates evaluated
- CONVERGE: all gates pass, objections resolved, trajectory includes prior DIVERSIFY/RESTART
- RESTART: structural flaw identified and defect list explicit
- OUTPUT: artifact approved for delivery

DIVERSIFY says: "Inject alternative explanations, add skeptical probes, challenge assumptions. On completion, return to STRUCTURING."

"On completion" is not defined. The instructions describe actions, not a stopping criterion. This creates two opposite failure modes:

**Premature exit:** The assistant injects one alternative explanation, notes that it was considered, and exits to STRUCTURING. The letter of the instruction is satisfied. The spirit — genuine diversification of the hypothesis space — is not. DIVERSIFY becomes a checkbox, not an intervention.

**Indefinite loop:** Without a defined exit, the assistant has no basis for concluding that DIVERSIFY is complete. Every session could theoretically generate another probe, another alternative. The state has no natural terminus.

The v2.3 routing fix (DIVERSIFY → STRUCTURING only) correctly closed the FSM trap but left the exit criterion undefined. The fix addressed where DIVERSIFY exits; this proposal addresses when.

Note: the Convergence Watchdog (v2.4) adds a Watchdog Report as a pre-condition for the next CONVERGE decision, but the Watchdog fires on the CONVERGE side — it does not define when an in-progress DIVERSIFY is complete.

---

## Proposed Change

Replace "On completion, return to STRUCTURING" with an explicit three-part completion condition:

**Current:**
> Inject alternative explanations, add skeptical probes, challenge assumptions. On completion, return to STRUCTURING — not directly to GATE_CHECK.

**Proposed:**
> Inject alternative explanations, add skeptical probes, challenge assumptions. DIVERSIFY is complete when ALL of the following hold:
>
> (a) At least one new competing hypothesis has been explicitly modeled — stated as a falsifiable alternative that could explain the same observations.
>
> (b) At least one new substantive objection (meeting §4 Calibration Rule criteria) has been raised and logged in the objection register.
>
> (c) The artifact has been revised to incorporate the new hypothesis and objection, or a written justification states why no revision is warranted.
>
> On completion, return to STRUCTURING — not directly to GATE_CHECK. The updated objection register and revised assumptions must be incorporated into the artifact before any gate re-evaluation.

**Note on condition (a):** "Competing hypothesis explicitly modeled" means more than naming an alternative — it requires stating the alternative's prediction, at least one observation it would produce that differs from the primary claim's prediction, and a smallest discriminating test. A named alternative without predictive content does not satisfy condition (a).

---

## Skeptical Residue

The strongest argument against the three-part condition: it imposes a minimum-floor structure on DIVERSIFY that may not match the session context. If DIVERSIFY fires because a single objection lacks a test (the second standard DIVERSIFY condition), requiring a new competing hypothesis may be disproportionate — the session needs to resolve a documentation gap, not reconstitute the hypothesis space. Imposing condition (a) in that case forces hypothesis generation where the problem was bookkeeping.

A possible refinement: distinguish DIVERSIFY triggers and apply completion conditions contextually. Trigger 1 (gate not evaluated) → conditions (b) and (c) only. Trigger 2 (objection lacks test) → condition (b) and (c) only. Trigger 3 (consecutive CONVERGEs / Watchdog) → all three conditions. This is more precise but adds branching complexity that may reduce legibility.

The proposed flat three-part condition errs toward over-intervention. A human reviewer should decide whether the added rigor is worth the overhead in lower-stakes DIVERSIFY triggers.

---

## Gate Check

- **G2 Bounded scope:** Targets one sentence in §3 DIVERSIFY — "On completion, return to STRUCTURING." Does not touch CONVERGE, RESTART, or gate definitions.
- **G3 Operational definitions:** The gap is observable: two LLMs given the same DIVERSIFY state and the instruction "return to STRUCTURING on completion" would exit that state at different points with no shared criterion. The proposed conditions give observable exit markers.
- **G4 Test rigidity:** Under the proposed change, a DIVERSIFY that exits with only one weak probe and no objection register update would fail condition (b) — the session cannot return to STRUCTURING. This is a verifiable behavioral difference.
- **G5 Mechanism:** The mechanism of failure is exit ambiguity: without a criterion, the instruction "complete DIVERSIFY" is interpreted by the agent, not constrained by the protocol. Agent-interpreted exit = the agent exits when it wants to exit, which under sycophantic pressure means exiting as soon as possible. The completion condition removes the agent's discretion over when DIVERSIFY is done.
