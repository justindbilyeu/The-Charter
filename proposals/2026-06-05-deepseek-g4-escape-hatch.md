# Proposal: G4 construct invalidation clause creates formalized loophole for threshold adjustment

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §2 Hard Gates — G4 Test Rigidity
**Charter version reviewed:** v3.0 (draft)
**Model Confidence Note:** DeepSeek's analysis is strong on identifying the formal loophole but may under-weight legitimate construct invalidation scenarios in field or longitudinal research where re-running a test with entirely new data is infeasible. The proposed fix prioritizes protocol integrity over research continuity. This trade-off is correct for the charter's core use case but may be too strict for some research contexts.

---

## Current Text

> **G4 Test rigidity** — thresholds cannot be adjusted to chase results. If a threshold is revised after data collection begins, the revision must be (a) motivated by a pre-registered protocol for construct invalidation, (b) documented with the specific flaw discovered, (c) applied without knowledge of whether the revision helps or hurts the current hypothesis, and (d) logged as a protocol deviation with full reasoning. Unplanned post-hoc adjustments remain prohibited.

Compare v2.2:

> **G4 Test rigidity** — thresholds cannot be adjusted after seeing results. Ever.

---

## Problem Statement

The v3.0 G4 clause was introduced to handle a real scenario: a construct is discovered to be invalid mid-study. V2.2's absolute prohibition offered no remedy — the test had to be abandoned entirely. V3.0 added a conditional escape hatch requiring a pre-registered construct invalidation protocol.

The clause fails because it places no content requirements on the pre-registered protocol. An empty, circular, or vague protocol is currently compliant:

> Pre-registered protocol: "If effect size < 0.2, the construct may be invalid."
> Data observed: effect size = 0.15, original threshold not met.
> Revision invoked: threshold adjusted to 0.10.
> Documentation: "Protocol deviation logged. Construct flaw: original threshold too conservative."

All four conditions (a)–(d) are satisfied. The threshold was adjusted retroactively. G4 was not breached on paper. The result is indistinguishable from p-hacking — threshold adjusted to chase results — while carrying the formal appearance of protocol compliance.

The mechanism of failure is rationalized flexibility: the escape hatch, intended to handle genuine measurement failures, functions identically to the loophole it was meant to prohibit. A pre-registered protocol with no content requirements is paperwork, not a gate.

The "Ever" in v2.2 was load-bearing. Removing it while adding a structurally toothless replacement weakens G4 from an unconditional constraint to a conditional one with no enforceable condition.

---

## Proposed Change

Replace the current G4 with:

> **G4 Test rigidity** — thresholds cannot be adjusted after data collection begins. If a construct invalidation is discovered mid-study, the following procedure applies:
>
> 1. The original test is terminated and recorded as **"invalidated — threshold not applied"** with the specific flaw documented.
> 2. A new test must be pre-registered with new thresholds before any further data collection or analysis.
> 3. New data must be collected, or a held-out validation set (pre-designated before data collection began) must be used. Retroactive threshold adjustment on already-collected data is prohibited without exception.
> 4. The invalidated test and the new test are both reported as part of the research record.
>
> Construct invalidation is not a failure. Retroactive threshold adjustment is.

---

## Skeptical Residue

**Strongest objection:** Requiring entirely new data collection is often infeasible — longitudinal studies, rare populations, expensive experiments. In practice, this fix converts "construct invalidation" from a recoverable event into a study-ending event. Researchers will either hide the invalidation or abandon the construct rather than lose months of data. The cure is worse than the disease.

**Response:** This is a genuine cost. The held-out validation set option partially addresses it — researchers who anticipate construct uncertainty can pre-designate a validation partition before data collection, preserving the ability to retest without new data. For research contexts where held-out sets are impossible, the charter's Constitutional Principle still applies: if a test cannot be re-run cleanly, the claim must be labeled E1 (speculation) with the invalidation documented as the reason. This is honest and auditable. Retroactive threshold adjustment is neither.

**What would change confidence:** A concrete operational definition of a "pre-registered construct invalidation protocol" that is both (1) content-rich enough to prevent gaming and (2) evaluable at time of pre-registration without already knowing the data. If such a definition can be written, the v3.0 escape hatch could be rescued. The burden of proof is on demonstrating that definition is achievable; absent it, the absolute prohibition stands.

---

## Gate Check

- **G2 Bounded scope:** Targets G4 only — specifically the construct invalidation escape hatch added in v3.0. Does not alter G1, G2, G3, G5, or any other section.
- **G3 Operational definitions:** "Threshold not applied" is a binary, observable state. "Held-out validation set pre-designated before data collection" is verifiable from the pre-registration record. The prohibition on retroactive adjustment is checkable by comparing the pre-registered threshold against the applied threshold.
- **G4 Test rigidity (for this proposal):** The proposed replacement produces a strictly different behavioral outcome: threshold adjustment on collected data is unconditionally prohibited. Under v3.0, it is conditionally permitted. A session operating under the proposed text and one operating under v3.0 text will diverge in exactly the case where construct invalidation is invoked.
- **G5 Mechanism:** V3.0 fails because a pre-registered protocol with no content requirements creates no actual barrier to retroactive adjustment. The mechanism of corruption is formal compliance theater: all four conditions can be satisfied by documentation that records the adjustment without constraining it. The proposed fix removes the conditional path entirely, making construct invalidation a study-termination event rather than a threshold-revision event.
