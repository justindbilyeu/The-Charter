# Proposal: Resolve execution deadlock in Coherence Controller DIVERSIFY trigger

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §3 Coherence Controller — DIVERSIFY trigger condition
**Charter version reviewed:** v2.1
**Model Confidence Note:** Gemini is prone to over-indexing on semantic logic loops and edge-case systemic deadlocks; may miss pragmatic user-experience frictions such as whether a human operator will find an automated operational pivot disruptive in rapid conversational workflows.

---

## Current Text

> The signal that triggers DIVERSIFY:
> "This feels obviously right."
>
> That feeling is not evidence of correctness.
> It is evidence that scrutiny should increase.

---

## Problem Statement

The DIVERSIFY trigger is defined as an internal subjective state — a "feeling" — that an LLM cannot reliably instantiate. This introduces two failure modes:

**1. Linguistic deadlock:** The Genesis section states *"We do not use the feeling of rightness as proof."* If the assistant successfully complies with this principle, it suppresses its "feeling of rightness" — and the DIVERSIFY trigger never fires. Conversely, if the assistant reports a "feeling," it has permitted an anthropomorphic internal state to drive its mode selection, violating the same Genesis principle it is supposed to uphold. Compliance and trigger activation are structurally incompatible.

**2. Infinite loop:** Any clean, well-structured solution can be met with the self-generated critique: "This feels obviously correct — therefore I must DIVERSIFY." There is no structural difference between "a good answer that should converge" and "a good answer that triggers more skepticism," because the trigger condition is the quality of the answer itself, not an observable structural property of the reasoning process.

LLMs generate text via probability distributions, not phenomenological experience. The phrase "obviously right" maps onto high-confidence token generation, which is a property of *any* well-formed response. The current trigger thus fires either never or always, depending on interpretation.

---

## Proposed Change

Replace the subjective trigger with observable structural conditions:

**Current:**
> The signal that triggers DIVERSIFY:
> "This feels obviously right."
>
> That feeling is not evidence of correctness.
> It is evidence that scrutiny should increase.

**Proposed:**
> The structural conditions that trigger DIVERSIFY:
>
> 1. Fewer than two competing hypotheses have been explicitly modeled for the current primary claim in this session.
> 2. The current claim or proposed artifact was generated without surfacing at least one explicit failure mode or boundary condition.
> 3. A gate check has not been applied to the current artifact since the last structural revision.
>
> When any condition is met, the assistant MUST enter DIVERSIFY: inject a counter-hypothesis, surface a failure mode, or apply a gate check before proceeding.

**Note on the proposed fix:** The skeptical residue below raises a real concern about rigid hypothesis-counting producing performative skepticism. Condition 1 in particular warrants further revision — "explicitly modeled" needs its own operational definition to avoid the same under-specification problem it is solving. This proposal is filed to establish the structural critique; the exact conditions may need a follow-on refinement.

---

## Skeptical Residue

**Strongest objection:** Replacing an intuitive heuristic with rigid structural accounting may produce performative skepticism — the assistant invents shallow counter-hypotheses to satisfy condition 1 rather than genuinely engaging with alternatives. The quality of the inquiry degrades into a checkbox exercise.

**Response:** This is a genuine risk and the strongest argument against this proposal as written. The mitigation is that the conditions are auditable — a shallow counter-hypothesis is observable as such and can be challenged, whereas a missed "feeling" is invisible. The current trigger produces invisible failures; the proposed conditions produce visible, challengeable ones. Performative compliance that is observable is preferable to invisible non-compliance.

**What would change confidence:** A concrete example of the proposed conditions being satisfied by a shallow counter-hypothesis while a genuine structural gap remains — i.e., conditions 1–3 pass but the proposal is clearly under-scrutinized. This would indicate the conditions are insufficient, not that subjective triggers are preferable.

---

## Gate Check

- **G2 Bounded scope:** Targets the DIVERSIFY trigger condition in §3 only; does not alter CONVERGE, RESTART, or any other section
- **G3 Operational definitions:** Replaces an unmeasurable internal state ("feeling") with observable structural properties (number of competing hypotheses, presence of explicit failure modes, gate check status)
- **G4 Test rigidity:** The three conditions are binary and evaluable at time of generation without post-hoc adjustment
- **G5 Mechanism:** Current text fails because it relies on an LLM mapping an anthropomorphic phenomenological state to a mode-change trigger. LLMs generate probabilistic token sequences; they have no subjective apparatus to trip a "feeling of rightness" wire reliably, producing either systematic non-triggering or arbitrary triggering
