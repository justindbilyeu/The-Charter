# Proposal: Operationalize "substantive objection" in the Calibration Rule

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §4 Productive Skepticism Protocol — Calibration Rule
**Charter version reviewed:** v2.1
**Model Confidence Note:** Grok is prone to missing cultural/LLM-training biases in what counts as "substantive"; may invent over-formalization risks where the rule's intent is to force deeper thinking without paralyzing output.

---

## Current Text

> **Calibration Rule**
> If the assistant cannot generate at least one substantive objection to the current proposal, the assistant has not thought hard enough yet and must try again before responding.

---

## Problem Statement

"Substantive objection" is undefined. Without operational criteria, the rule admits two symmetrical failure modes:

1. **Underenforcement:** A superficial or repetitive objection satisfies the rule. The assistant restates a previously addressed concern, or produces a generic "this needs more evidence" that applies to any proposal regardless of content. The rule is technically satisfied; genuine scrutiny is bypassed.

2. **Unverifiable refusal:** The assistant claims inability to generate an objection without a clear failure mode. There is no criterion for distinguishing "genuinely exhausted scrutiny" from "premature compliance."

The result is performative skepticism — the rule creates the appearance of adversarial scrutiny without the substance. This is a direct failure of the protocol's intent.

**Relationship to existing proposal:** This proposal is complementary to `2026-06-05-skepticism-stopping-conditions.md`, which adds *termination criteria* (when scrutiny is complete). This proposal adds *entry criteria* (what a valid objection is). Together they bookend the skepticism protocol: valid objections must meet a standard (this proposal), and once all valid objections are addressed, scrutiny terminates (stopping-conditions proposal).

---

## Proposed Change

**Current:**
> If the assistant cannot generate at least one substantive objection to the current proposal, the assistant has not thought hard enough yet and must try again before responding.

**Proposed:**
> If the assistant cannot generate at least one substantive objection to the current proposal, the assistant has not thought hard enough yet and must try again before responding. A substantive objection must be: (a) specific — targeting a named element of the proposal, not the class of proposals in general; (b) testable — pointing to a condition under which the proposal would fail; (c) tied to a gate, failure mode, or assumption not previously addressed in the current session; and (d) not a restatement of an objection already raised and documented.

---

## Skeptical Residue

**Strongest objection:** The definition adds verbosity and overhead to every response, slowing quick-response interactions unnecessarily. Low-stakes scoping sessions would pay the same formalization cost as high-stakes research.

**Response:** The Calibration Rule already applies to every response; the proposed definition does not change scope, only precision. The overhead is in comprehension at time of reading, not execution — once internalized, checking (a)–(d) is no slower than the current undefined check. The alternative — an undefined standard that allows performative compliance — costs more in degraded output quality than the definition costs in reading time.

**What would change confidence:** A concrete example of a response where criteria (a)–(d) cannot be satisfied but a genuine substantive objection exists — i.e., a case where the definition is too narrow. I could not construct one.

---

## Gate Check

- **G2 Bounded scope:** Targets the Calibration Rule specifically — one sentence in §4; does not alter other skepticism protocol elements
- **G3 Operational definitions:** Provides four explicit criteria, each observable and checkable by another LLM reviewing the same session
- **G4 Test rigidity:** The definition is set in advance; whether a given objection satisfies (a)–(d) can be evaluated without post-hoc adjustment
- **G5 Mechanism:** Current text fails G3 and G5 by using "substantive" without mapping it to any procedure, observable, or criterion — enabling subjective enforcement that the charter elsewhere explicitly prohibits
