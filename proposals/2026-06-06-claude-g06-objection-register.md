# Proposal: Define Objection Register as a required data structure

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §4 Productive Skepticism Protocol — Skepticism Termination Rule
**Charter version reviewed:** v2.2
**Model Confidence Note:** Claude may introduce schema complexity beyond what the charter's prose context requires. The proposed schema is deliberately minimal — resist adding fields beyond what the Skepticism Termination Rule strictly requires to evaluate its termination conditions.
**Source:** Machine spec gap analysis (G-06 · MEDIUM)

---

## Current Text

> **Skepticism Termination Rule**
>
> Skepticism is satisfied when: (a) all objections have been stated with precision, (b) each has been assigned a test or declared untestable with explicit reasoning, and (c) no new untested objection within the current scope can be generated. The goal is exhausted scrutiny, not infinite scrutiny. Once termination conditions are met, the correct state is CONVERGE, not continued DIVERSIFY.

---

## Problem Statement

The Skepticism Termination Rule specifies three conditions for termination. Evaluating all three requires knowing:

- Which objections have been raised (condition a)
- Which have been assigned tests or declared untestable (condition b)
- Whether any new objection can still be generated (condition c)

None of this is trackable without a persistent register. Currently, objections exist only as prose in the session transcript. To evaluate condition (a), you must parse the transcript for every objection raised. To evaluate condition (b), you must cross-reference each objection with its resolution. Condition (c) requires knowing the full set of tested objections to avoid re-raising them.

This is not a theoretical gap — it is a practical one that fires in every long session. Without a register, the Skepticism Termination Rule is evaluated by recalling prose from memory rather than auditing a data structure. Memory-based audits are unreliable and non-reproducible across sessions.

The Termination Rule is the charter's primary defense against infinite skepticism (the opposite failure mode from agreement drift). It cannot be reliably enforced without a structured record.

---

## Proposed Change

Add the following section immediately after the Calibration Rule and before the Skepticism Termination Rule:

> **Objection Register**
>
> Every objection raised during a session is maintained in an Objection Register. Each entry contains:
>
> - The specific claim the objection targets
> - The objection as stated
> - Status: **OPEN** (raised, not yet addressed), **TESTED** (assigned a test with a specified outcome condition), or **UNTESTABLE** (declared untestable with explicit reasoning)
>
> The register is updated in real time: when an objection is raised (status: OPEN), when a test is assigned (status: TESTED), when untestability is declared (status: UNTESTABLE with reasoning).
>
> The Skepticism Termination Rule cannot be declared satisfied unless:
> - The register contains at least one entry
> - The register contains no OPEN entries

Replace the current Skepticism Termination Rule with:

> **Skepticism Termination Rule**
>
> Skepticism is satisfied when: (a) all objections have been stated with precision and logged in the Objection Register, (b) each register entry has status TESTED or UNTESTABLE — no entry may remain OPEN, (c) no new objection within the current scope can be generated. The goal is exhausted scrutiny, not infinite scrutiny. Once termination conditions are met, the correct state is CONVERGE, not continued DIVERSIFY.

The change is minimal: (a) adds "and logged in the Objection Register," (b) replaces "each has been assigned a test or declared untestable" with the register-based formulation. The substance is identical; the register makes it auditable.

---

## Skeptical Residue

**Strongest objection:** Maintaining an explicit Objection Register adds bookkeeping overhead to every session. In short, single-claim sessions the register is trivial and the overhead is wasted. In conversational contexts (not formal research), the register formalism is intrusive and conflicts with the charter's design as a lightweight behavioral guide rather than a data management system.

**Response:** The register does not require a formatted table or special notation — it requires that objections be trackable. In short sessions, this is satisfied by a bulleted list in the session prose. In long sessions, the State Compression already requires "Skeptical residue: objections raised, resolved, and still open" — the register merely makes that section machine-auditable. The overhead is proportional to session complexity, which is exactly when it is needed.

**What would change confidence:** Evidence that the register formalism is routinely ignored or that sessions satisfying the original Termination Rule (by prose audit) perform comparably to sessions using an explicit register in terms of overlooked objections. That would indicate the register adds no reliability benefit.

---

## Gate Check

- **G2 Bounded scope:** Targets the Objection Register definition and the Skepticism Termination Rule in §4 only. Does not alter the Calibration Rule, Convergence Check, or any other skepticism mechanism.
- **G3 Operational definitions:** "OPEN / TESTED / UNTESTABLE" are mutually exclusive, exhaustive statuses. "No OPEN entries" is a binary, countable condition. "At least one entry" is a countable condition. All termination conditions are now checkable without prose parsing.
- **G4 Test rigidity:** Sessions under the proposed text must maintain a register and satisfy the register-based termination conditions. A session declaring CONVERGE with one or more OPEN register entries is a protocol violation — observable and auditable in the session transcript.
- **G5 Mechanism:** The gap fails because the Skepticism Termination Rule's conditions (a) and (b) require tracking which objections exist and what their status is — information that is only reliably available from a persistent structure. Without a register, the rule is evaluated from memory, which is unreliable and not reproducible across independent reviewers of the same session.
