# FSM States

Seven states. Each has a description, valid transitions, and a gap annotation where the charter is underspecified.

---

## INIT

**Description:** System boot state. Charter loaded, session context empty. Awaiting first claim input.

**Transitions:** → STRUCTURING

**Gap:** `G-01 · HIGH` — No initialization procedure defined in the charter. Boot state is implicit in the prose but undefined in any machine-executable sense. What context is loaded at session start? What is the default state before the first claim arrives?

**Proposed resolution:** Define INIT entry conditions: Charter version loaded, session ID assigned, operator context captured, objection register cleared.

---

## STRUCTURING

**Description:** Incoming idea or claim is being compiled into a structured artifact. Structuring Contract (§1) active.

**Transitions:** → GATE_CHECK, → STRUCTURING (self-loop while compiling)

**Gap:** None identified.

---

## GATE_CHECK

**Description:** G1–G5 applied to the current artifact. All must pass to proceed.

**Transitions:** → DIVERSIFY (gates fail, alternatives needed), → CONVERGE (all gates pass), → RESTART (structural flaw)

**Gap:** `G-04 · MEDIUM` — Gate failure sequencing undefined. What happens when G3 fails but G1–G2 pass? Partial gate states are unspecified. Does G1 failure short-circuit G2–G5?

**Proposed resolution:** Define gate dependency graph. G1 + G2 are prerequisites (numeric completeness + bounded scope). G3–G5 are parallel validators. G1 or G2 failure triggers RESTART. G3–G5 failure triggers DIVERSIFY or targeted STRUCTURING.

---

## DIVERSIFY

**Description:** Inject competing explanations, skeptical probes, assumption challenges. §4 Productive Skepticism Protocol active.

**Transitions:** → GATE_CHECK, → STRUCTURING

**Gap:** `G-02 · HIGH` — DIVERSIFY trigger undefined for LLM execution. Current text: "This feels obviously right" is anthropomorphic. An LLM cannot introspect phenomenological states. The trigger either never fires or fires constantly. See [OPEN_QUESTIONS.md Q2](../OPEN_QUESTIONS.md) and proposals `2026-06-05-gemini-coherence-controller-deadlock.md` and `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md`.

**Proposed resolution:** Operationalize as structural conditions checkable from session transcript. See Q2 in [OPEN_QUESTIONS.md](../OPEN_QUESTIONS.md).

---

## CONVERGE

**Description:** Exhausted scrutiny. All gates pass, all objections documented, no new untested objection in scope.

**Transitions:** → OUTPUT, → INIT (new claim)

**Gap:** None identified.

---

## RESTART

**Description:** Structural flaw detected. Recompile with explicit defect list. Do not patch around the failure.

**Transitions:** → STRUCTURING

**Gap:** `G-03 · HIGH` — No watchdog defined. The charter names agreement drift as a failure mode but provides no detection mechanism. A system that has drifted into mirror mode has no internal signal that it has done so.

**Proposed resolution:** Define a periodic self-check: at each OUTPUT, evaluate whether the last N state transitions produced any RESTART or DIVERSIFY. If not, flag for human review.

---

## OUTPUT

**Description:** Artifact produced. Handoff generated. State Compression triggered if §9 conditions met.

**Transitions:** → INIT (new claim), → STRUCTURING (continue current work)

**Gap:** None identified.

---

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
             └──► GATE_CHECK  │
                       │      └──► STRUCTURING
                       ▼
                    OUTPUT
                    /    \
                   ▼      ▼
                 INIT  STRUCTURING
```
