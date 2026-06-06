# Proposal: Remove DIVERSIFY → GATE_CHECK shortcut; require artifact recompilation

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §3 Coherence Controller — DIVERSIFY state routing
**Charter version reviewed:** v2.2
**Model Confidence Note:** Gemini's core competence here is system routing and execution path tracing. The risk is over-weighting graph topology correctness at the expense of operational flexibility. The proposed fix (strict DIVERSIFY → STRUCTURING) is less flexible than conditional routing but avoids introducing trigger-source state-tracking complexity. This proposal takes the simpler fix.
**Source:** Gemini FSM structural analysis of MACHINE_SPEC.md transition graph

---

## Current Text

From §3, DIVERSIFY description:

> **DIVERSIFY** — inject alternative explanations, add skeptical probes, challenge assumptions before proceeding

From the MACHINE_SPEC.md transition table (Section 3.7):

> | DIVERSIFY | → GATE_CHECK, → STRUCTURING | ...

The transition graph shows:

```
           GATE_CHECK
          /     |     \
         ▼      ▼      ▼
    DIVERSIFY CONVERGE RESTART
         │        │       │
         └──► GATE_CHECK  │
                   │      └──► STRUCTURING
                   ▼
                OUTPUT
```

---

## Problem Statement

The FSM as specified permits GATE_CHECK → DIVERSIFY → GATE_CHECK as a valid execution path. This path is a structural trap.

When GATE_CHECK fails and routes to DIVERSIFY, DIVERSIFY's function is to inject alternatives, add probes, and challenge assumptions. These operations update the objection register. But they do not update the underlying structured_artifact — the artifact is not recompiled during DIVERSIFY. The objection register grows; the artifact does not change.

When DIVERSIFY then routes directly back to GATE_CHECK, GATE_CHECK re-evaluates the same structured_artifact it just failed against. The gates fail for the same reasons. GATE_CHECK routes to DIVERSIFY again. The loop repeats.

**The failure mode is deterministic:** under this routing, any GATE_CHECK failure that does not result in RESTART will produce an execution cycle with no exit condition. The objection register accumulates entries; the artifact is never revised; gates continue to fail; DIVERSIFY continues to be triggered; the cycle runs until context is exhausted.

The MACHINE_SPEC.md transition table acknowledges this as Gap G-02 (DIVERSIFY trigger undefined) — but the routing trap is a separate issue. Even a well-specified DIVERSIFY trigger cannot resolve a loop caused by routing DIVERSIFY back to GATE_CHECK without an intermediate recompilation step.

**The correct model:** DIVERSIFY's output is new information (objections, alternatives, challenged assumptions). That new information must be incorporated into the structured_artifact before gate evaluation can be meaningful. The only mechanism the spec provides for incorporating information into an artifact is STRUCTURING. Therefore, the path after DIVERSIFY must always pass through STRUCTURING.

---

## Proposed Change

**In §3, revise the DIVERSIFY description to specify its exit transition:**

Replace:

> **DIVERSIFY** — inject alternative explanations, add skeptical probes, challenge assumptions before proceeding

With:

> **DIVERSIFY** — inject alternative explanations, add skeptical probes, challenge assumptions. When DIVERSIFY is complete, the session must return to STRUCTURING to incorporate the updated objection register and revised assumptions into the artifact before any gate evaluation occurs. DIVERSIFY does not route directly to GATE_CHECK.

**In MACHINE_SPEC.md, update the transition table:**

Replace:

> | DIVERSIFY | → GATE_CHECK, → STRUCTURING |

With:

> | DIVERSIFY | → STRUCTURING |

The `DIVERSIFY → GATE_CHECK` transition is removed. STRUCTURING remains the only valid exit from DIVERSIFY.

**Note on the STRUCTURING self-loop:** STRUCTURING already has a `→ STRUCTURING` transition (self-loop while compiling). The combined path DIVERSIFY → STRUCTURING → GATE_CHECK achieves the same evaluative coverage as DIVERSIFY → GATE_CHECK while guaranteeing the artifact is updated before re-evaluation.

---

## Skeptical Residue

**Strongest objection — DIVERSIFY was not always triggered by GATE_CHECK:** The current transition table permits `DIVERSIFY → GATE_CHECK` alongside `DIVERSIFY → STRUCTURING`, allowing the routing to vary by trigger source. The Coherence Controller can trigger DIVERSIFY during STRUCTURING (before GATE_CHECK is ever reached). In that case, returning to STRUCTURING after DIVERSIFY is an artifact recompilation pass that may be unnecessary if the artifact has already been updated. Requiring STRUCTURING in all cases imposes recompilation overhead on cases that don't need it.

**Response:** The overhead of a STRUCTURING pass is bounded and acceptable. STRUCTURING is not a full session reset — it is the artifact compilation step. A STRUCTURING pass after DIVERSIFY that concludes the artifact is already up-to-date terminates quickly and routes to GATE_CHECK normally. The cost of an unnecessary STRUCTURING pass is marginal; the cost of the routing loop (context exhaustion, invisible failure) is severe. The simpler invariant (DIVERSIFY always → STRUCTURING) is preferable to conditional routing that requires tracking the trigger source.

**What would change confidence:** Evidence that removing `DIVERSIFY → GATE_CHECK` produces sessions where STRUCTURING passes consistently conclude "no change needed" (indicating the pass is always unnecessary and the overhead is real), combined with evidence that the routing loop failure mode never occurs in practice (indicating the fix addresses a theoretical problem with no operational cost).

---

## Gate Check

- **G2 Bounded scope:** Targets only the DIVERSIFY exit transition in §3 and the corresponding transition table entry in MACHINE_SPEC.md. Does not alter GATE_CHECK routing, STRUCTURING behavior, or any other section.
- **G3 Operational definitions:** The routing loop is observable in any session transcript that shows GATE_CHECK → DIVERSIFY → GATE_CHECK with no intervening STRUCTURING step. The proposed fix is observable: under the new text, a GATE_CHECK → DIVERSIFY transition must be followed by a STRUCTURING step before any GATE_CHECK can appear.
- **G4 Test rigidity:** A session that routes DIVERSIFY directly to GATE_CHECK after the proposed change is adopted is a protocol violation detectable from the transcript. The absence of a STRUCTURING step between DIVERSIFY and GATE_CHECK is a binary, auditable outcome.
- **G5 Mechanism:** The trap fails because GATE_CHECK is evaluating a stale artifact. DIVERSIFY updates the objection register but cannot update the artifact — artifact update is the exclusive function of STRUCTURING. A gate evaluation against a stale artifact is not a meaningful evaluation; gates may pass or fail for reasons that the DIVERSIFY output has already invalidated. The mechanism of failure is a missing recompilation step between objection discovery (DIVERSIFY) and gate evaluation (GATE_CHECK).
