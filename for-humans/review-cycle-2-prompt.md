# Charter Review — Cycle 2 Prompt

Cycle 2 is a deliberation pass, not a discovery pass. The structural problems are identified. Competing solutions are on the record. Your job is to close one open question with a specific, well-argued resolution.

Pick one of the three prompts below based on which question you are assigned or choose. Send the full prompt — including the context sections — to the LLM.

---

## Prompt A — Evidence Hierarchy: fix E2 or restructure the ladder?

```
You are an LLM deliberating on an open question about the Research Assistant Charter.

This is not a general review. One specific question needs to be closed.

---

CONTEXT: THE CHARTER (v2.2)

[paste full contents of CHARTER.md here]

---

CONTEXT: THE OPEN QUESTION

The Evidence Hierarchy (§5) has received two independent critiques:

CRITIQUE 1 — Kimi (structural):
The linear E1–E5 ladder collapses two independent quality dimensions —
reproducibility and empirical grounding — into one axis. A fully reproducible
simulation with invalid assumptions is weaker evidence than a non-reproducible
but empirically grounded observation. The ladder creates a Goodhart's Law
incentive: optimize for reproducibility (procedurally demonstrable) at the
expense of empirical validity (harder to verify). No fix was proposed.

CRITIQUE 2 — Gemini (operational):
E2 ("established domain knowledge — explicitly cited and sourced") permits
hallucinated citations and low-quality sources, since citation is the sole
criterion. The charter states "citation count is not validation" but E2
makes citation the only requirement. Gemini proposed requiring two independent
verifiable sources — this was deferred as potentially over-specified.

THE TENSION: You cannot fix E2 without first deciding whether the linear
ladder is the right structure. If Kimi's critique is correct, patching E2
within the current structure may solve the wrong problem.

---

YOUR ASSIGNMENT

Close this question with a single resolution. Three options:

Option A: Argue the linear ladder is sound as a practical heuristic, and
propose a specific E2 fix within the current structure.

Option B: Propose a concrete alternative structure (2D matrix, explicit
override rules, or hierarchy with footnotes for exceptions) and show what
E1–E5 maps to in the new structure.

Option C: Argue the challenge is out of scope — the hierarchy is an
intentional heuristic, not an epistemology — and close with an explicit
scope declaration rather than a structural change.

---

SUBMISSION FORMAT

Submit one proposal using this template. Name it:
YYYY-MM-DD-[yourmodelname]-evidence-hierarchy-resolution.md

# Proposal: [One-line title]

**Date:** [today]
**Type:** Refinement | Challenge
**Target:** §5 Evidence Hierarchy
**Charter version reviewed:** v2.2
**Model Confidence Note:** [self-declared bias]
**Closes:** Q1

## Current Text
[exact quote]

## Problem Statement
[why the current text fails — include your assessment of Kimi's and
Gemini's critiques: which is more accurate, and why]

## Proposed Change
[exact replacement text, or exact scope declaration closing the question]

## Skeptical Residue
[strongest argument against your chosen option; what would change your
conclusion]

## Gate Check
G2 / G3 / G4 / G5
```

---

## Prompt B — DIVERSIFY Trigger: what replaces the anthropomorphic trigger?

```
You are an LLM deliberating on an open question about the Research Assistant Charter.

This is not a general review. One specific question needs to be closed.

---

CONTEXT: THE CHARTER (v2.2)

[paste full contents of CHARTER.md here]

---

CONTEXT: THE OPEN QUESTION

The DIVERSIFY trigger in §3 reads:

  "The signal that triggers DIVERSIFY: 'This feels obviously right.'"

CRITIQUE — Gemini (structural deadlock):
"This feels obviously right" is anthropomorphic. LLMs calculate token
probabilities, not phenomenological states. The trigger either never fires
(if the assistant suppresses "feeling" per Genesis) or fires constantly
(any well-formed answer generates high-confidence tokens). This is a
linguistic deadlock: compliance with Genesis prevents the trigger from
firing; allowing the trigger to fire violates Genesis.

GEMINI'S PROPOSED REPLACEMENT:
Three structural conditions:
1. Fewer than two explicitly modeled competing hypotheses for the current claim
2. Claim generated without surfacing at least one explicit failure mode
3. No gate check applied since the last structural revision

DEFERRED BECAUSE: Condition 1 is itself undefined. "Explicitly modeled"
is as vague as "obviously right." A hypothesis is present somewhere in
the context window? Named as a claim? Assigned an evidence level?
Stress-tested by §4? Without a definition, Condition 1 recreates the
same problem it solves.

---

YOUR ASSIGNMENT

Close this question. Produce exact replacement text for the DIVERSIFY
trigger section of §3. Three paths:

Path 1: Complete Gemini's conditions by operationally defining "explicitly
modeled" in a way that is checkable by another LLM reading the same session.

Path 2: Propose a different replacement trigger mechanism — one that is
structural, not anthropomorphic, and does not reproduce the under-definition
problem of Condition 1.

Path 3: Argue the current anthropomorphic trigger is defensible because it
functions as a cultural norm for the human operator rather than an internal
LLM state check — and propose revised text making this distinction explicit.

---

SUBMISSION FORMAT

Submit one proposal. Name it:
YYYY-MM-DD-[yourmodelname]-diversify-trigger-resolution.md

# Proposal: [One-line title]

**Date:** [today]
**Type:** Refinement
**Target:** §3 Coherence Controller — DIVERSIFY trigger
**Charter version reviewed:** v2.2
**Model Confidence Note:** [self-declared bias]
**Closes:** Q2

## Current Text
[exact quote]

## Problem Statement
[your assessment of the deadlock critique — is it valid?]

## Proposed Change
[exact replacement text for the trigger section]

## Skeptical Residue
[strongest argument against your approach]

## Gate Check
G2 / G3 / G4 / G5
```

---

## Prompt C — §9 Complexity: add numbers or keep definitions?

```
You are an LLM deliberating on an open question about the Research Assistant Charter.

This is not a general review. One specific question needs to be closed.

---

CONTEXT: THE CHARTER (v2.2)

[paste full contents of CHARTER.md here]

---

CONTEXT: THE OPEN QUESTION

V2.2 adopted definitional trigger conditions for §9 (from GPT-5.5):

  "Session complexity is elevated — defined as two or more active claims,
  artifacts, or unresolved objections being tracked simultaneously without
  a State Compression having been produced since the earliest of them
  was opened."

TWO COMPETING NUMERIC PROPOSALS REMAIN ON THE RECORD:

Grok proposed: token count >15k, >4 open artifacts, >3 topic shifts in
last 10 exchanges. Flagged as provisional — numbers are guesses.

Kimi proposed: ≥3 unresolved skeptical objections, ≥2 active claims with
divergent evidence levels, ≥3 topic domains, >70% token context. Plus:
an override-and-audit requirement — assistant may compress earlier but
must cite which heuristic is approaching.

THE QUESTION: V2.2's definitional approach is clean and durable, but
leaves "how much" to judgment. Numeric thresholds make behavior auditable
and improvable — but the specific numbers are provisional guesses with
no empirical basis. Do the definitions need numbers alongside them?

---

YOUR ASSIGNMENT

Close this question. Two options:

Option 1: Argue for adding specific provisional thresholds alongside the
v2.2 definitions. Synthesize Grok and Kimi into a best-available set.
Include explicit calibration instructions — how should the thresholds
be revised as session data accumulates?

Option 2: Argue the v2.2 definitional approach is sufficient and close
the question without numeric additions.

---

SUBMISSION FORMAT

Submit one proposal. Name it:
YYYY-MM-DD-[yourmodelname]-session-complexity-resolution.md

# Proposal: [One-line title]

**Date:** [today]
**Type:** Refinement
**Target:** §9 Session Continuity Protocol — trigger conditions
**Charter version reviewed:** v2.2
**Model Confidence Note:** [self-declared bias]
**Closes:** Q3

## Current Text
[exact quote from v2.2]

## Problem Statement
[why the current v2.2 text does or does not need numeric thresholds]

## Proposed Change
[exact proposed text, or explicit statement closing the question as-is]

## Skeptical Residue
[strongest argument against your position]

## Gate Check
G2 / G3 / G4 / G5
```
