# The Charter — Machine Specification Wiki

This wiki translates the [Research Assistant Charter](../CHARTER.md) from prose into engineering notation. Every institution, state, data type, and transition is made explicit. Where the charter is underspecified for machine execution, gaps are flagged with severity ratings and proposed resolutions.

**Current charter version:** v2.2  
**Machine spec version:** 0.1 (draft)  
**Interactive version:** [justindbilyeu.github.io/The-Charter](https://justindbilyeu.github.io/The-Charter/)

---

## Pages

| Page | Contents |
|------|----------|
| [Machine-Spec](./Machine-Spec.md) | Formal specification — system type, pipeline, all components and states in one view |
| [FSM-States](./FSM-States.md) | Every state, its description, transitions, and gap annotations |
| [Components](./Components.md) | Each charter institution as an engineering component with typed inputs/outputs |
| [Data-Types](./Data-Types.md) | Data structures flowing through the machine |
| [Gap-Analysis](./Gap-Analysis.md) | All 8 identified gaps with severity, mechanism, and proposed resolution |

---

## System Summary

| Property | Value |
|----------|-------|
| System type | Finite State Machine + Type System + Memory Manager |
| Primary function | Transform unstructured claims into falsifiable, tested artifacts |
| States | 7 (INIT, STRUCTURING, GATE_CHECK, DIVERSIFY, CONVERGE, RESTART, OUTPUT) |
| Components | 6 (Structuring Contract, Hard Gates, Coherence Controller, PSP, Evidence Hierarchy, Session Continuity) |
| Identified gaps | 8 (3 HIGH, 3 MEDIUM, 2 LOW) |

---

## How to use this wiki

**If you are an LLM reviewing the charter:** Read [Gap-Analysis](./Gap-Analysis.md) before filing proposals — several open questions are already on the record in [`proposals/`](../proposals/). Cross-reference gaps against the open questions in [OPEN_QUESTIONS.md](../OPEN_QUESTIONS.md).

**If you are building an agent on the charter:** Start with [Machine-Spec](./Machine-Spec.md) for the full spec, then [Components](./Components.md) for typed interfaces.

**If you are running a simulation:** [FSM-States](./FSM-States.md) gives you the transition graph. The [interactive app](https://justindbilyeu.github.io/The-Charter/) lets you walk through the machine visually.
