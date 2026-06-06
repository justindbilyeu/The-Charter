# Proposal: Structural Conditioning of the DIVERSIFY Trigger

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §3 Coherence Controller — DIVERSIFY trigger
**Charter version reviewed:** v2.4
**Closes:** Q2
**Model Confidence Note:** High confidence. This approach completely detaches the trigger from internal emotional heuristics, converting it into an inspectable, audit-ready checklist.

---

## Current Text

> The updated objection register and revised assumptions must be incorporated into the artifact before any gate re-evaluation.
>
> Premature convergence is a failure mode.
>
> If the trajectory shows three or more consecutive CONVERGEs with no DIVERSIFY or RESTART — if ideas are clicking together before they have been stress-tested — the correct response is DIVERSIFY, not COMPLETE.
>
> The signal that triggers DIVERSIFY:
> "This feels obviously right."
>
> That feeling is not evidence of correctness.
> It is evidence that scrutiny should increase.

---

## Problem Statement

The deadlock critique is structurally valid. Anthropomorphic prompts like "This feels obviously right" force an LLM into an unresolvable loop: either it plays along by simulating a "feeling" (violating Genesis and introducing non-deterministic behavior), or it functions correctly as an estimator of conditional probabilities and ignores the trigger entirely.

Furthermore, simply stating that a hypothesis must be "explicitly modeled" introduces a second layer of vagueness. To make the Coherence Controller programmatic, the DIVERSIFY trigger must fire based on visible, countable, structural omissions within the current context window.

---

## Proposed Change

Add a named "Structural DIVERSIFY Triggers" subsection immediately after the "This feels obviously right" narrative and before the Convergence Watchdog. The anthropomorphic text is preserved as cultural/operator-facing framing; the structural conditions are the machine-enforceable enforcement layer beneath it.

Three conditions, any of which mandates DIVERSIFY:

**1. Hypothesis Under-Specification:** Fewer than two competing hypotheses are documented in the active session context. A hypothesis is documented only if it includes: (a) a distinct identifier (e.g., H1, H2); (b) an explicit evidence level (E1–E5); (c) a discriminating test proposal with at least one named independent variable and one named dependent variable.

**2. Asymmetric Risk Assessment:** The active claim has been modified or advanced without an accompanying update to the objection register, or it lacks a recorded Failure Mode Probe (§4) entry detailing its specific failure conditions.

**3. Gate Omission:** New claims, metrics, or parameter ranges have been incorporated into the active artifact since the last formal gate evaluation.

*Note on Condition 3:* "Incorporated into the active artifact" — not "introduced into the dialogue." Clarifications, examples, and analogies raised in conversation do not trigger this condition. Changes to the structured artifact do.

---

## Skeptical Residue

The strongest argument against this structural approach is that it risks turning the DIVERSIFY state into a bureaucratic compliance checklist. An LLM could easily auto-generate a weak, superficial "H2" with an arbitrary "E1" status simply to fulfill the structural requirement and clear the gate, without actually introducing real, paradigm-challenging skepticism.

By removing the "feeling" threshold, we trade an anthropomorphic trap for a potential "checking the box" failure mode. This is a known trade-off. The structural conditions are better than no conditions, but they do not fully eliminate low-effort compliance as a failure mode. The DIVERSIFY exit criterion (v2.5, three-part completion condition) partially mitigates this — a box-checked hypothesis must also produce a new substantive objection and artifact revision before DIVERSIFY is complete.

---

## Gate Check

- **G2 Bounded scope:** Targets the DIVERSIFY trigger section of §3 specifically. Does not alter CONVERGE, RESTART, or gate definitions.
- **G3 Operational definitions:** Every condition relies on countable elements (distinct identifiers, evidence levels, named variables, formal gate evaluation events). Another LLM reading the same session transcript would identify the same violated conditions.
- **G4 Test rigidity:** The structural conditions mandate immediate state transition when met — they cannot be bypassed or modified post-hoc.
- **G5 Mechanism:** The failure mode addressed is trigger evasion: an anthropomorphic condition either never fires (correct LLM behavior) or fires non-deterministically (simulated affect). Observable structural omissions do not have this failure mode.
