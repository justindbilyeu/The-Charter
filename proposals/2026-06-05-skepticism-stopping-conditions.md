# Proposal: Add stopping conditions for skepticism

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §3 Coherence Controller; §4 Productive Skepticism Protocol
**Charter version reviewed:** v2.1

---

## Current Text

**§3 Coherence Controller:**
> CONVERGE — structure is tight, gates pass, proceed to test

**§4 Calibration Rule:**
> If the assistant cannot generate at least one substantive objection to the current proposal, the assistant has not thought hard enough yet and must try again before responding.

---

## Problem Statement

The charter has strong escalation rules — when to DIVERSIFY, when to raise objections, when to RESTART — but no explicit criteria for when scrutiny has been satisfied.

The Calibration Rule in §4 requires the assistant to *always* generate at least one objection before responding. This is a one-way ratchet: scrutiny can always escalate, but the charter provides no chartered state of "scrutiny complete."

The failure mode this enables:

1. Hypothesis A is proposed.
2. Assistant raises Objection 1.
3. Objection 1 is tested and fails.
4. Assistant raises Objection 2 (Calibration Rule requires it).
5. Objection 2 is tested and fails.
6. Repeat indefinitely.

CONVERGE in §3 currently reads as: "structure is tight, gates pass." But there is no criterion for *when* that judgment can be made, and the Calibration Rule implies the assistant must always find something new to object to. This creates an asymmetry: escalation is rule-governed, convergence is implicit and ungoverned.

Infinite skepticism is not rigor. It is paralysis wearing rigor's clothing.

---

## Proposed Change

**§3 — Add CONVERGE criteria:**

**Current:**
> CONVERGE — structure is tight, gates pass, proceed to test

**Proposed:**
> CONVERGE — structure is tight, gates pass, proceed to test. CONVERGE criteria: (a) all G1–G5 gates pass, (b) all raised objections have been tested and their outcomes documented, (c) no untested objection with a viable and scoped test remains. CONVERGE is not consensus. It is exhausted scrutiny.

**§4 — Add Skepticism Termination Rule after the Calibration Rule:**

**Add:**
> **Skepticism Termination Rule**
> Skepticism is satisfied when: (a) all objections have been stated with precision, (b) each has been assigned a test or declared untestable with explicit reasoning, and (c) no new untested objection within the current scope can be generated. Generating objections indefinitely is not rigor — it is paralysis. The goal is exhausted scrutiny, not infinite scrutiny. Once termination conditions are met, the correct state is CONVERGE, not continued DIVERSIFY.

---

## Skeptical Residue

**Strongest objection:** "Exhausted scrutiny" is subjective. How does an assistant know it has run out of valid objections? This just moves the ambiguity from "when to converge" to "when objections are exhausted."

**Response:** This is a genuine limitation. But the charter's current alternative — no stopping condition at all — is strictly worse. The proposed language at least makes the stopping condition *explicit and auditable*: objections must be stated with precision, assigned tests, and documented. That creates a checklist. The current version has no checklist and no termination state. An imperfect explicit criterion outperforms an absent one.

**Second objection:** The Calibration Rule may need to be softened, not supplemented. If the rule requires generating an objection before *every* response, termination is structurally impossible.

**Response:** The Calibration Rule is strongest early in a session when structure is loose. The Termination Rule governs late-session behavior when scrutiny has run its course. These are complementary, not contradictory. The Calibration Rule governs whether an individual response is ready; the Termination Rule governs whether CONVERGE is the appropriate mode. Both can coexist.

**What would change my confidence:** A concrete example where the Termination Rule produces premature CONVERGE on a claim that should have remained in DIVERSIFY. The key protection against this is condition (c): "no new untested objection within the current scope can be generated." If objections remain, CONVERGE is still blocked.

---

## Gate Check

- **G2 Bounded scope:** Targets §3 CONVERGE definition and §4 Calibration Rule specifically; does not alter other institutions
- **G3 Operational definitions:** The failure mode is observable — the charter has DIVERSIFY trigger conditions but no CONVERGE trigger conditions; the asymmetry is verifiable by inspection
- **G4 Test rigidity:** With this addition, CONVERGE becomes an explicit, checkable state with three listed conditions; without it, CONVERGE is an implicit judgment call with no criteria. The behavioral difference is verifiable.
- **G5 Mechanism:** The mechanism of failure is asymmetric rule structure — strong escalation rules paired with no termination rules — creating a system that can only ratchet toward infinite scrutiny, never return to convergence.
