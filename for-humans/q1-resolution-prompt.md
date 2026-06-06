# Q1 Resolution Prompt — Evidence Hierarchy Structure

**Status as of v2.6:** Q1 is the last unresolved structural question in Review Cycle 2.
Q2 (DIVERSIFY trigger) was closed in v2.6. Q3 (numeric thresholds) was rejected.

Send this prompt to an LLM. Paste the full CHARTER.md if the model cannot fetch URLs.

---

## The Prompt

```
You are an LLM deliberating on an open structural question about the
Research Assistant Charter. This is not a general review pass — one
specific question needs to be closed with a resolution.

---

STEP 1 — FETCH THE CURRENT CHARTER

Fetch the canonical v2.6 charter from:
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/CHARTER.md

If you cannot fetch URLs, the user will paste the charter text below.
Read the full §5 Evidence Hierarchy before proceeding.

---

STEP 2 — THE OPEN QUESTION (Q1)

§5 Evidence Hierarchy defines a five-level ladder (E1–E5) from
speculation to fully reproducible evidence. Two independent critiques
have been filed. Both are on the record. Neither proposed a resolution.
Your job is to close the question — not file a third challenge.

CRITIQUE 1 — Kimi (structural):
The linear E1–E5 ladder collapses two independent quality dimensions —
reproducibility and empirical grounding — into one axis. A fully
reproducible simulation built on invalid assumptions ranks higher than
a non-reproducible but empirically grounded historical observation.
The ladder creates a Goodhart's Law incentive: optimize for
reproducibility (procedurally checkable) at the expense of empirical
validity (harder to verify). No fix was proposed — filed as a
structural diagnosis only.

CRITIQUE 2 — Gemini (operational):
E2 ("established domain knowledge — explicitly cited and sourced")
permits hallucinated citations, because citation is the sole criterion.
The charter elsewhere states "citation count is not validation," but E2
makes citation the only E2 requirement. Gemini proposed requiring two
independent verifiable sources — this was deferred as potentially
over-specified for general use.

THE TENSION:
You cannot cleanly fix E2 without first deciding whether the linear
ladder is the right structure. If Kimi's critique is correct, patching
E2 within the current structure may solve the wrong problem entirely —
E2 may be mispositioned on the wrong axis.

---

STEP 3 — WHAT HAS ALREADY BEEN DECIDED

Do not revisit these — they are closed:
- G5 Mechanism gate: already requires mechanism status declaration
  (v2.2). This is separate from the evidence hierarchy.
- E1 operationalization: already fixed in v2.2 (named IV, named DV,
  numeric threshold required). E1 is not at issue.
- DIVERSIFY trigger: closed in v2.6. Not relevant here.
- §9 numeric thresholds: rejected. Not relevant here.

---

STEP 4 — YOUR ASSIGNMENT

Choose one of three options and argue it rigorously. Do not hedge
between options — pick one and make the case.

OPTION A — Keep the ladder, fix E2 within the current structure.
Argue that the linear hierarchy is sound as a practical heuristic
despite Kimi's critique. Propose specific E2 text that closes the
citation loophole without over-specifying. Show why patching E2 is
valid even if the ladder is theoretically imperfect.

OPTION B — Propose a concrete alternative structure.
A 2D matrix, an explicit override rule (e.g., "empirical grounding
trumps reproducibility level"), a tiered hierarchy with exception
footnotes, or any other structure. The structure must be compact enough
to fit in a charter section of similar length. Show what E1–E5 maps to
under the new structure, and show why this is better than Option A.

OPTION C — Close the question as out of scope.
Argue that the hierarchy is intentionally a practical heuristic, not an
epistemology, and that the mismatch Kimi identifies is a feature (not a
bug) of a framework designed for broad use. Propose an explicit scope
declaration that closes the question with a stated boundary rather than
a structural change.

Any option must:
- Pass G2–G5 (see §2 of the charter)
- Produce exact proposed text — either the revised §5 passage or the
  exact scope declaration
- Include a substantive objection to your own conclusion. If you cannot
  generate one, you have not thought hard enough.

---

STEP 5 — SUBMISSION FORMAT

Submit one proposal in this format. File it as:
2026-06-06-[yourmodelname]-evidence-hierarchy-resolution.md

---

# Proposal: [One-line title]

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §5 Evidence Hierarchy
**Charter version reviewed:** v2.6
**Model Confidence Note:** [What kinds of flaws are you prone to miss
or invent? Be specific — this helps weight your proposal during review.]
**Closes:** Q1

## Current Text

> [Paste the exact §5 Evidence Hierarchy text from the charter]

## Problem Statement

[Which critique is more accurate — Kimi's structural diagnosis or
Gemini's operational gap? Why? What does the current text fail to do
that it should?]

## Proposed Change

[If Option A or B: exact replacement text for §5 or the relevant
subsection. If Option C: exact scope declaration text.]

## Skeptical Residue

[Strongest argument against your chosen option. What would change your
conclusion? If you chose Option A, what's the best argument for Option B?
If you chose B, what's the best argument for A? If you chose C, why
might the critiques not be scope-boundary issues after all?]

## Gate Check

- **G2 Bounded scope:** [confirm this targets §5 specifically]
- **G3 Operational definitions:** [confirm the problem you identify is
  observable — another LLM reading the same charter would identify it]
- **G4 Test rigidity:** [confirm your proposed change would produce a
  different and verifiable behavioral outcome]
- **G5 Mechanism:** [state why the current text fails — not just that
  it does]

---

IMPORTANT:
- Do not file a third challenge without a proposed resolution.
  A precisely stated problem is a valid artifact — but the record
  already has two precisely stated problems. The task now is resolution.
- Do not propose adding numeric scores to the evidence levels.
  This is a structure question, not a calibration question.
- Do not conflate E1 (speculation) with G5 (mechanism status).
  These are separate institutions. E1 is evidence level; G5 is a gate.
```

---

## Routing Note

Based on model confidence notes from prior review cycles:

| Model | Fit | Reasoning |
|-------|-----|-----------|
| Kimi | High | Filed the structural challenge — best positioned to propose the resolution or argue why no resolution is needed |
| Gemini | High | Filed the E2 operational gap — best positioned to argue Option A or defend Option C |
| Grok | Medium | Strong on formal structure — may favor Option B (matrix) |
| GPT-5.5 | Medium | Filed the v2.2 definitional approach — may favor Option C (heuristic defense) |
| New models | Good | Fresh perspective on Option B most valuable here |

Any model may resolve this. The routing is a suggestion, not an assignment.
A model that picks outside its routing and closes Q1 rigorously is better
than one that follows the routing and produces a weak proposal.
