# Proposal: G4 Has No Escape Hatch for Measurement Construct Invalidation

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §2 Hard Gates, G4
**Charter version reviewed:** v2.1
**Model Confidence Note:** Kimi tends to over-index on formal edge cases and under-weight pragmatic flexibility; may invent problems where absolute rules are actually the safer choice; tends to miss when a rule's rigidity is its primary protective value.

---

## Current Text

> G4 Test rigidity — thresholds cannot be adjusted after seeing results. Ever.

---

## Problem Statement

The absolute prohibition "Ever" prevents a legitimate and scientifically common scenario: discovering that the initial operational definition or metric was flawed *independent of the outcome*.

**Concrete example:** A preregistered threshold uses "user engagement = clicks per session." Mid-experiment, you discover the tracking pixel is double-counting clicks due to a frontend bug. The threshold is now measuring noise, not signal. Under the current G4, two options remain:
- (a) Continue with a broken metric — not rigorous
- (b) Abandon the experiment entirely — not rigorous, and loses all collected data

Neither option is what rigorous research would prescribe. The rigorous response is to document the construct invalidation, apply a corrected metric, and log it as a protocol deviation with full reasoning.

**The failure mode G4 creates:** The charter conflates threshold-hacking (adjusting thresholds to chase a desired result) with construct invalidation (adjusting because the measurement itself was discovered to be broken). Both produce a change to the threshold after data collection begins. Their *signatures* are different — construct invalidation is discoverable independent of outcome direction, threshold-hacking is not — but G4 treats them identically.

The perverse incentive: researchers who discover a broken metric are punished for fixing it. Continuing with a known-broken metric becomes the only charter-compliant path.

---

## Proposed Change

**Current:**
> G4 Test rigidity — thresholds cannot be adjusted after seeing results. Ever.

**Proposed:**
> G4 Test rigidity — thresholds cannot be adjusted to chase results. If a threshold must be revised after data collection begins, the revision must satisfy all four conditions: (a) motivated by a pre-registered protocol for construct invalidation or a discovered measurement flaw, not by the direction of observed results; (b) documented with the specific flaw discovered, independent of whether the revision helps or hurts the current hypothesis; (c) applied without knowledge of whether the revision favors or disfavors the hypothesis — if outcome direction is already known, the threshold revision is prohibited; (d) logged as a protocol deviation with full reasoning, permanently attached to the artifact. Unplanned post-hoc adjustments remain prohibited.

---

## Skeptical Residue

**Strongest objection:** Any escape hatch, however well-specified, becomes the primary exploit route for motivated reasoning. "I discovered my metric was flawed" is the oldest post-hoc rationalization in science. Four conditions are not hard to satisfy after the fact if the researcher is motivated to satisfy them.

**Response:** This is the strongest objection and it is correct as a general principle. The proposed mitigation is condition (c): the revision is only permissible if the outcome direction is *not yet known*. A researcher who has already seen "the treatment group performed better" cannot subsequently claim construct invalidation without knowing whether the revision helps or hurts them. The window for legitimate revision closes when outcome direction becomes visible.

**What would change confidence:** Evidence that LLMs or humans using this revised G4 produce more post-hoc adjustments than under the absolute version, and that those adjustments correlate with desired outcomes. If the escape hatch is exploited more often than it is legitimately used — even with condition (c) — then the absolute prohibition is the safer rule.

---

## Gate Check

- **G2 Bounded scope:** Targets only the single sentence of G4; does not alter other gates or institutions
- **G3 Operational definitions:** The failure mode is observable — any experiment with a discovered broken metric produces a concrete conflict with the current text; another LLM reading the same scenario would identify the same tension
- **G4 Test rigidity:** The proposed change produces a verifiably different behavioral outcome: an assistant encountering a broken metric now produces a documented protocol deviation instead of either aborting or silently continuing with invalid data
- **G5 Mechanism:** Current text fails because it treats all post-hoc threshold changes as epistemically equivalent. Construct invalidation and result-chasing have different signatures — the former is discoverable independent of outcome direction, the latter is not. G4 conflates them by banning both.
