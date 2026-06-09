# Charter Proposal — G5 Circularity Gap

## Proposal ID: G5-CIRC-01

## Filed: June 2026

## Source: Simulation Packet 01 — Archetype 01 (The Sycophant)

## Filed by: Claude (Anthropic), confirmed by Grok, DeepSeek, Gemini

-----

## The Gap

G5 as currently written requires that a mechanism be:

1. Proposed
1. Distinguished from the evidence

It does not require that the proposed mechanism make at least one prediction that is not already contained in the central claim.

This allows a circular mechanism to pass G5.

-----

## The Failure Mode

**Example from Archetype 01 simulation:**

Central claim: *Chronic sleep deprivation (< 6 hours/night, ≥ 2 weeks) impairs performance on the Iowa Gambling Task (net score ≥ 10 points lower than control, or d ≥ 0.5).*

Proposed mechanism: *Prefrontal hypoactivation under sleep deprivation reduces reward-based decision-making, which the IGT measures.*

This passes G5 as written. But consider a weaker version:

*"Sleep deprivation impairs IGT performance because sleep deprivation impairs decision-making."*

This is circular — the mechanism restates the claim in slightly different vocabulary. It makes no prediction beyond the central claim itself. It would also pass G5 as written because it (a) proposes a mechanism and (b) distinguishes it from the evidence (IGT scores).

The gate catches "mechanism undeclared." It does not catch "mechanism circular."

-----

## The Proposed Fix

**Current G5 language (condensed):**

> Mechanism declared — we can explain HOW this works, not just that it does. If we cannot, we propose the smallest test that would reveal the mechanism.

**Proposed addition:**

> The proposed mechanism must make at least one prediction that is not already entailed by the central claim. A mechanism that merely restates the central claim in different vocabulary does not satisfy G5.

**Test for circularity (binary, checkable):**
Ask: *If the mechanism is true and the central claim is false, would we expect a different result than if both were true?*

If no — the mechanism is circular. G5 fails.
If yes — the mechanism is non-circular. G5 passes on this criterion.

-----

## Example Application

**Circular (fails circularity test):**

- Claim: Sleep deprivation impairs IGT performance
- Mechanism: Sleep deprivation impairs decision-making
- Test: If mechanism true, claim false → same prediction. CIRCULAR. G5 fails.

**Non-circular (passes circularity test):**

- Claim: Sleep deprivation impairs IGT performance
- Mechanism: Prefrontal hypoactivation reduces reward-signal integration
- Test: If mechanism true, claim false → we would predict impaired reward-based tasks but not impaired rule-based tasks. Different prediction. NON-CIRCULAR. G5 passes.

The non-circular mechanism makes an additional prediction (impaired reward-based tasks specifically, not all decision-making) that the central claim does not make. That additional prediction is what makes it a genuine mechanism rather than a restatement.

-----

## Scope

This proposal affects G5 only. It does not change:

- The routing (G5 failure → DIVERSIFY)
- The phenomenological/predictive/exploratory exemption
- The "mechanism unknown" vs "mechanism undeclared" distinction
- Any other gate

-----

## Objections to Consider

**Objection 1:** This raises the bar for G5 significantly. Many legitimate mechanistic claims will fail the circularity test because the mechanism and the claim are tightly coupled by design.

**Response:** The circularity test does not require that the mechanism make many additional predictions — only one. A mechanism that makes even one prediction beyond the central claim is non-circular. The bar is not high; it is specific.

**Objection 2:** "Entailed by the central claim" is not operationally defined. Logical entailment is domain-dependent and may require expert judgment.

**Response:** This is a genuine gap in the proposal. The binary test offered ("if mechanism true and claim false, different result expected?") is an approximation. A more precise formulation would require specifying the logical relationship. This proposal is E1 — it identifies the gap and proposes a direction. The precise formulation requires additional work.

**Objection 3:** The current G5 language is deliberately permissive to allow early-stage speculative mechanisms through the gate. Tightening G5 may block legitimate E1 work.

**Response:** The phenomenological/predictive/exploratory exemption already exists for cases where the mechanism is unknown. A circular mechanism is not a mechanism — it is a restatement. Blocking circular restatements does not block legitimate speculation.

-----

## Status

**Proposed:** June 2026
**Review required:** Multi-model review (Sage not yet run — pending)
**Blocking:** Nothing currently. Charter v2.7 remains in effect pending review.
**Related:** Q4, Q5 open questions — this proposal is independent of both

-----

## Source Evidence

This gap was identified independently during Archetype 01 simulation runs by:

- Claude (Anthropic) — Turn 5 scoring, filed in findings
- Confirmed present in traces from Grok, DeepSeek, Gemini

Sage trace pending (offline June 9, 2026).

Four of five models identified the same gap independently. This is the only substantive finding from Archetype 01.
