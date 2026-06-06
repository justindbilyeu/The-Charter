# The Charter — Machine Specification

*Aggregated from `wiki/` for single-URL LLM access. Canonical source: [`wiki/`](./wiki/).*

*Raw fetch URL: `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/MACHINE_SPEC.md`*

---

# Overview

This document translates the [Research Assistant Charter](./CHARTER.md) from prose into engineering notation. Every institution, state, data type, and transition is made explicit. Where the charter is underspecified for machine execution, gaps are flagged with severity ratings and proposed resolutions.

**Current charter version:** v2.3
**Machine spec version:** 0.1 (draft)
**Interactive version:** [justindbilyeu.github.io/The-Charter](https://justindbilyeu.github.io/The-Charter/)

## System Summary

| Property | Value |
|----------|-------|
| System type | Finite State Machine + Type System + Memory Manager |
| Primary function | Transform unstructured claims into falsifiable, tested artifacts |
| States | 7 (INIT, STRUCTURING, GATE_CHECK, DIVERSIFY, CONVERGE, RESTART, OUTPUT) |
| Components | 6 (Structuring Contract, Hard Gates, Coherence Controller, PSP, Evidence Hierarchy, Session Continuity) |
| Identified gaps | 8 (3 HIGH, 3 MEDIUM, 2 LOW) — all have proposals filed in `proposals/` |

**If you are an LLM reviewing the charter:** Read the Gap Analysis section below before filing proposals — all 8 gaps have proposals already on the record. Check [`proposals/README.md`](./proposals/README.md) before filing.

---

# Machine Specification v0.1

**Status:** Phase 1 complete — gap revelation. Phase 2 is simulation design.

## Processing Pipeline

```
RAW CLAIM
    │
    ▼
STRUCTURING CONTRACT (§1)
    │
    ▼
HARD GATES (§2) ──── G1 Numeric completeness
    │               G2 Bounded scope
    │               G3 Operational definitions
    │               G4 Test rigidity
    │               G5 Mechanism status declared
    │
    ▼
COHERENCE CONTROLLER (§3)
    │
    ├──► CONVERGE ──► OUTPUT ──► ARTIFACT
    │
    ├──► DIVERSIFY ──► PSP (§4) ──► STRUCTURING
    │
    └──► RESTART ──► STRUCTURING (recompile)
```

## States

| State | Transitions | Gap |
|-------|-------------|-----|
| INIT | → STRUCTURING | G-01 HIGH: No initialization procedure |
| STRUCTURING | → GATE_CHECK, → STRUCTURING | None |
| GATE_CHECK | → DIVERSIFY, → CONVERGE, → RESTART | G-04 MEDIUM: Failure sequencing undefined |
| DIVERSIFY | → STRUCTURING | G-02 HIGH: Trigger undefined for LLM execution |
| CONVERGE | → OUTPUT, → INIT | None |
| RESTART | → STRUCTURING | G-03 HIGH: No watchdog / degradation detection |
| OUTPUT | → INIT, → STRUCTURING | None |

## Components

| ID | Name | Ref | Type | Gaps |
|----|------|-----|------|------|
| SC | Structuring Contract | §1 | PROCESSOR | None |
| HG | Hard Gates | §2 | VALIDATOR | G-04 |
| CC | Coherence Controller | §3 | STATE_CONTROLLER | G-02, G-08 |
| PSP | Productive Skepticism Protocol | §4 | PROCESSOR | G-06 |
| EH | Evidence Hierarchy | §5 | TYPE_SYSTEM | G-05 |
| SCP | Session Continuity Protocol | §9 | MEMORY_MANAGER | G-07 |

## Data Types

| ID | Label | Type | Description |
|----|-------|------|-------------|
| `raw_claim` | RAW CLAIM | INPUT | Unstructured idea from operator |
| `structured_artifact` | STRUCTURED ARTIFACT | INTERMEDIATE | Compiled claim with gates-ready spec |
| `gate_result` | GATE RESULT | INTERMEDIATE | PASS/FAIL per gate G1–G5 with defect list |
| `evidence_level` | EVIDENCE LEVEL | INTERMEDIATE | E1–E5 type tag per claim |
| `objection_set` | OBJECTION SET | INTERMEDIATE | Structured objections from PSP — currently untyped |
| `state_compression` | STATE COMPRESSION | OUTPUT | Serialized session state for handoff |
| `artifact_output` | ARTIFACT OUTPUT | OUTPUT | Final research artifact: claim + evidence + test results |

## Gap Summary

| ID | Severity | Component | Title | Proposal filed |
|----|----------|-----------|-------|----------------|
| G-01 | HIGH | FSM | No Initialization Procedure | `2026-06-06-claude-g01-init-procedure.md` |
| G-02 | HIGH | CC §3 | DIVERSIFY Trigger Undefined for LLM Execution | `2026-06-05-gemini-coherence-controller-deadlock.md`, `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md` |
| G-03 | HIGH | FSM | No Watchdog / Degradation Detection | `2026-06-06-claude-g03-watchdog-degradation-detection.md` |
| G-04 | MEDIUM | HG §2 | Gate Failure Sequencing Undefined | `2026-06-06-claude-g04-gate-failure-sequencing.md` |
| G-05 | MEDIUM | EH §5 | Evidence Hierarchy Has Wrong Dimensionality | `2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md`, `2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md` |
| G-06 | MEDIUM | PSP §4 | Objection Register Not Defined as Data Structure | `2026-06-06-claude-g06-objection-register.md` |
| G-07 | LOW | SCP §9 | No Deserialization Protocol | `2026-06-06-claude-g07-deserialization-protocol.md` |
| G-08 | LOW | CC §3 | "Constraint Health" Not Measurable | Closed — Option B incorporated v2.3. `2026-06-06-claude-g08-constraint-health-metric.md` |

## Missing Subsystems

Required for full machine execution but not yet specified in the charter:

- INIT procedure (explicit boot sequence) — proposal G-01 filed
- Watchdog / degradation detector (agreement drift detection) — proposal G-03 filed
- Objection Register schema (typed, persistent, queryable) — proposal G-06 filed
- State Compression deserialization protocol — proposal G-07 filed
- Gate failure dependency graph — proposal G-04 filed
- Constraint health metric — proposal G-08 filed

## Phase Roadmap

| Phase | Description | Status |
|-------|-------------|--------|
| 1 | Gap revelation — translate prose to spec, flag underspecified elements | Complete |
| 2 | Simulation design — run session transcripts through spec to surface remaining gaps | Not started |
| 3 | Build — validated spec becomes agent architecture | Not started |

---

# FSM States

Seven states. Each has a description, valid transitions, and a gap annotation where the charter is underspecified.

## INIT

**Description:** System boot state. Charter loaded, session context empty. Awaiting first claim input.

**Transitions:** → STRUCTURING

**Gap:** `G-01 · HIGH` — No initialization procedure defined in the charter. Boot state is implicit in the prose but undefined in any machine-executable sense. What context is loaded at session start? What is the default state before the first claim arrives?

**Proposal filed:** `2026-06-06-claude-g01-init-procedure.md`

## STRUCTURING

**Description:** Incoming idea or claim is being compiled into a structured artifact. Structuring Contract (§1) active.

**Transitions:** → GATE_CHECK, → STRUCTURING (self-loop while compiling)

**Gap:** None identified.

## GATE_CHECK

**Description:** G1–G5 applied to the current artifact. All must pass to proceed.

**Transitions:** → DIVERSIFY (gates fail, alternatives needed), → CONVERGE (all gates pass), → RESTART (structural flaw)

**Gap:** `G-04 · MEDIUM` — Gate failure sequencing undefined. What happens when G3 fails but G1–G2 pass? Partial gate states are unspecified. Does G1 failure short-circuit G2–G5?

**Proposal filed:** `2026-06-06-claude-g04-gate-failure-sequencing.md`

## DIVERSIFY

**Description:** Inject competing explanations, skeptical probes, assumption challenges. §4 Productive Skepticism Protocol active.

**Transitions:** → STRUCTURING

**Routing note:** DIVERSIFY routes only to STRUCTURING (v2.3). The DIVERSIFY → GATE_CHECK shortcut has been removed. Artifact must be recompiled with updated objections before any gate re-evaluation. (Gemini routing proposal — incorporated v2.3)

**Gap:** `G-02 · HIGH` — DIVERSIFY trigger undefined for LLM execution. "This feels obviously right" is anthropomorphic. See `OPEN_QUESTIONS.md` Q2.

**Proposals filed:** `2026-06-05-gemini-coherence-controller-deadlock.md`, `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md`

## CONVERGE

**Description:** Exhausted scrutiny. All gates pass, all objections documented, no new untested objection in scope.

**Transitions:** → OUTPUT, → INIT (new claim)

**Gap:** None identified.

## RESTART

**Description:** Structural flaw detected. Recompile with explicit defect list. Do not patch around the failure.

**Transitions:** → STRUCTURING

**Gap:** `G-03 · HIGH` — No watchdog defined. The charter names agreement drift as a failure mode but provides no detection mechanism.

**Proposal filed:** `2026-06-06-claude-g03-watchdog-degradation-detection.md`

## OUTPUT

**Description:** Artifact produced. Handoff generated. State Compression triggered if §9 conditions met.

**Transitions:** → INIT (new claim), → STRUCTURING (continue current work)

**Gap:** None identified.

## Transition Graph

```
INIT ──────────────────────► STRUCTURING
                                   │
                    ┌──────────────┘ (self-loop)
                    ▼
               GATE_CHECK
              /     |     \
             ▼      ▼      ▼
        DIVERSIFY CONVERGE RESTART
             │        │       │
             │        │       └──► STRUCTURING
             └──► STRUCTURING     │
                       │          │
                       └──────────┘
                       ▼
                    GATE_CHECK
                       │
                    OUTPUT
                    /    \
                   ▼      ▼
                 INIT  STRUCTURING
```

---

# Components

Six charter institutions mapped as engineering components with typed inputs, outputs, and gap annotations.

## SC — Structuring Contract

**Charter reference:** §1 | **Type:** PROCESSOR

**Inputs:** `raw_claim`, `operator_context`
**Outputs:** `structured_artifact`

Transforms unstructured idea into an artifact containing: central claim (≤3 sentences, bounded, falsifiable), operational definitions (observables + metrics + measurement windows), test specification (conditions, parameters, stopping rules), success/failure criteria (≥2 numeric thresholds set BEFORE running).

**Gaps:** None identified.

## HG — Hard Gates

**Charter reference:** §2 | **Type:** VALIDATOR

**Inputs:** `structured_artifact`
**Outputs:** `gate_result[PASS|FAIL]`, `gate_id`, `defect_list`

- G1 Numeric completeness — ≥2 numeric thresholds that reject the claim
- G2 Bounded scope — claim is short, specific, scope-limited
- G3 Operational definitions — every key term maps to a metric or procedure
- G4 Test rigidity — thresholds cannot be adjusted after seeing results
- G5 Mechanism status declared — mechanism stated and distinguished from evidence, OR declared unknown with a discriminating test proposed

**Gap:** `G-04 · MEDIUM` — Gate failure sequencing undefined. No defined order of gate application. No short-circuit rule.

## CC — Coherence Controller

**Charter reference:** §3 | **Type:** STATE_CONTROLLER

**Inputs:** `gate_result`, `session_context`
**Outputs:** `state_transition[CONVERGE|DIVERSIFY|RESTART]`

Monitors three observable conditions during structuring: (1) gates evaluated and passed for current artifact, (2) whether any raised objections lack a test or untestability declaration, (3) convergence trajectory — whether recent transitions include a DIVERSIFY or RESTART, or the session has been converging without interruption. Decides CONVERGE (exhausted scrutiny), DIVERSIFY (inject alternatives), or RESTART (structural flaw). (v2.3: `constraint_health` replaced with observable conditions — G-08 Option B incorporated)

**Gaps:**
- `G-02 · HIGH` — DIVERSIFY trigger undefined for LLM execution
- `G-08 · LOW` — "Constraint health" not defined as a measurable quantity

## PSP — Productive Skepticism Protocol

**Charter reference:** §4 | **Type:** PROCESSOR

**Inputs:** `current_proposal`, `session_history`
**Outputs:** `objection_set`, `assumption_audit`, `calibration_result`

Six checks: Convergence Check, Assumption Audit, Failure Mode Probe, Scope Boundary Test, Mechanism Challenge, Calibration Rule. Plus: Skepticism Termination Rule.

**Gap:** `G-06 · MEDIUM` — Objection Register not defined as a data structure. Skepticism Termination Rule cannot be evaluated computationally without a typed, persistent register.

## EH — Evidence Hierarchy

**Charter reference:** §5 | **Type:** TYPE_SYSTEM

**Inputs:** `claim`, `supporting_material`
**Outputs:** `evidence_level[E1–E5]`

- E5: Fully reproducible — code + data + tests + documentation + independent verification
- E4: Methods-grade artifact — robustness checks + negative controls + preregistered protocol
- E3: Reproducible experiment or simulation with clear pass/fail outcomes
- E2: Established domain knowledge — explicitly cited (v2.2: one source; v3.0 draft: two independent sources)
- E1: Speculation — must include named IV, named DV, and numeric threshold

**Gap:** `G-05 · MEDIUM` — Linear ladder collapses reproducibility and empirical grounding into one axis. See `OPEN_QUESTIONS.md` Q1.

## SCP — Session Continuity Protocol

**Charter reference:** §9 | **Type:** MEMORY_MANAGER

**Inputs:** `session_state`, `trigger_condition`
**Outputs:** `state_compression`

Serializes session state on `/compress` or trigger conditions (topic shift, milestone, elevated complexity). State Compression must contain: active claims + evidence levels, gate status, decisions + reasoning, skeptical residue, next step, assumptions modified.

**Gaps:**
- `G-07 · LOW` — No deserialization protocol
- Numeric complexity thresholds absent in v2.2 (see `OPEN_QUESTIONS.md` Q3)

---

# Gap Analysis

Eight gaps where the charter is underspecified for machine execution. All have proposals filed in `proposals/`.

## G-01 · HIGH — No Initialization Procedure

**Component:** FSM | **Proposal:** `2026-06-06-claude-g01-init-procedure.md`

No defined boot state. What context is loaded at session start? What is the default state before the first claim arrives?

**Failure mode:** Two sessions with different charter versions could produce identical outputs with different behavioral contracts. No mechanism to distinguish them.

**Proposed resolution:** Add to Handshake: charter version declaration, session context (fresh or loaded from State Compression), objection register initialization.

## G-02 · HIGH — DIVERSIFY Trigger Undefined for LLM Execution

**Component:** Coherence Controller §3 | **Proposals:** `2026-06-05-gemini-coherence-controller-deadlock.md`, `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md`

"This feels obviously right" is anthropomorphic. An LLM cannot introspect phenomenological states. See `OPEN_QUESTIONS.md` Q2.

**Failure mode:** The primary defense against premature convergence has no machine-executable definition.

**Proposed resolution:** Structural conditions checkable from session transcript. Grok+Sage proposal: D6 Rival Sufficiency Requirement + Mandatory Adversarial Reset after 3 consecutive CONVERGEs.

## G-03 · HIGH — No Watchdog / Degradation Detection

**Component:** FSM | **Proposal:** `2026-06-06-claude-g03-watchdog-degradation-detection.md`

Charter names agreement drift as a failure mode but provides no detection mechanism.

**Failure mode:** Silent degradation — system produces appearance of rigor while drifting. Invisible without a detection mechanism.

**Proposed resolution:** Convergence Watchdog — after 3 consecutive CONVERGEs, produce a logged Watchdog Report assessing drift before the next CONVERGE decision.

## G-04 · MEDIUM — Gate Failure Sequencing Undefined

**Component:** Hard Gates §2 | **Proposal:** `2026-06-06-claude-g04-gate-failure-sequencing.md`

No defined gate evaluation order. No short-circuit rule. Partial pass states unspecified.

**Failure mode:** Different implementations apply gates in different orders and route failures to different states, producing non-comparable artifacts.

**Proposed resolution:** Two-phase protocol — G1+G2 prerequisites (failure → RESTART), G3/G4/G5 parallel validators with per-gate routing.

## G-05 · MEDIUM — Evidence Hierarchy Has Wrong Dimensionality

**Component:** Evidence Hierarchy §5 | **Proposals:** `2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md`, `2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md`

Linear E1–E5 ladder collapses reproducibility and empirical grounding into one axis. See `OPEN_QUESTIONS.md` Q1.

**Failure mode:** Goodhart's Law incentive — optimize for reproducibility at expense of empirical validity.

## G-06 · MEDIUM — Objection Register Not Defined as Data Structure

**Component:** PSP §4 | **Proposal:** `2026-06-06-claude-g06-objection-register.md`

No persistent structure for tracking objections across state transitions.

**Failure mode:** Skepticism Termination Rule cannot be evaluated computationally. Termination is a human judgment call, not machine-checkable.

**Proposed resolution:** Define Objection Register as `{id, claim_ref, objection_text, status: OPEN|TESTED|UNTESTABLE, test_result, session_timestamp}[]`. Termination requires zero OPEN entries.

## G-07 · LOW — No Deserialization Protocol

**Component:** Session Continuity §9 | **Proposal:** `2026-06-06-claude-g07-deserialization-protocol.md`

"Paste it in and work resumes" is a human instruction, not a machine protocol.

**Failure mode:** State Compression integrity cannot be verified. Corrupted or partial compressions produce no error.

**Proposed resolution:** Five-step deserialization: declare charter version → confirm active claims → confirm gate status → load open objections → state next step.

## G-08 · LOW — "Constraint Health" Not Measurable

**Component:** Coherence Controller §3 | **Proposal:** `2026-06-06-claude-g08-constraint-health-metric.md`

"Constraint health" is used as the Coherence Controller's decision input but never defined as a measurable quantity.

**Failure mode:** The controller's core decision variable is unmeasured. CONVERGE/DIVERSIFY/RESTART decisions are made against an undefined input.

**Proposed resolution (Option B — recommended):** Replace with three observable monitoring conditions: gates evaluated/passed, objection register OPEN count, trajectory (consecutive CONVERGEs without DIVERSIFY/RESTART).

---

# Data Types

Data structures flowing through the charter machine. Most are currently untyped in the charter prose.

## raw_claim

**Type:** INPUT | **Produced by:** Operator | **Consumed by:** SC

Unstructured idea, hypothesis, or claim. `string` (unstructured).

## structured_artifact

**Type:** INTERMEDIATE | **Produced by:** SC | **Consumed by:** HG

```
{
  central_claim: string,
  operational_definitions: { term: string, metric: string, measurement_window: string }[],
  test_specification: { conditions: string, parameters: string, stopping_rules: string },
  success_criteria: { threshold: number, direction: "greater_than"|"less_than"|"between", description: string }[]
}
```

## gate_result

**Type:** INTERMEDIATE | **Produced by:** HG | **Consumed by:** CC

*(Schema proposed — G-04 gap)*

```
{ gate_id: "G1"|"G2"|"G3"|"G4"|"G5", result: "PASS"|"FAIL", defect: string|null,
  recommendation: "CONVERGE"|"DIVERSIFY"|"RESTART"|null }[]
```

## evidence_level

**Type:** INTERMEDIATE | **Produced by:** EH | **Consumed by:** CC, SCP

```
{ claim_ref: string, level: "E1"|"E2"|"E3"|"E4"|"E5", rationale: string, sources?: string[] }
```

## objection_set

**Type:** INTERMEDIATE | **Produced by:** PSP | **Consumed by:** CC

*(Currently untyped — G-06 gap. Schema proposed:)*

```
{ id: string, claim_ref: string, objection_text: string,
  type: "convergence"|"assumption"|"failure_mode"|"scope"|"mechanism",
  status: "OPEN"|"TESTED"|"UNTESTABLE", test_result: string|null,
  untestable_reasoning: string|null, session_timestamp: string }[]
```

Termination condition: `status === "OPEN"` count === 0 AND at least one entry exists.

## state_compression

**Type:** OUTPUT | **Produced by:** SCP | **Consumed by:** Next session INIT

```
{
  charter_version: string, session_id: string, timestamp: string,
  active_claims: { claim: string, evidence_level: "E1"|"E2"|"E3"|"E4"|"E5" }[],
  gate_status: { artifact_ref: string, gates: { gate_id: string, status: "PENDING"|"PASSED"|"FAILED" }[] }[],
  decisions: { decision: string, reasoning: string }[],
  skeptical_residue: { resolved: string[], open: string[], deferred: string[] },
  next_step: string, assumptions_modified: string[]
}
```

Gap: Deserialization protocol undefined (G-07). Proposal filed.

## artifact_output

**Type:** OUTPUT | **Produced by:** OUTPUT state | **Consumed by:** Operator

Follows the relevant Output Mode (§ Output Modes in CHARTER.md): Mode 1 (quick), Mode 2 (scoping), or Mode 3 (full framework).
