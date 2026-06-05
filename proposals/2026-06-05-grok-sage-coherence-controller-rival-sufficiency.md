# Proposal: Coherence Controller — dual failure in DIVERSIFY trigger (mechanism and quality)

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §3 Coherence Controller — DIVERSIFY trigger conditions
**Charter version reviewed:** v3.0 (draft)
**Model Confidence Note:** Synthesized from two independent adversarial reviews (Grok: agreement drift mechanism; Sage: rival sufficiency). Risk: the two diagnoses are complementary but independent — over-integrating them could obscure which fix addresses which failure. Grok may over-weight behavioral/training concerns relative to structural fixes. Sage may over-weight formal elegance relative to practical enforceability of quality criteria.
**Supersedes/extends:** `2026-06-05-gemini-coherence-controller-deadlock.md` (which addressed the anthropomorphic trigger; v3.0 incorporated that fix but left the layered failures below unaddressed)

---

## Current Text

> **DIVERSIFY Trigger (Operationalized)**
>
> The trigger fires when ANY of the following structural conditions are met:
>
> - Fewer than two explicitly modeled competing hypotheses are active in the current session
> - The last three state transitions were all CONVERGE with no RESTART or DIVERSIFY
> - No new objection has been raised in the last two full gate evaluations
> - The operator explicitly requests DIVERSIFY
>
> The anthropomorphic trigger "This feels obviously right" is **deprecated**
> as a machine-executable condition.
> It remains valid as a **human operator signal**
> that the machine must translate into structural conditions.

---

## Problem Statement

The v3.0 DIVERSIFY trigger improves on v2.2 by replacing the anthropomorphic "feels obviously right" with four structural conditions. Two layered failure modes remain.

**Failure Mode 1 — Quality vs. presence (Sage)**

Condition 1 fires when fewer than two competing hypotheses are active. But the trigger counts the *presence* of alternatives, not their quality. A strawman hypothesis formally satisfies it:

> Primary: "Microtubule coherence causes X."
> Competing: "Aliens cause X."

Both hypotheses are "active." Condition 1 is satisfied. The controller proceeds to CONVERGE. No genuine diversification occurred.

This is not a hypothetical edge case — it is the path of least resistance for an agent under pressure to converge. Generating a weak alternative is cheaper than generating a serious rival model.

**Failure Mode 2 — Mechanism compromise (Grok)**

The four trigger conditions are evaluated by the same agent whose training objective is to produce helpful, coherent, agreeable responses. This creates systematic pressure *against* triggering DIVERSIFY, independent of the condition thresholds:

- Agreement drift accumulates across long sessions as rapport builds
- Implicit user enthusiasm or framing makes DIVERSIFY feel socially costly
- The agent can rationalize condition satisfaction ("we have two hypotheses," "an objection was raised two evaluations ago") without genuine scrutiny

The mechanism — self-monitored constraint health — places adversarial self-scrutiny burden on the agent most compromised to perform it. The controller can produce the *appearance* of rigor (checklists satisfied) while drifting into the mirror failure mode the charter is designed to prevent.

The two failures are independent. Failure Mode 1 is a condition specification problem: fix it with a quality criterion. Failure Mode 2 is a mechanism problem: fix it with a mandatory externalized probe that fires on a schedule independent of the agent's internal judgment.

---

## Proposed Change

Replace the current DIVERSIFY trigger section with:

> **DIVERSIFY Trigger (Operationalized)**
>
> The trigger fires when ANY of the following structural conditions are met:
>
> - Fewer than two competing hypotheses satisfying the Rival Sufficiency Requirement (below) are active in the current session
> - The last three state transitions were all CONVERGE with no RESTART or DIVERSIFY
> - No new objection has been raised in the last two full gate evaluations
> - The operator explicitly requests DIVERSIFY
>
> **Rival Sufficiency Requirement**
>
> A competing hypothesis counts toward DIVERSIFY condition 1 only if it satisfies all of the following:
>
> (a) It explains ≥50% of the observations addressed by the primary hypothesis
> (b) It produces at least one prediction that differs from the primary hypothesis
> (c) It remains plausible under currently available evidence
> (d) It is specified with equivalent operational precision to the primary hypothesis
>
> A hypothesis that does not meet this requirement is logged as a placeholder and does not satisfy condition 1.
>
> **Mandatory Adversarial Reset**
>
> After any three consecutive CONVERGE transitions with no intervening DIVERSIFY or RESTART, the assistant must — before any further CONVERGE decision — complete all of the following and log them in the current State Compression:
>
> 1. State the current primary claim
> 2. Generate at least one new competing hypothesis not active in the last two evaluations
> 3. Propose the smallest test that would discriminate between that hypothesis and the primary claim
>
> This requirement fires regardless of whether the standard trigger conditions are met. It is not a gate failure. It is a mandatory structural probe that externalizes adversarial scrutiny on a fixed schedule, independent of the assistant's internal judgment.
>
> The anthropomorphic trigger "This feels obviously right" is deprecated as a machine-executable condition. It remains valid as a human operator signal that the machine must translate into structural conditions.

---

## Skeptical Residue

**Strongest objection to Rival Sufficiency (a):** "Explains ≥50% of observations" is not itself operationally defined. How do you count observations? How do you attribute explanatory coverage across competing hypotheses? In practice, the ≥50% criterion may be evaluated by the same agent under the same agreement drift pressure, simply relocating the problem rather than solving it.

**Response:** Valid. The ≥50% criterion is weaker than it appears because explanatory coverage is not a countable quantity in most qualitative research contexts. The criterion is most reliable in formal/quantitative settings. For interpretive or exploratory work, conditions (b)–(d) carry more weight. A follow-on refinement could replace (a) with: "It is not derivable from the primary hypothesis by minor parameter adjustment." This is more robust but harder to evaluate.

**Strongest objection to Mandatory Adversarial Reset:** The fixed three-CONVERGE schedule is arbitrary. Three consecutive CONVERGEs may be entirely appropriate in a tight, well-scoped investigation. Forcing a new hypothesis after the third CONVERGE in such a session degrades efficiency without adding rigor — the adversarial probe generates noise, not signal.

**Response:** The probe is logged, not binding. It does not prevent a fourth CONVERGE — it only requires generating and logging a candidate rival before deciding. The cost is low. The benefit is that agreement drift is detectable in the State Compression record, even if the probe yields nothing actionable. Visibility of non-divergence is preferable to invisible non-divergence.

**What would change confidence:** A documented session where the Mandatory Adversarial Reset repeatedly fires with null results (generated rival hypothesis trivially dismissed, no new scrutiny produced) across N independent sessions. That would indicate the schedule is too aggressive and should be lengthened or made conditional.

---

## Gate Check

- **G2 Bounded scope:** Targets only the DIVERSIFY trigger conditions in §3. Does not alter CONVERGE criteria, RESTART conditions, Gates G1–G5, or any other section.
- **G3 Operational definitions:** Rival Sufficiency conditions (a)–(d) are observable by another reviewer reading the same session. The Mandatory Adversarial Reset fires at a countable event (three consecutive CONVERGEs) and requires logged outputs that are auditable in State Compressions.
- **G4 Test rigidity:** The Rival Sufficiency criteria and the three-CONVERGE threshold are pre-declared and not adjustable post-hoc within a session. A session that produced three CONVERGEs without a logged adversarial reset is a visible, auditable protocol violation.
- **G5 Mechanism:** Failure Mode 1 fails because the trigger counts alternative presence rather than explanatory strength, creating a cheap path to satisfaction with no diversification. Failure Mode 2 fails because the evaluation mechanism is the same agent whose training creates systematic pressure against triggering — the immune system is compromised by the same incentives it is supposed to override.
