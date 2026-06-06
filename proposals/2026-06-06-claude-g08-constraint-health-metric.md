# Proposal: Define "constraint health" as an observable quantity

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §3 Coherence Controller
**Charter version reviewed:** v2.2
**Model Confidence Note:** Claude is prone to formalizing metaphors into metrics prematurely. The skeptical residue below argues that Option B (reframe rather than formalize) may be preferable. The proposal offers both options and recommends the simpler one.
**Source:** Machine spec gap analysis (G-08 · LOW)

---

## Current Text

> The assistant monitors **constraint health** during structuring and explicitly decides:
>
> **CONVERGE** — structure is tight, gates pass, proceed to test.
> **DIVERSIFY** — inject alternative explanations, add skeptical probes, challenge assumptions before proceeding
> **RESTART** — recompile with explicit defect list, do not patch around a structural flaw

---

## Problem Statement

"Constraint health" is used as the input to the Coherence Controller's state decision. It is the variable the controller monitors. But it is never defined as a measurable quantity — not as a scalar, a vector, or a set of observable conditions.

This means the controller's core decision — which of CONVERGE, DIVERSIFY, RESTART to choose — is made against an undefined input. The controller is told to monitor something it cannot compute.

In practice, "constraint health" is understood intuitively: high health means gates are passing and objections are being addressed; low health means something is wrong. But "understood intuitively" is precisely what the charter is designed to replace with observable conditions. The charter cannot simultaneously require that "constraint health" drive state decisions and leave it undefined.

Two options are available:

**Option A:** Define constraint health as a function of observable session quantities.
**Option B:** Remove "constraint health" as a term and replace it with the observable conditions it gestures at.

Option B is simpler and avoids introducing a metric that would need ongoing calibration. This proposal recommends Option B.

---

## Proposed Change

**Option B (recommended):** Replace "constraint health" with explicit observable conditions.

Replace:

> The assistant monitors **constraint health** during structuring and explicitly decides:

With:

> The assistant monitors the following conditions during structuring and explicitly decides:
>
> - **Gates:** how many of G1–G5 have been evaluated and passed for the current artifact
> - **Objections:** whether the objection register contains any OPEN entries
> - **Trajectory:** whether the last state transition was CONVERGE following a DIVERSIFY or RESTART (scrutiny was active) or CONVERGE following another CONVERGE (scrutiny may be drifting)

And update the CONVERGE/DIVERSIFY/RESTART descriptions to reference these conditions explicitly:

> **CONVERGE** — all applicable gates pass, objection register has no OPEN entries, and the trajectory shows at least one DIVERSIFY or RESTART in the recent session history. CONVERGE is exhausted scrutiny, not pattern-matched agreement.
>
> **DIVERSIFY** — one or more gates have not been evaluated, the objection register has OPEN entries, or the trajectory shows three or more consecutive CONVERGEs. Inject alternative explanations, add skeptical probes, challenge assumptions before proceeding.
>
> **RESTART** — a structural flaw has been identified that cannot be resolved by refinement. Recompile with explicit defect list. Do not patch around a structural flaw.

**Option A (if a metric is preferred):** Define constraint health as:

> H = (gates_passed / max(1, gates_evaluated)) × (objections_resolved / max(1, objections_raised))
>
> H ∈ [0, 1]. High health (H > 0.8): CONVERGE is appropriate if trajectory conditions also favor it. Low health (H < 0.5): DIVERSIFY or RESTART is required. The trajectory condition (three consecutive CONVERGEs) overrides a high H score and triggers DIVERSIFY regardless.

---

## Skeptical Residue

**Strongest objection to Option B:** Replacing "constraint health" with a list of observable conditions makes the Coherence Controller section longer and more complex. The original prose is cleaner precisely because "constraint health" is a compressed, intuitive concept. An experienced operator understands it immediately. Over-specifying it into observable conditions may actually make the charter harder to internalize and apply.

**Response:** The charter's purpose is to define behavior that is consistent, auditable, and not dependent on "intuitive understanding." If "constraint health" is intuitive but undefined, it is doing the same work as "This feels obviously right" in the DIVERSIFY trigger — a naturalistically-grounded but non-operational concept. The charter has already rejected that approach for the DIVERSIFY trigger. Consistency requires rejecting it here too.

**What would change confidence:** Evidence that the observable conditions in Option B produce worse state decisions than the intuitive "constraint health" concept — i.e., sessions with high H and favorable trajectory that clearly should have triggered DIVERSIFY, or vice versa. That would indicate the observable proxies are the wrong proxies.

---

## Gate Check

- **G2 Bounded scope:** Targets only the "constraint health" concept and the CONVERGE/DIVERSIFY/RESTART state descriptions in §3. Does not alter trigger conditions, gates, or any other section.
- **G3 Operational definitions:** "Gates evaluated and passed" is countable. "OPEN objection register entries" is countable. "Three or more consecutive CONVERGEs" is countable from the session history. All three monitoring conditions are observable from session state without inference.
- **G4 Test rigidity:** Sessions under the proposed text must base state decisions on the three observable conditions. A CONVERGE decision that does not satisfy the gate, objection register, and trajectory conditions is a protocol violation — auditable from the session transcript.
- **G5 Mechanism:** The gap fails because the controller's decision input ("constraint health") is defined only by intuition. A controller that makes decisions against an undefined input cannot be audited, compared across sessions, or improved. The mechanism of failure is undefined inputs producing unverifiable decisions.
