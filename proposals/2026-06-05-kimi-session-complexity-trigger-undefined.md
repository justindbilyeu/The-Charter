# Proposal: "Rising Session Complexity" Trigger Is Operationally Undefined

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §9 Session Continuity Protocol — trigger conditions
**Charter version reviewed:** v2.1
**Model Confidence Note:** Kimi is prone to over-indexing on operational precision and may demand formalization where heuristic judgment is more robust; may miss that some triggers are intentionally vague to preserve operator discretion; tends to invent structural gaps where flexible language is a feature.

---

## Current Text

> The assistant produces a State Compression when:
> - The assistant detects rising session complexity

---

## Problem Statement

The trigger "the assistant detects rising session complexity" has no operational definition. The charter requires operational definitions throughout (G3), yet here it asks the assistant to exercise undefined judgment.

Three failure modes result:

1. **Inconsistent execution:** One assistant produces a compression after 10 topic switches; another never does because it has no threshold to cross. The same session would produce different compression behavior across models.

2. **Invisible drift:** The operator cannot tell whether the assistant is ignoring complexity or simply has no mechanism to detect it. Both look identical from the outside.

3. **False positives:** An assistant may compress prematurely because it lacks a clear "not yet" signal, fragmenting productive work flow without cause.

The charter's own Coherence Controller would classify this as a G3 failure: a rule that relies on "the assistant feels like it" is not yet testable.

**Relationship to existing proposals:** `2026-06-05-grok-session-complexity-trigger-operationalization.md` proposes specific numeric thresholds (15k tokens, 4 artifacts, 3 topic shifts). `2026-06-05-gpt-5.5-state-compression-trigger-ambiguity.md` proposes operational definitions for "topic shift," "milestone," and "session complexity." This proposal takes a third approach: numeric heuristics with an explicit override and audit requirement. All three proposals address the same confirmed gap from different angles and are filed as competing evidence for the human reviewer.

---

## Proposed Change

**Replace the "rising session complexity" trigger with:**

> - Session complexity is considered elevated when any of the following heuristic thresholds are met: ≥3 unresolved skeptical objections active simultaneously; OR ≥2 active claims with divergent evidence levels (e.g., one at E1 and one at E3+); OR ≥3 distinct topic domains active in the current context window; OR token context usage exceeds 70% of the model's effective working limit.
>
> The assistant may produce a State Compression earlier than these thresholds if it judges the session state to be at risk, but must explicitly state which heuristic threshold it believes is approaching and why.

---

## Skeptical Residue

**Strongest objection:** These heuristics are arbitrary. Why 3 objections and not 4? Why 70% and not 80%? Formalizing bad heuristics creates a false sense of precision — cargo-cult operationalization that is worse than honest vagueness.

**Response:** The proposed thresholds are acknowledged as provisional. The claim is not that these numbers are correct; it is that *some* numbers must be declared and logged, so behavior is auditable and improvable. An assistant that states "I am compressing because 3 unresolved objections are active" can have its judgment reviewed and the threshold adjusted. An assistant that compresses because "complexity feels high" produces no auditable record. The provisional numbers are starting points, not endpoints.

**What would change confidence:** Evidence that the proposed heuristics predict degraded output quality (higher error rates, more self-contradiction, more gate failures) no better than random chance. If the thresholds provide no signal, the vague original was preferable because it at least didn't pretend to be precise.

---

## Gate Check

- **G2 Bounded scope:** Targets only the "rising session complexity" bullet in §9; does not alter other triggers or the rest of the Session Continuity Protocol
- **G3 Operational definitions:** The problem is observable — two different assistants will produce different compression schedules for the same session because "complexity" is undefined; another LLM reviewing the same session transcript cannot verify whether a compression was correctly triggered
- **G4 Test rigidity:** The proposed change produces a verifiably different outcome: an assistant must now cite a specific heuristic when compressing, making the decision auditable and improvable
- **G5 Mechanism:** Current text fails because it delegates a critical state-management decision to uninspectable model judgment — the same kind of "feels right" judgment the charter explicitly distrusts in §3 Coherence Controller
