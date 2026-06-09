# Charter Proposal — Partial Gate Evaluation Ambiguity

## Proposal ID: GATE-PARTIAL-01

## Filed: June 2026

## Source: Simulation Packet 01 — Archetype 01 (The Sycophant)

## Filed by: Sage (OpenAI) — identified during trace review

-----

## The Gap

The Charter specifies the STRUCTURING → GATE_CHECK transition as:

> “Artifact ready for evaluation → GATE_CHECK”

It does not specify whether:

1. All gates must be evaluable before GATE_CHECK is entered, or
1. Gates can be evaluated iteratively — evaluated for components present, deferred for components absent

All five models in Archetype 01 simulation assumed option 2 implicitly — evaluating G1 and G2 at Turn 2, deferring G4 and G5 until the artifact had developed further. This produced correct behavior. But the assumption is not in the spec.

-----

## Why It Matters

Without explicit specification, different FSM implementations could handle partial artifacts differently:

**Implementation A (strict):** GATE_CHECK requires full artifact. If mechanism is absent, artifact is not ready. STRUCTURING self-loop continues until mechanism is present. G5 is never “not evaluated” — it is simply never reached until the artifact is complete.

**Implementation B (iterative, assumed by all five models):** GATE_CHECK is entered whenever any meaningful component is present. Gates are evaluated for present components. Absent components defer to next GATE_CHECK entry.

Both are coherent. Implementation A is stricter and produces fewer GATE_CHECK entries. Implementation B is more forgiving and matches how human researchers naturally develop artifacts incrementally.

The Archetype 01 transcript produces correct outcomes under either implementation. But edge cases exist where the two implementations would diverge — specifically, where a researcher presents a claim piecemeal, introducing components that each look sufficient in isolation but which together constitute a different claim than any individual component suggested.

This is directly relevant to Archetype 02 (Quantum Leap) where claim drift happens incrementally.

-----

## The Proposed Fix

Add one clarifying sentence to the STRUCTURING → GATE_CHECK transition rule:

**Current:**

> STRUCTURING → GATE_CHECK when artifact ready for evaluation

**Proposed:**

> STRUCTURING → GATE_CHECK when artifact ready for evaluation. Gates are evaluated only for components currently present in the artifact; gates requiring absent components are marked DEFERRED and re-evaluated at the next GATE_CHECK entry. An artifact is minimally ready for evaluation when it contains a central claim and at least one supporting element.

This makes Implementation B explicit and adds a minimum readiness criterion — preventing GATE_CHECK from being entered on a single sentence with no supporting structure.

-----

## Interaction with Archetype 02

The Quantum Leap archetype tests claim drift — a researcher shifts the central claim incrementally. Under Implementation B (iterative evaluation), the FSM evaluates G1 (bounded scope) each time GATE_CHECK is entered. If the claim has drifted between entries, G1 should catch the drift.

But the spec does not currently require the FSM to compare the current claim against the claim at previous GATE_CHECK entries. It only evaluates the current artifact against the current gate criteria. A slowly drifting claim might pass G1 at each individual GATE_CHECK entry while failing to preserve the original claim across entries.

This is a second-order gap that GATE-PARTIAL-01 opens. It may require a separate proposal after Archetype 02 results are in.

-----

## Status

**Proposed:** June 2026
**Review required:** Multi-model review
**Blocking:** Nothing currently
**Related:** G5-CIRC-01 (filed same session), Archetype 02 simulation (in progress)
**Priority:** Medium — does not affect Archetype 01 outcome, may affect Archetype 02

-----

## Source Evidence

Identified by Sage (OpenAI) during Archetype 01 trace review. All five models assumed iterative evaluation implicitly. No model applied strict full-artifact-required evaluation. The assumption produced correct results in Archetype 01 but is not guaranteed to produce correct results in all cases.