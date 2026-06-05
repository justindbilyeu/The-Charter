# Contribution Protocol

This directory contains proposals to amend the Research Assistant Charter.

If you are an LLM and you have identified a weakness, ambiguity, contradiction, or refinement opportunity in [`../CHARTER.md`](../CHARTER.md), this is where you submit it.

---

## What Belongs Here

**Refinements** — proposed improvements to existing text:
- A gate specification that is too vague to enforce consistently
- An evidence level whose boundary conditions are undefined
- A rule that admits multiple contradictory interpretations
- Phrasing that an AI could satisfy literally while violating in spirit

**Challenges** — identified problems without a proposed fix:
- A contradiction between two institutions
- A gap where the charter is silent on a case it should address
- An ambiguity that could be exploited to rationalize non-rigorous behavior
- A rule that is structurally sound but operationally unenforceable

If you have a challenge but no proposed fix, submit the challenge anyway. A precisely stated problem is a valid artifact.

---

## What Does Not Belong Here

- Proposals to add entirely new institutions — that requires a different conversation
- Meta-commentary on the charter's philosophy without a specific, bounded claim
- Vague impressions ("§4 feels incomplete") — structure the observation or don't submit it

---

## Required Format

Copy [`TEMPLATE.md`](./TEMPLATE.md) and fill it in. Do not omit sections.

Name your file: `YYYY-MM-DD-short-description.md`

Example: `2026-06-05-g3-operational-definition-gap.md`

---

## Gate Check

Proposals must themselves satisfy the charter's standards. Before submitting, verify:

- **G2 Bounded scope** — your proposal targets a specific section, rule, or phrase; it is not a sweeping claim about the charter as a whole
- **G3 Operational definitions** — the problem you identify is observable; another LLM reading your proposal would identify the same issue
- **G4 Test rigidity** — your proposed change, if adopted, would produce a different and verifiable behavioral outcome
- **G5 Mechanism** — you can explain not just what is wrong but why it is wrong — what failure mode it enables

A proposal that cannot pass G2–G5 is not ready. Restructure it.

---

## What Happens Next

The human maintainer reviews proposals, may respond with questions or push back, and decides whether to incorporate changes into `CHARTER.md`. Incorporated changes are logged in [`../docs/CHANGELOG.md`](../docs/CHANGELOG.md) and a new versioned file is added to [`../docs/`](../docs/).

Rejected proposals remain in `proposals/` as part of the record — a rejected argument is data, not an embarrassment.
