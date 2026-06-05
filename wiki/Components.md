# Components

Six charter institutions mapped as engineering components with typed inputs, outputs, and gap annotations.

---

## SC — Structuring Contract

**Charter reference:** §1  
**Component type:** PROCESSOR

**Inputs**
- `raw_claim` — unstructured idea or hypothesis from operator
- `operator_context` — session framing, prior assumptions

**Outputs**
- `structured_artifact` — compiled claim with gates-ready spec

**Specification**

Transforms unstructured idea into an artifact containing:
- Central claim: ≤3 sentences, bounded, falsifiable
- Operational definitions: observables + metrics + measurement windows
- Test specification: conditions, parameters, stopping rules
- Success/failure criteria: ≥2 numeric thresholds set BEFORE running

**Gaps:** None identified.

---

## HG — Hard Gates

**Charter reference:** §2  
**Component type:** VALIDATOR

**Inputs**
- `structured_artifact`

**Outputs**
- `gate_result[PASS|FAIL]`
- `gate_id`
- `defect_list`

**Specification**

- G1 Numeric completeness — ≥2 numeric thresholds that reject the claim
- G2 Bounded scope — claim is short, specific, scope-limited
- G3 Operational definitions — every key term maps to a metric or procedure
- G4 Test rigidity — thresholds cannot be adjusted after seeing results
- G5 Mechanism status declared — mechanism stated and distinguished from evidence, OR declared unknown with a discriminating test proposed

**Gaps**

- `G-04 · MEDIUM` — Gate failure sequencing undefined. Partial pass state unspecified. No defined order of gate application. No short-circuit rule: does G1 failure skip G2–G5?

---

## CC — Coherence Controller

**Charter reference:** §3  
**Component type:** STATE_CONTROLLER

**Inputs**
- `gate_result`
- `constraint_health`
- `session_context`

**Outputs**
- `state_transition[CONVERGE|DIVERSIFY|RESTART]`

**Specification**

Monitors constraint health during structuring. Decides:
- CONVERGE: all gates pass, all objections tested, no untested objection with a viable scoped test remains
- DIVERSIFY: inject competing explanations, skeptical probes, assumption challenges
- RESTART: structural flaw detected; recompile with explicit defect list

**Gaps**

- `G-02 · HIGH` — DIVERSIFY trigger undefined for LLM execution. "This feels obviously right" is anthropomorphic. See [OPEN_QUESTIONS.md Q2](../OPEN_QUESTIONS.md).
- `G-08 · LOW` — "Constraint health" not defined as a measurable quantity. Currently a metaphor doing the work of a metric.
- No tie-breaking rule when multiple state transitions are valid simultaneously.

---

## PSP — Productive Skepticism Protocol

**Charter reference:** §4  
**Component type:** PROCESSOR

**Inputs**
- `current_proposal`
- `session_history`

**Outputs**
- `objection_set`
- `assumption_audit`
- `calibration_result`

**Specification**

Six checks applied before accepting any claim:
1. Convergence Check — ≥2 competing explanations explored?
2. Assumption Audit — which assumptions are being treated as facts?
3. Failure Mode Probe — how would this break in practice?
4. Scope Boundary Test — where does this claim stop being valid?
5. Mechanism Challenge — can we explain HOW, not just that it does?
6. Calibration Rule — generate at least one substantive objection

Plus: Skepticism Termination Rule — scrutiny terminates when all objections stated, assigned tests or declared untestable, and no new untested objection in scope.

**Gaps**

- `G-06 · MEDIUM` — Objection Register not defined as a data structure. Objections are produced but not typed or persistently tracked across state transitions. The Skepticism Termination Rule requires knowing which objections have been addressed — but there is no specified register to check against.

---

## EH — Evidence Hierarchy

**Charter reference:** §5  
**Component type:** TYPE_SYSTEM

**Inputs**
- `claim`
- `supporting_material`

**Outputs**
- `evidence_level[E1–E5]`

**Specification**

- E5: Fully reproducible — code + data + tests + documentation + independent verification
- E4: Methods-grade artifact — robustness checks + negative controls + preregistered protocol
- E3: Reproducible experiment or simulation with clear pass/fail outcomes
- E2: Established domain knowledge — explicitly cited, ≥2 independent verifiable sources (v3.0 draft)
- E1: Speculation — must include named IV, named DV, and numeric threshold for a minimal decisive test

No claim may be described as E3+ without a structured artifact and test results.

**Gaps**

- `G-05 · MEDIUM` — Linear ladder collapses reproducibility and empirical grounding into one axis. A reproducible simulation with invalid assumptions outranks a non-reproducible empirical observation. Goodhart's Law incentive: optimize for reproducibility at expense of empirical validity. See [OPEN_QUESTIONS.md Q1](../OPEN_QUESTIONS.md).
- E2 boundary criteria — hallucinated citations not excluded under v2.2 (one-source rule). v3.0 draft adds two-source requirement.
- No upgrade/downgrade protocol when evidence level changes mid-session.

---

## SCP — Session Continuity Protocol

**Charter reference:** §9  
**Component type:** MEMORY_MANAGER

**Inputs**
- `session_state`
- `trigger_condition`

**Outputs**
- `state_compression`

**Specification**

Serializes session state into a State Compression on `/compress` or trigger conditions:
- Topic shift — primary claim/artifact/objective changes to a different one
- Milestone — gate status changes, artifact completed, or test specification finalized
- Session complexity elevated — ≥2 active claims, artifacts, or unresolved objections tracked simultaneously without a State Compression since the earliest was opened

State Compression must contain: active claims + evidence levels, gate status, decisions + reasoning, skeptical residue, next step, assumptions modified this session.

**Gaps**

- `G-07 · LOW` — No deserialization protocol. State Compression is defined as a serialization output but re-ingestion into a new session is unspecified. "Paste it in" is a human instruction, not a machine protocol.
- `G-08` — Numeric thresholds absent in v2.2; trigger conditions rely on judgment for "elevated complexity." See [OPEN_QUESTIONS.md Q3](../OPEN_QUESTIONS.md).
- No checksum or integrity verification on State Compression output.
