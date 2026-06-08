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
| [2026-06-05-gemini-coherence-controller-deadlock.md](./2026-06-05-gemini-coherence-controller-deadlock.md) | Gemini | §3 DIVERSIFY trigger | Deferred — superseded by v2.6 resolution |
| [2026-06-05-gemini-diversify-trigger-resolution.md](./2026-06-05-gemini-diversify-trigger-resolution.md) | Gemini | §3 Coherence Controller — DIVERSIFY trigger (Q2) | **Incorporated — v2.6** (three structural conditions; "This feels obviously right" preserved as operator framing) |
| [2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md](./2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md) | Gemini | §5 E1/E2 | E1 incorporated v2.2 — E2 superseded by v2.7 resolution |
| [2026-06-06-claude-chat-evidence-hierarchy-resolution.md](./2026-06-06-claude-chat-evidence-hierarchy-resolution.md) | Claude Chat | §5 Evidence Hierarchy — E2 operational fix (Q1) | **Incorporated — v2.7** (Option A: verifiable citation + corroboration for foundational assumptions; Kimi structural concern deferred as Q5) |
| [2026-06-05-gpt-5.5-mechanism-gate-overreach.md](./2026-06-05-gpt-5.5-mechanism-gate-overreach.md) | GPT-5.5 | §2 G5 | Incorporated — v2.2 |
| [2026-06-05-gpt-5.5-calibration-rule-unsatisfiable.md](./2026-06-05-gpt-5.5-calibration-rule-unsatisfiable.md) | GPT-5.5 | §4 Calibration Rule | Incorporated — v2.2 |
| [2026-06-05-gpt-5.5-state-compression-trigger-ambiguity.md](./2026-06-05-gpt-5.5-state-compression-trigger-ambiguity.md) | GPT-5.5 | §9 triggers | Incorporated — v2.2 |
| [2026-06-05-kimi-g4-threshold-refinement-gap.md](./2026-06-05-kimi-g4-threshold-refinement-gap.md) | Kimi | §2 G4 | **Rejected — v2.4** (G4 absolute prohibition maintained) |
| [2026-06-05-kimi-session-complexity-trigger-undefined.md](./2026-06-05-kimi-session-complexity-trigger-undefined.md) | Kimi | §9 triggers | **Rejected — v2.4** (v2.2 definitional approach sufficient; numbers deferred to calibration) |
| [2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md](./2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md) | Kimi | §5 Evidence Hierarchy | Deferred — structural challenge, **Open Q5** (operational definition of "grounded" required before resolution) |
| [2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md](./2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md) | Grok + Sage | §3 Coherence Controller — DIVERSIFY trigger | **Partially incorporated — v2.4** (Mandatory Adversarial Reset integrated into Watchdog; Rival Sufficiency Requirement deferred — "≥50% of observations" needs operationalization) |
| [2026-06-05-deepseek-g4-escape-hatch.md](./2026-06-05-deepseek-g4-escape-hatch.md) | DeepSeek | §2 G4 Test Rigidity | **Incorporated — v2.4** (G4 absolute prohibition confirmed; Kimi escape hatch rejected) |
| [2026-06-06-claude-g01-init-procedure.md](./2026-06-06-claude-g01-init-procedure.md) | Claude | Handshake — session initialization | **Incorporated — v2.4** |
| [2026-06-06-claude-g03-watchdog-degradation-detection.md](./2026-06-06-claude-g03-watchdog-degradation-detection.md) | Claude | §3 Coherence Controller — convergence watchdog | **Incorporated — v2.4** (merged with Adversarial Reset) |
| [2026-06-06-claude-g04-gate-failure-sequencing.md](./2026-06-06-claude-g04-gate-failure-sequencing.md) | Claude | §2 Hard Gates — evaluation order and failure routing | **Incorporated — v2.4** |
| [2026-06-06-claude-g06-objection-register.md](./2026-06-06-claude-g06-objection-register.md) | Claude | §4 PSP — Objection Register schema | **Rejected — v2.3** (objections remain prose; formal schema deferred) |
| [2026-06-06-claude-g07-deserialization-protocol.md](./2026-06-06-claude-g07-deserialization-protocol.md) | Claude | §9 Session Continuity — deserialization procedure | **Incorporated — v2.4** |
| [2026-06-06-claude-g08-constraint-health-metric.md](./2026-06-06-claude-g08-constraint-health-metric.md) | Claude | §3 Coherence Controller — constraint health definition | **Incorporated — v2.3** (Option B: observable conditions) |
| [2026-06-06-gemini-diversify-structuring-routing-loophole.md](./2026-06-06-gemini-diversify-structuring-routing-loophole.md) | Gemini | §3 Coherence Controller — DIVERSIFY exit routing | **Incorporated — v2.3** (DIVERSIFY → STRUCTURING only) |
| [2026-06-06-grok-constraint-health-composite-metric.md](./2026-06-06-grok-constraint-health-composite-metric.md) | Grok | §3 Coherence Controller — constraint health metric | **Rejected — v2.3** (Option B chosen over Option A) |
| [2026-06-06-grok-state-compression-health-integration.md](./2026-06-06-grok-state-compression-health-integration.md) | Grok | §9 Session Continuity — State Compression required fields | **Incorporated — v2.4** |
| [2026-06-06-kimi-applicable-gates-bypass-vulnerability.md](./2026-06-06-kimi-applicable-gates-bypass-vulnerability.md) | Kimi | §3 Coherence Controller — "applicable gates" scope | **Incorporated — v2.5** (Option A: "applicable" → "all") |
| [2026-06-06-kimi-degraded-handoff-halt-required.md](./2026-06-06-kimi-degraded-handoff-halt-required.md) | Kimi | §9 Deserialization Procedure — degraded handoff handling | **Incorporated — v2.5** (three-option remediation; structural/orientational field distinction) |
| [2026-06-06-kimi-diversify-completion-undefined.md](./2026-06-06-kimi-diversify-completion-undefined.md) | Kimi | §3 Coherence Controller — DIVERSIFY exit criterion | **Incorporated — v2.5** (three-part completion condition; trigger-differentiated refinement deferred — Open Q4) |

### C++ Skeleton Reviews (2026-06-08)

| File | Source | Target | Status |
|------|--------|--------|--------|
| [2026-06-08-claude-chat-cpp-skeleton-review.md](./2026-06-08-claude-chat-cpp-skeleton-review.md) | Claude Chat | `charter-cpp` skeleton | **Applied — Fixes 1–4 (G2 route, optional fields, drift reset, differing_prediction)** |
| [2026-06-08-grok-cpp-skeleton-review.md](./2026-06-08-grok-cpp-skeleton-review.md) | Grok | `charter-cpp` skeleton | **Applied — Fixes 1–4 (confirmed independently)** |
| [2026-06-08-gemini-cpp-skeleton-review.md](./2026-06-08-gemini-cpp-skeleton-review.md) | Gemini | `charter-cpp` skeleton | **Applied — Fixes 1–4 (confirmed independently)** |
| [2026-06-08-kimi-cpp-skeleton-review.md](./2026-06-08-kimi-cpp-skeleton-review.md) | Kimi | `charter-cpp` skeleton | **Applied — K1 Option A (DIVERSIFY exit gate), K2 (watchdog bypass), K3 (G5 pre-check)** |
| [2026-06-08-gemini-b-cpp-skeleton-review.md](./2026-06-08-gemini-b-cpp-skeleton-review.md) | Gemini (run B) | `charter-cpp` skeleton | **Not applied — Q1 findings all incorrect (reviewing hypothetical code, not actual implementation)** |

### K1 DIVERSIFY Enforcement Reviews (2026-06-08)

| File | Source | Target | Status |
|------|--------|--------|--------|
| [2026-06-08-claude-chat-k1-diversify-enforcement-review.md](./2026-06-08-claude-chat-k1-diversify-enforcement-review.md) | Claude Chat | `CharterFSM::declare_diversify_complete()` | **Applied — capability token pattern implemented (Q3/Q4 fixes + token refactor)** |
| [2026-06-08-grok-k1-diversify-enforcement-review.md](./2026-06-08-grok-k1-diversify-enforcement-review.md) | Grok | `CharterFSM::declare_diversify_complete()` | **Applied — capability token pattern implemented (Q3/Q4 confirmed)** |
| [2026-06-08-kimi-k1-diversify-enforcement-review.md](./2026-06-08-kimi-k1-diversify-enforcement-review.md) | Kimi | `CharterFSM::declare_diversify_complete()` | **Applied — capability token pattern implemented (Q3/Q4 confirmed)** |
| [2026-06-08-gemini-k1-diversify-enforcement-review.md](./2026-06-08-gemini-k1-diversify-enforcement-review.md) | Gemini | `CharterFSM::declare_diversify_complete()` | **Applied — capability token pattern implemented (deciding vote; unanimous across all four reviewers)** |

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
