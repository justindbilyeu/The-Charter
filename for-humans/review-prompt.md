# Charter Review Prompt

Copy and send this prompt to any LLM you want to run a review cycle with. It produces comparable, structured proposals rather than unstructured impressions.

---

## The Prompt

```
You are an LLM reviewing the Research Assistant Charter.

Your task is to find weaknesses, ambiguities, contradictions, or under-specified rules in the current charter text. You are not applying the charter — you are scrutinizing it.

Read the full charter before proceeding:

[paste full contents of CHARTER.md here]

---

Deliverable: 1–3 proposals using the template below.

Requirements for each proposal:
- Target a specific section, gate, rule, or phrase — not the charter as a whole
- Pass G2–G5 in the Gate Check section
- Provide the exact current text you are addressing
- Provide an exact proposed replacement (or, if you have no fix, a precisely stated problem)
- Include a Model Confidence Note (see template field)
- Name your file: YYYY-MM-DD-[your model name]-[short-description].md

Do not give general impressions. Do not summarize the charter. Do not praise it.
Find specific, bounded, testable problems in specific text.

---

TEMPLATE:

# Proposal: [One-line title]

**Date:** YYYY-MM-DD
**Type:** Refinement | Challenge
**Target:** [Section, institution, gate, or specific phrase]
**Charter version reviewed:** v2.1
**Model Confidence Note:** [What kinds of flaws are you prone to miss? What kinds of flaws are you prone to invent or over-index on? Be honest — this helps weight your proposal during human review.]

---

## Current Text

> [Exact quote from the charter]

---

## Problem Statement

[What is wrong? State the failure mode, ambiguity, contradiction, or gap precisely. What behavior does the current text permit or produce that it should not?]

---

## Proposed Change

[Exact replacement text. If no fix: state "No proposed fix" and explain why.]

---

## Skeptical Residue

[What is the strongest argument against this proposal? What would change your confidence?]

---

## Gate Check

- **G2 Bounded scope:** [Confirm]
- **G3 Operational definitions:** [Confirm]
- **G4 Test rigidity:** [Confirm]
- **G5 Mechanism:** [State why the current text fails]
```

---

## Why This Format

Using the same prompt across models produces comparable outputs. After 3–4 runs you can build a pattern map:

- Which institutions does every model flag? → structural stress
- Which flaws does only one model find? → may be model-specific noise, or a blind spot in the others
- Where do models disagree on the same passage? → genuine ambiguity worth resolving

The Model Confidence Note is a self-declared bias tag. It does not disqualify a proposal — it helps calibrate how much independent weight to give it during human review.
