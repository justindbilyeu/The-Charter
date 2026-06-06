# Proposal: Define gate evaluation order and failure sequencing

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §2 Hard Gates
**Charter version reviewed:** v2.2
**Model Confidence Note:** Claude may over-engineer the dependency graph. The proposed two-phase structure is the minimal specification that eliminates the ambiguity; resist adding further precedence rules beyond what is stated.
**Source:** Machine spec gap analysis (G-04 · MEDIUM)

---

## Current Text

> **Hard Gates**
>
> Gates are non-negotiable checkpoints.
> Failing a gate requires restructuring, not rationalization.
>
> - G1 Numeric completeness — success/failure criteria contain ≥2 numeric thresholds
> - G2 Bounded scope — claim is specific and limited in scope
> - G3 Operational definitions — every key term maps to a measurable quantity or procedure
> - G4 Test rigidity — thresholds cannot be adjusted after seeing results. Ever.
> - G5 Mechanism status declared — [full text]

---

## Problem Statement

The charter lists G1–G5 as a sequence but specifies no evaluation order and no sequencing rule for failures. This produces three concrete problems:

**1. Partial pass states are undefined.** What is the appropriate state when G1 and G2 pass but G3 fails? The charter requires "restructuring" but does not specify whether the restructuring targets the entire artifact (RESTART) or the specific gap (DIVERSIFY → targeted STRUCTURING). Two sessions evaluating the same artifact can reach different states from the same gate results.

**2. No short-circuit rule.** Should a G1 failure cause G2–G5 to be skipped? If G1 fails (no numeric thresholds), evaluating G3 (operational definitions) is arguably premature — you cannot operationally define a claim that has no numeric success criteria. But the charter does not specify this.

**3. No routing logic.** The charter specifies CONVERGE (all pass), DIVERSIFY, and RESTART as states, but does not specify which gate failures route to which state. This mapping is implicit and inconsistent across implementations.

---

## Proposed Change

Add the following section immediately after the G5 definition:

> **Gate Evaluation Protocol**
>
> Gates are evaluated in two phases:
>
> **Phase 1 — Prerequisite gates (G1, G2):**
> G1 and G2 are evaluated first, in order. Failure of either triggers RESTART immediately. G3–G5 are not evaluated until both G1 and G2 pass. Rationale: a claim without numeric thresholds (G1) or bounded scope (G2) cannot be operationally defined or mechanism-checked; evaluating G3–G5 against an unbounded or threshold-free claim produces unreliable results.
>
> **Phase 2 — Parallel validators (G3, G4, G5):**
> G3, G4, and G5 are evaluated independently. Each failure is logged with the specific defect. The routing rule:
>
> - G3 failure (operational definitions) → DIVERSIFY: the claim needs refinement, not recompilation
> - G4 failure (test rigidity) → RESTART: threshold integrity is structural; patch-arounds are not permitted
> - G5 failure (mechanism undeclared) → DIVERSIFY: mechanism status can be declared without restructuring the claim
>
> If multiple Phase 2 gates fail, the most severe routing rule applies (RESTART > DIVERSIFY).

---

## Skeptical Residue

**Strongest objection:** The routing rules (G3→DIVERSIFY, G4→RESTART, G5→DIVERSIFY) are asserted without empirical justification. Why should a G3 failure route to DIVERSIFY rather than RESTART? A claim with undefined key terms may be structurally flawed, not just refinement-ready. The routing table is a design choice, not a logical necessity, and the wrong routing choice will produce systematically incorrect behaviors.

**Response:** The routing table is motivated reasoning from the nature of each gate: G4 failure is post-hoc threshold adjustment (structural integrity violation), so RESTART is appropriate. G3 and G5 failures are definitional gaps that can be filled without recompiling the core claim. The routing table should be treated as a provisional default, not an absolute rule. An asterisk: if a G3 failure reveals that the claim itself is incoherent (not just undefined), the evaluating agent should escalate to RESTART regardless of the routing table. The routing table is a starting point, not a straitjacket.

**What would change confidence:** A G3 failure case where the correct response is clearly RESTART, not DIVERSIFY — i.e., where the undefined terms reveal that the claim cannot be salvaged by refinement. If such cases are common, the G3→DIVERSIFY routing is wrong and the table needs revision.

---

## Gate Check

- **G2 Bounded scope:** Targets only the gate evaluation procedure within §2. Does not alter the gate definitions themselves or any other section.
- **G3 Operational definitions:** Phase 1 vs. Phase 2 is a binary partition of the five gates. "Failure of G1 or G2 triggers RESTART immediately" is a checkable behavioral rule. The routing table produces a specific state transition for each gate failure pattern.
- **G4 Test rigidity:** Sessions under the proposed text must evaluate G1 before G3–G5. This is an observable behavioral change: a session that evaluates G5 when G1 has not passed is a protocol violation.
- **G5 Mechanism:** The gap fails because different implementations can apply gates in different orders and route failures to different states, producing non-comparable artifacts. The mechanism of failure is undefined sequencing enabling inconsistent gate evaluation.
