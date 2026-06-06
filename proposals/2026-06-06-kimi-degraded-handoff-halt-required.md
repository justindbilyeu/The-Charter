# Proposal: Degraded Handoff — "proceed but declare" contradicts MUST fields

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §9 Deserialization Procedure — final paragraph ("A compression missing gate status or objection register is a degraded handoff — proceed but declare which fields are missing")
**Charter version reviewed:** v2.4
**Model Confidence Note:** I may over-index on the halt-required option and under-weight session continuity concerns. The "proceed but declare" approach has genuine value in research contexts where stopping work is costly. A human reviewer should weigh the operational cost of a hard halt against the structural cost of the contradiction this proposal identifies.

---

## Current Text

> A valid State Compression contains:
> - Active claims and their current evidence level (E1–E5)
> - Gate status for all open artifacts (G1–G5)
> - Decisions made and the reasoning behind them
> - Skeptical residue: objections raised, resolved, and still open
> - Next step: single, specific, actionable
> - Assumptions added or modified this session
> - Constraint Health: state of the three monitoring conditions at compression time
> - Adversarial Anchor: whether the Convergence Watchdog fired this session; if so, what the drift assessment concluded

> A compression missing gate status or objection register is a degraded handoff — proceed but declare which fields are missing.

---

## Problem Statement

The State Compression section uses "contains" to list fields — implying all are required for validity. The Deserialization Procedure closes with "proceed but declare which fields are missing" for a compression missing gate status or objection register. These are in direct contradiction.

If gate status and objection register are MUST fields, a compression without them is not a valid State Compression — it is an incomplete or corrupted document. The appropriate response to an invalid document is not to proceed while noting the invalidity; it is to halt and require remediation. "Proceed but declare" prices degradation at zero cost: the only consequence of an incomplete handoff is a declaration, and the session continues as if the handoff were valid.

This creates a bypass route for inherited gate and objection state. An assistant receiving a degraded handoff that "proceeds but declares" effectively begins a fresh session with unverified gate status — precisely the condition §9 Deserialization Procedure is designed to prevent. The declaration is a fig leaf: it looks like accountability but produces no constraint on behavior.

The contradiction becomes exploitable under adversarial conditions: a State Compression that omits gate status and objection register strips the new session of its inherited constraints while appearing to follow the protocol. The "degrade and declare" path is indistinguishable from intentional sanitization.

---

## Proposed Change

Replace the final paragraph of the Deserialization Procedure:

**Current:**
> A compression missing gate status or objection register is a degraded handoff — proceed but declare which fields are missing.

**Proposed:**
> A compression missing required fields (gate status, objection register, Constraint Health, Adversarial Anchor) is an invalid handoff. Before new work proceeds, the operator must take one of three actions: (1) supply the missing fields explicitly, (2) grant an explicit waiver acknowledging that inherited gate and objection state cannot be verified and that affected artifacts must be re-evaluated from scratch, or (3) treat the session as fresh — no inherited claims, gates, or objections.
>
> A compression missing non-structural fields (next step, assumption log) may proceed with declaration. The distinction is: structural fields constrain the session's epistemic state; non-structural fields support orientation only.

This distinguishes between fields that carry epistemic obligations (gate status, objection register, health state, anchor) and fields that carry orientation value only (next step, assumption log). Incomplete structural fields require operator action. Incomplete orientation fields warrant declaration but not halt.

---

## Skeptical Residue

The strongest argument against the hard-halt option: research sessions have real costs. If a State Compression was produced under context pressure and is missing gate status, a hard halt may strand the session entirely — the operator may not be able to reconstruct the missing fields. The current "proceed but declare" approach preserves session continuity at the cost of epistemic cleanliness.

The counter: the charter explicitly states "Session state is not reconstructed from memory. It is carried forward in writing." A compression that cannot carry state forward in writing is not serving its function. The cost of a hard halt for an incomplete compression is a design pressure toward producing complete compressions — which is what the charter wants. The "proceed but declare" fallback removes that pressure.

A middle path: the proposed three-option remediation (supply fields / explicit waiver / fresh session) preserves operator agency without silently degrading epistemic state. The halt is not permanent — it requires a decision, not reconstruction.

---

## Gate Check

- **G2 Bounded scope:** Targets one paragraph at the end of the Deserialization Procedure in §9. The observation is that two adjacent passages in the same section contradict each other.
- **G3 Operational definitions:** The contradiction is observable: "valid State Compression contains [list]" followed by "proceed but declare" for a missing item from that list. Another model reading both passages would identify the same tension.
- **G4 Test rigidity:** Under the proposed change, a session receiving a compression missing gate status cannot proceed to new work without explicit operator action — a verifiable behavioral difference from the current "proceed but declare."
- **G5 Mechanism:** The mechanism of failure is cost asymmetry: if the penalty for an incomplete handoff is only a declaration, the incentive to produce complete handoffs is weakened and the exploit path (omit gate status, reset inherited constraints) costs nothing to execute.
