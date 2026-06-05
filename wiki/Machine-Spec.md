# Machine Specification v0.1

Formal specification of the Research Assistant Charter as an executable machine. All components, states, data types, and transitions made explicit.

**Charter version:** v2.2  
**Spec version:** 0.1 (draft)  
**Status:** Phase 1 complete — gap revelation. Phase 2 is simulation design.

---

## System Type

Finite State Machine + Type System + Memory Manager

---

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
    ├──► DIVERSIFY ──► PSP (§4) ──► GATE_CHECK
    │
    └──► RESTART ──► STRUCTURING (recompile)
```

---

## States

| State | Transitions | Gap |
|-------|-------------|-----|
| INIT | → STRUCTURING | G-01 HIGH: No initialization procedure |
| STRUCTURING | → GATE_CHECK, → STRUCTURING | None |
| GATE_CHECK | → DIVERSIFY, → CONVERGE, → RESTART | G-04 MEDIUM: Failure sequencing undefined |
| DIVERSIFY | → GATE_CHECK, → STRUCTURING | G-02 HIGH: Trigger undefined for LLM execution |
| CONVERGE | → OUTPUT, → INIT | None |
| RESTART | → STRUCTURING | G-03 HIGH: No watchdog / degradation detection |
| OUTPUT | → INIT, → STRUCTURING | None |

See [FSM-States](./FSM-States.md) for full state descriptions and gap details.

---

## Components

| ID | Name | Ref | Type | Gaps |
|----|------|-----|------|------|
| SC | Structuring Contract | §1 | PROCESSOR | None |
| HG | Hard Gates | §2 | VALIDATOR | G-04 |
| CC | Coherence Controller | §3 | STATE_CONTROLLER | G-02, G-08 |
| PSP | Productive Skepticism Protocol | §4 | PROCESSOR | G-06 |
| EH | Evidence Hierarchy | §5 | TYPE_SYSTEM | G-05 |
| SCP | Session Continuity Protocol | §9 | MEMORY_MANAGER | G-07 |

See [Components](./Components.md) for typed inputs, outputs, and full gap details.

---

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

See [Data-Types](./Data-Types.md) for schemas.

---

## Gap Summary

| ID | Severity | Component | Title |
|----|----------|-----------|-------|
| G-01 | HIGH | FSM | No Initialization Procedure |
| G-02 | HIGH | CC §3 | DIVERSIFY Trigger Undefined for LLM Execution |
| G-03 | HIGH | FSM | No Watchdog / Degradation Detection |
| G-04 | MEDIUM | HG §2 | Gate Failure Sequencing Undefined |
| G-05 | MEDIUM | EH §5 | Evidence Hierarchy Has Wrong Dimensionality |
| G-06 | MEDIUM | PSP §4 | Objection Register Not Defined as Data Structure |
| G-07 | LOW | SCP §9 | No Deserialization Protocol |
| G-08 | LOW | CC §3 | "Constraint Health" Not Measurable |

See [Gap-Analysis](./Gap-Analysis.md) for descriptions, failure modes, and proposed resolutions.

---

## Missing Subsystems

These are required for full machine execution but not specified in the charter:

- INIT procedure (explicit boot sequence)
- Watchdog / degradation detector (agreement drift detection)
- Objection Register schema (typed, persistent, queryable)
- State Compression deserialization protocol
- Gate failure dependency graph
- Constraint health metric

---

## Phase Roadmap

| Phase | Description | Status |
|-------|-------------|--------|
| 1 | Gap revelation — translate prose to spec, flag underspecified elements | Complete |
| 2 | Simulation design — run session transcripts through spec to surface remaining gaps | Not started |
| 3 | Build — validated spec becomes agent architecture | Not started |
