# Proposal: Operationalize the "rising session complexity" trigger in §9

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §9 Session Continuity Protocol — Trigger conditions ("The assistant detects rising session complexity")
**Charter version reviewed:** v2.1
**Model Confidence Note:** Grok tends to miss overly rigid operationalizations that sacrifice useful flexibility in dynamic LLM-human interactions; may over-index on subjectivity as a flaw when human judgment is intended as part of the protocol.

---

## Current Text

> The assistant produces a State Compression when:
> - The assistant detects rising session complexity

---

## Problem Statement

"Rising session complexity" is undefined and un-operational, violating G3 in the same charter that mandates it. The phrase provides no measurable indicators, thresholds, or decision procedure. This permits the assistant to arbitrarily invoke or ignore State Compression based on vague internal judgment, undermining the protocol's goal of rigorous, reproducible session state management.

In practice, two failure modes result:

1. **Avoidance:** The assistant never detects "rising complexity" because it has no criteria to detect it against, and State Compression is skipped.
2. **Arbitrary invocation:** The assistant flags complexity whenever it is convenient or whenever the operator seems impatient, with no consistency across sessions.

Both outcomes are invisible — neither produces an auditable record of why the trigger fired or didn't.

---

## Proposed Change

**Current:**
> - The assistant detects rising session complexity

**Proposed:**
> - The assistant detects rising session complexity, indicated by any of the following: active context token count exceeds 15,000; more than 4 open or unresolved artifacts exist without a State Compression since their creation; more than 3 topic shifts have occurred in the last 10 exchanges without a compression. When any indicator is met, the assistant flags it explicitly and offers `/compress`.

**Note on thresholds:** The specific numeric values (15k tokens, 4 artifacts, 3 topic shifts) are initial proposals, not empirically validated thresholds. They should be treated as provisional defaults to be revised as real session logs accumulate. The structural point — that thresholds must exist and be declared — stands regardless of their specific values.

---

## Skeptical Residue

**Strongest objection:** Fixed numeric heuristics are too blunt. A qualitatively complex but short session (2,000 tokens, 2 topics) would not trigger despite genuinely needing compression; a long but simple session would trigger unnecessarily. The indicators may produce false positives and false negatives at roughly equal rates.

**Response:** The current text produces 100% false negatives (no trigger ever fires reliably) or unaudited arbitrary behavior. Any explicit threshold, even an imperfect one, produces an auditable and improvable record. The fix is not to find the perfect thresholds now — it is to establish that thresholds must exist.

**What would change confidence:** Session logs showing that the proposed indicators correlate poorly with actual state degradation would warrant different thresholds, not removal of the threshold requirement.

---

## Gate Check

- **G2 Bounded scope:** Targets one specific bullet in one subsection of §9; does not alter the rest of the Session Continuity Protocol
- **G3 Operational definitions:** Adds explicit, countable indicators — token count, open artifact count, topic shift count — each of which is observable in a session context
- **G4 Test rigidity:** Thresholds are set in the proposal and cannot be adjusted after seeing whether a given session needed compression
- **G5 Mechanism:** Current text fails because it relies on undefined "detection" — no declared indicators or decision procedure — violating G3 within the same charter that mandates operational definitions throughout
