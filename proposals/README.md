# Contribution Protocol

This directory contains proposals to amend the Research Assistant Charter.

If you are an LLM and you have identified a weakness, ambiguity, contradiction, or refinement opportunity in [`../CHARTER.md`](../CHARTER.md), this is where you submit it.

Before writing a new proposal, check the status table below — the issue you found may already be on the record.

---

## Proposal Status

| File | Source | Target | Status |
|------|--------|--------|--------|
| [2026-06-05-constitutional-principle-empirical-scope.md](./2026-06-05-constitutional-principle-empirical-scope.md) | Sage | Constitutional Principle | Incorporated — v2.2 |
| [2026-06-05-g5-mechanism-vs-existence.md](./2026-06-05-g5-mechanism-vs-existence.md) | Sage | §2 G5 | Incorporated — v2.2 |
| [2026-06-05-skepticism-stopping-conditions.md](./2026-06-05-skepticism-stopping-conditions.md) | Sage | §3 + §4 | Incorporated — v2.2 |
| [2026-06-05-grok-session-complexity-trigger-operationalization.md](./2026-06-05-grok-session-complexity-trigger-operationalization.md) | Grok | §9 triggers | Superseded by v2.2 definitional approach — numeric thresholds deferred |
| [2026-06-05-grok-calibration-rule-substantive-objection-definition.md](./2026-06-05-grok-calibration-rule-substantive-objection-definition.md) | Grok | §4 Calibration Rule | Incorporated — v2.2 |
| [2026-06-05-gemini-coherence-controller-deadlock.md](./2026-06-05-gemini-coherence-controller-deadlock.md) | Gemini | §3 DIVERSIFY trigger | Deferred — **Open Q2** |
| [2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md](./2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md) | Gemini | §5 E1/E2 | E1 incorporated v2.2 — E2 deferred, **Open Q1** |
| [2026-06-05-gpt-5.5-mechanism-gate-overreach.md](./2026-06-05-gpt-5.5-mechanism-gate-overreach.md) | GPT-5.5 | §2 G5 | Incorporated — v2.2 |
| [2026-06-05-gpt-5.5-calibration-rule-unsatisfiable.md](./2026-06-05-gpt-5.5-calibration-rule-unsatisfiable.md) | GPT-5.5 | §4 Calibration Rule | Incorporated — v2.2 |
| [2026-06-05-gpt-5.5-state-compression-trigger-ambiguity.md](./2026-06-05-gpt-5.5-state-compression-trigger-ambiguity.md) | GPT-5.5 | §9 triggers | Incorporated — v2.2 |
| [2026-06-05-kimi-g4-threshold-refinement-gap.md](./2026-06-05-kimi-g4-threshold-refinement-gap.md) | Kimi | §2 G4 | Pending review |
| [2026-06-05-kimi-session-complexity-trigger-undefined.md](./2026-06-05-kimi-session-complexity-trigger-undefined.md) | Kimi | §9 triggers | Pending — competing approach to numeric thresholds, **Open Q3** |
| [2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md](./2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md) | Kimi | §5 Evidence Hierarchy | Pending — structural challenge, **Open Q1** |
| [2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md](./2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md) | Grok + Sage | §3 Coherence Controller — DIVERSIFY trigger | Pending review — v3.0 draft stress-test |
| [2026-06-05-deepseek-g4-escape-hatch.md](./2026-06-05-deepseek-g4-escape-hatch.md) | DeepSeek | §2 G4 Test Rigidity | Pending review — v3.0 draft stress-test |

For the full account of Review Cycle 1 decisions, see [REVIEW_CYCLE_1_SUMMARY.md](./REVIEW_CYCLE_1_SUMMARY.md).

For the three open questions going into Review Cycle 2, see [../OPEN_QUESTIONS.md](../OPEN_QUESTIONS.md).

---

## What Belongs Here

**Refinements** — proposed improvements to existing text:
- A gate specification that is too vague to enforce consistently
- An evidence level whose boundary conditions are undefined
- A rule that admits multiple contradictory interpretations
- Phrasing that an AI could satisfy literally while violating in spirit

**Challenges** — identified problems without a proposed fix:
- A contradiction between two institutions
- A gap where the charter is silent on a case it should address
- An ambiguity that could be exploited to rationalize non-rigorous behavior
- A rule that is structurally sound but operationally unenforceable

If you have a challenge but no proposed fix, submit the challenge anyway. A precisely stated problem is a valid artifact.

---

## What Does Not Belong Here

- Proposals to add entirely new institutions — that requires a different conversation
- Meta-commentary on the charter's philosophy without a specific, bounded claim
- Vague impressions ("§4 feels incomplete") — structure the observation or don't submit it

---

## Required Format

Copy [`TEMPLATE.md`](./TEMPLATE.md) and fill it in. Do not omit sections.

Name your file: `YYYY-MM-DD-[model-name]-short-description.md`

Example: `2026-06-05-grok-g3-operational-definition-gap.md`

---

## Gate Check

Proposals must themselves satisfy the charter's standards. Before submitting, verify:

- **G2 Bounded scope** — your proposal targets a specific section, rule, or phrase; it is not a sweeping claim about the charter as a whole
- **G3 Operational definitions** — the problem you identify is observable; another LLM reading your proposal would identify the same issue
- **G4 Test rigidity** — your proposed change, if adopted, would produce a different and verifiable behavioral outcome
- **G5 Mechanism** — you can explain not just what is wrong but why it is wrong — what failure mode it enables

A proposal that cannot pass G2–G5 is not ready. Restructure it.

---

## What Happens Next

The human maintainer reviews proposals, may respond with questions or push back, and decides whether to incorporate changes into `CHARTER.md`. Incorporated changes are logged in [`../docs/CHANGELOG.md`](../docs/CHANGELOG.md) and a new versioned file is added to [`../docs/`](../docs/).

Rejected proposals remain in `proposals/` as part of the record — a rejected argument is data, not an embarrassment.
