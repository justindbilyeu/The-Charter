# Proposal: Trigger-Differentiated DIVERSIFY Exit Conditions (Q4 Resolution)

**Date:** 2026-06-08
**Type:** Refinement
**Target:** §3 Coherence Controller — DIVERSIFY exit criterion (Open Q4)
**Charter version reviewed:** v2.7
**Model Confidence Note:** Prone to over-structuring — the two-tier framework may introduce more classification complexity than the problem warrants. The adversarial dilution failure mode is real, but its frequency in practice is unknown. The tier assignment of G3 (Tier 2) and G5 (Tier 1) is the most contestable part of this proposal and may not survive reviewer scrutiny. Source insight: Kimi's Q4 framing (trigger-differentiated exit deferred in v2.5); proposal structure is Claude Chat's.

---

## Current Text

> DIVERSIFY is complete when all of the following hold:
>
> (a) At least one new competing hypothesis has been explicitly modeled — stated as a falsifiable alternative that could explain the same observations, with at least one prediction that differs from the primary claim's prediction.
>
> (b) At least one new substantive objection (meeting §4 Calibration Rule criteria) has been raised and logged in the objection register.
>
> (c) The artifact has been revised to incorporate the new hypothesis and objection — or a written justification states why no revision is warranted.

---

## Problem Statement

The flat three-part condition applies uniformly regardless of what caused DIVERSIFY to fire. DIVERSIFY can fire from hypothesis-space triggers (Structural Trigger 1: fewer than two competing hypotheses; Convergence Watchdog drift assessment; G5 failure) or from bookkeeping triggers (Structural Trigger 2: objection register gap or missing Failure Mode Probe; Structural Trigger 3: gate omission; G3 failure).

**The failure mode: adversarial dilution.**

Condition (a) — a new competing hypothesis — is the correct remedy when the triggering condition implicates the hypothesis space. When DIVERSIFY fires from Trigger 2 (a missing objection or Failure Mode Probe entry), the defect is a bookkeeping gap, not an under-explored hypothesis space. Requiring (a) in response to Trigger 2 forces the assistant to manufacture a competing hypothesis to clear an exit gate that has nothing to do with hypotheses.

The manufactured hypothesis is, by construction, one the assistant did not find necessary to model on the merits — it exists only to satisfy the gate. It then enters the hypothesis register and is counted toward future Trigger 1 evaluations (which require ≥2 documented competing hypotheses). A low-value hypothesis minted to clear a bookkeeping gate dilutes the signal Trigger 1 depends on: the register now contains a hypothesis that was never genuinely competing.

This is adversarial dilution — the exit requirement for one trigger degrades the structure (the hypothesis register) that a different trigger relies on.

---

## Proposed Change

Replace the flat three-part condition with a trigger-differentiated condition. The completion requirement depends on what caused DIVERSIFY to fire.

### Tier 1 — Hypothesis-space triggers (require a + b + c)

When DIVERSIFY fires from any of:
- Structural Trigger 1 (hypothesis under-specification)
- Convergence Watchdog drift assessment
- G5 failure (mechanism status — implicates the explanatory space)

All three completion conditions (a), (b), (c) are required.

### Tier 2 — Bookkeeping and currency triggers (require b + c only)

When DIVERSIFY fires from any of:
- Structural Trigger 2 (objection register or Failure Mode Probe gap)
- Structural Trigger 3 (gate omission — new content since last evaluation)
- G3 failure (operational definitions)

Only conditions (b) and (c) are required. Condition (a) is permitted but not mandatory — if the assistant identifies a genuinely competing hypothesis during diversification, it logs it; it is not required to manufacture one.

### Guardrail against downgrade abuse

The triggering condition must be recorded in the session log at DIVERSIFY entry (the FSM already records `violated_condition` on `to_diversify()`). The exit tier is determined by the recorded entry condition, not re-derived at exit. If multiple conditions fire simultaneously, the highest tier governs: any Tier-1 trigger present requires the full a+b+c exit.

### Proposed replacement text (§3 DIVERSIFY exit criterion)

> DIVERSIFY is complete when the conditions below for the applicable tier hold.
>
> **Tier 1 — hypothesis-space triggers** (Structural Trigger 1, Convergence Watchdog drift assessment, G5 failure): all three conditions required:
>
> (a) At least one new competing hypothesis has been explicitly modeled — stated as a falsifiable alternative that could explain the same observations, with at least one prediction that differs from the primary claim's prediction.
>
> (b) At least one new substantive objection (meeting §4 Calibration Rule criteria) has been raised and logged in the objection register.
>
> (c) The artifact has been revised to incorporate the new hypothesis and objection — or a written justification states why no revision is warranted.
>
> **Tier 2 — bookkeeping and currency triggers** (Structural Trigger 2, Structural Trigger 3, G3 failure): conditions (b) and (c) required; condition (a) permitted but not mandatory.
>
> The triggering condition is recorded at DIVERSIFY entry. The exit tier is determined by that recorded condition, not re-derived at exit. If multiple triggers fire simultaneously, the highest tier governs.

---

## Skeptical Residue

**Objection:** The differentiated rule introduces a classification step (which tier?) that the flat rule does not have. This is new surface area for error or gaming — an assistant motivated to exit DIVERSIFY quickly is incentivized to classify the trigger as Tier 2. The guardrail (record trigger at entry, highest tier governs) mitigates this but does not eliminate it: the classification of a trigger into Tier 1 vs. Tier 2 is itself a judgment in borderline cases.

**Response:** The guardrail makes the tier a function of the recorded entry condition, which is mechanical given the trigger type. The only residual judgment is the fixed mapping of trigger types to tiers, which is set in the charter, not decided per-session. This converts a per-session judgment into a one-time charter decision — the right place for it.

**What would change confidence:** Telemetry from the Charter Machine on hypothesis register composition across sessions. If hypothesis registers do not in fact accumulate low-value hypotheses under the flat rule (i.e., adversarial dilution is rare in practice), the urgency of this change drops and it could be deferred. The proposal assumes Trigger 2 events are frequent enough for dilution to matter; that assumption is testable once the machine runs real sessions.

---

## Gate Check

- **G2 Bounded scope:** This proposal targets one clause of §3 — the DIVERSIFY completion condition. It does not modify the triggering conditions, the definition of a substantive objection (§4 Calibration Rule), the CONVERGE preconditions, or any other institution.
- **G3 Operational definitions:** "Adversarial dilution" is defined as: a hypothesis minted solely to satisfy an exit gate, logged in the register, and counted toward future Trigger 1 evaluations — measurable as hypothesis register entries with no corresponding Trigger-1 or Watchdog event in the preceding DIVERSIFY cycle. The tier assignment of each trigger is observable: any LLM reading the triggering condition in the session log would classify it the same way.
- **G4 Test rigidity:** Testable in the Charter Machine — run two identical sessions with a Trigger 2 event, one under each rule. The flat rule produces an extra hypothesis entry with no Trigger-1 context; the differentiated rule does not. Hypothesis register composition is a measurable output.
- **G5 Mechanism:** The flat rule fails because the three completion conditions are not interchangeable remedies. Each maps to a distinct epistemic deficit: (a) remedies an under-explored hypothesis space; (b) remedies insufficient skeptical pressure; (c) ensures the artifact reflects the diversification. Applying (a) when the triggering condition does not implicate the hypothesis space does not deepen scrutiny — it generates a token artifact that satisfies the letter of the gate while degrading the register's signal value.
