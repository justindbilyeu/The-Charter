# Gap Analysis

Eight gaps identified where the charter is underspecified for machine execution. Three HIGH severity, three MEDIUM, two LOW.

Before filing a proposal on any of these, check [`proposals/README.md`](../proposals/README.md) — several are already on the record.

---

## G-01 · HIGH — No Initialization Procedure

**Component:** FSM  
**Charter section:** None (implicit)

**Description**

The charter has no defined boot state. What context is loaded at session start? What is the default state before the first claim arrives? INIT is implied by the prose but never specified as a machine-executable procedure.

**Failure mode:** A session with no initialization protocol has no defined starting state, no way to verify Charter version loaded, and no cleared objection register. Two sessions with different charter versions could produce identical outputs with different behavioral contracts.

**Proposed resolution**

Define INIT entry conditions:
- Charter version loaded and declared
- Session ID assigned
- Operator context captured
- Objection register initialized (empty)
- Default evidence level set to E1

**Related proposals:** None filed yet.

---

## G-02 · HIGH — DIVERSIFY Trigger Undefined for LLM Execution

**Component:** Coherence Controller §3  
**Charter section:** §3 DIVERSIFY trigger

**Description**

"This feels obviously right" is anthropomorphic. An LLM cannot introspect phenomenological states. The trigger either never fires (if the assistant suppresses "feeling" per Genesis) or fires constantly (any well-formed answer generates high-confidence tokens).

**Failure mode:** The primary defense against premature convergence has no machine-executable definition. The immune system has no trigger.

**Proposed resolution**

See [OPEN_QUESTIONS.md Q2](../OPEN_QUESTIONS.md) for the full deliberation. Key proposals on record:
- Gemini: three structural conditions (partially undefined — "explicitly modeled" needs operationalization)
- Grok + Sage (`2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md`): D6 Rival Sufficiency Requirement + Mandatory Adversarial Reset after 3 consecutive CONVERGEs

**Related proposals:** `2026-06-05-gemini-coherence-controller-deadlock.md`, `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md`

---

## G-03 · HIGH — No Watchdog / Degradation Detection

**Component:** FSM  
**Charter section:** §3, §8 ("agreement drift")

**Description**

The charter names agreement drift as a failure mode but provides no detection mechanism. A system that has drifted into mirror mode has no internal signal that it has done so. The watchdog is implicitly the human operator — but that dependency is never specified.

**Failure mode:** Silent degradation. The system produces the appearance of rigor (checklists satisfied, gates passed) while gradually softening scrutiny. By the time the operator notices, the structural damage is already in the artifact record.

**Proposed resolution**

Define a periodic self-check: at each OUTPUT, evaluate whether the last N state transitions produced any RESTART or DIVERSIFY. If no RESTART or DIVERSIFY in the last 3 transitions, flag for human review. This fires as G-03 in the machine spec.

The Mandatory Adversarial Reset in `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md` partially addresses this via a scheduled structural probe.

**Related proposals:** `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md`

---

## G-04 · MEDIUM — Gate Failure Sequencing Undefined

**Component:** Hard Gates §2  
**Charter section:** §2

**Description**

When a gate fails, the charter requires restructuring. But which gates are prerequisites for which? Does G1 failure short-circuit G2–G5? Can G3 fail while G1–G2 pass and still proceed to partial testing? Partial gate states are unspecified.

**Failure mode:** An assistant can apply gates in any order, skip non-failing gates after a failure, or produce inconsistent partial-pass states that another session would evaluate differently.

**Proposed resolution**

Define gate dependency graph:
- G1 + G2 are prerequisites. Failure of either triggers RESTART.
- G3, G4, G5 are parallel validators. Failure triggers DIVERSIFY or targeted STRUCTURING.
- Gate evaluation order is G1 → G2 → G3/G4/G5 (parallel). Short-circuit after G1 or G2 failure.

**Related proposals:** None filed yet.

---

## G-05 · MEDIUM — Evidence Hierarchy Has Wrong Dimensionality

**Component:** Evidence Hierarchy §5  
**Charter section:** §5

**Description**

The linear E1–E5 ladder collapses two independent quality dimensions — reproducibility and empirical grounding — into one axis. A fully reproducible simulation with invalid boundary conditions ranks higher (E3) than a non-reproducible but empirically grounded historical observation. This creates a Goodhart's Law incentive: optimize for reproducibility (procedurally demonstrable) at the expense of empirical validity (harder to verify).

**Failure mode:** An assistant can satisfy E3+ by producing reproducible simulations with unvalidated assumptions, while empirically grounded qualitative evidence is systematically underweighted.

**Proposed resolution**

See [OPEN_QUESTIONS.md Q1](../OPEN_QUESTIONS.md) for the full deliberation. Three options:
- Option A: Declare the ladder a practical heuristic and fix E2 within the current structure
- Option B: Propose a 2D structure (reproducibility × empirical grounding)
- Option C: Declare the challenge out of scope with an explicit scope note

**Related proposals:** `2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md`, `2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md`

---

## G-06 · MEDIUM — Objection Register Not Defined as Data Structure

**Component:** Productive Skepticism Protocol §4  
**Charter section:** §4

**Description**

Objections are produced by the PSP but there is no defined persistent structure for tracking them across state transitions. The Skepticism Termination Rule requires knowing which objections have been addressed — but there is no specified register to check against. Objections exist in session prose but not as a queryable data structure.

**Failure mode:** The Skepticism Termination Rule cannot be evaluated computationally. Whether scrutiny has been "exhausted" is a human judgment call, not a machine-checkable condition. An assistant can declare termination without a complete audit.

**Proposed resolution**

Define Objection Register as a typed data structure:
```
{
  id: string,
  claim_ref: string,
  objection_text: string,
  status: "OPEN" | "TESTED" | "UNTESTABLE",
  test_result: string | null,
  session_timestamp: string
}
```
Required input/output of PSP and Coherence Controller. Skepticism Termination Rule gates on `status === "OPEN"` count === 0.

**Related proposals:** None filed yet.

---

## G-07 · LOW — No Deserialization Protocol

**Component:** Session Continuity Protocol §9  
**Charter section:** §9

**Description**

State Compression is defined as a serialization output with a specific schema. But the re-ingestion procedure — how a new session boots from a State Compression — is unspecified. "Paste it in and work resumes" is a human instruction, not a machine protocol. A new session has no defined procedure for mapping the pasted content to machine state.

**Failure mode:** State Compression integrity cannot be verified. A corrupted or partial State Compression produces no error — the session continues with an undefined prior state.

**Proposed resolution**

Define State Compression as a typed schema with a deserialization protocol:
1. Parse schema — validate required fields present
2. Load to INIT state with prior context
3. Skip to last known gate status
4. Resume from open objections

The kimi-synthesis-draft.md includes a version of this in §9.

**Related proposals:** None filed yet.

---

## G-08 · LOW — "Constraint Health" Not Measurable

**Component:** Coherence Controller §3  
**Charter section:** §3

**Description**

The Coherence Controller "monitors constraint health" but this is never defined as a measurable quantity. It cannot be computed, compared, or thresholded. It is currently a metaphor doing the work of a metric — the controller is told to monitor something that has no operational definition.

**Failure mode:** The core decision variable of the Coherence Controller is unmeasured. CONVERGE / DIVERSIFY / RESTART decisions are made against an undefined input.

**Proposed resolution**

Define constraint health as a scalar or vector function of:
- Gates passed / gates applied (gate coverage ratio)
- Objections resolved / objections raised (skepticism ratio)
- Evidence levels of active claims (E1-weighted claims as vulnerability indicator)

A formulation like `H = (gates_passed / gates_applied) × (objections_resolved / max(1, objections_raised))` gives a value in [0, 1]. Below a threshold, DIVERSIFY should be preferred over CONVERGE.

**Related proposals:** None filed yet.
