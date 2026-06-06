# Proposal: Define constraint health as a weighted composite metric (competing approach to G-08)

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §3 Coherence Controller — constraint health definition
**Charter version reviewed:** v2.2
**Model Confidence Note:** Grok's architectural strength is system monitoring and signal weighting. The risk is introducing numeric precision that implies calibration confidence the proposal does not have. The threshold (0.6) and component weights (0.4/0.3/0.3) are stated without empirical grounding — this is explicitly acknowledged in the skeptical residue. The proposal is filed as a competing approach to `2026-06-06-claude-g08-constraint-health-metric.md`, which recommends observable conditions (Option B) rather than a numeric metric.
**Source:** Grok structural analysis of MACHINE_SPEC.md gap G-08

---

## Current Text

> The assistant monitors **constraint health** during structuring and explicitly decides:
>
> **CONVERGE** — structure is tight, gates pass, proceed to test.
> **DIVERSIFY** — inject alternative explanations, add skeptical probes, challenge assumptions before proceeding
> **RESTART** — recompile with explicit defect list, do not patch around a structural flaw

---

## Problem Statement

"Constraint health" is the Coherence Controller's decision input but is never defined as a measurable quantity. The controller cannot compute what it is asked to monitor. (This is also the substance of `2026-06-06-claude-g08-constraint-health-metric.md`.)

The competing proposal (G-08, Option B) addresses this by replacing "constraint health" with three observable boolean/count conditions. This proposal offers the alternative: define constraint health as a numeric composite score, making the CONVERGE/DIVERSIFY/RESTART decision thresholds explicit and adjustable.

The core argument for a numeric metric over observable conditions: observable conditions are themselves weighted implicitly when the controller makes a state decision. Making the weighting explicit — even if the initial weights are provisional — forces the weighting to be auditable and correctable. An implicit weighting that drives state decisions is a hidden model; a numeric metric with explicit weights is a visible one.

---

## Proposed Change

Define constraint health as a composite score H ∈ [0, 1], updated at each gate evaluation cycle:

> **Constraint Health Score**
>
> H = (0.4 × H_hyp) + (0.3 × H_obj) + (0.3 × H_traj)
>
> Where:
> - **H_hyp** = 1 if two or more competing hypotheses are active in the current artifact; 0 otherwise
> - **H_obj** = 1 if at least one new objection was raised in the last two gate evaluation cycles; 0 otherwise
> - **H_traj** = 1 if the last three state transitions include at least one DIVERSIFY or RESTART; 0 if all three were CONVERGE
>
> **Threshold rules:**
> - H ≥ 0.6: CONVERGE is permitted if gate conditions are also satisfied
> - H < 0.6: DIVERSIFY is required regardless of gate outcomes
>
> H is computed at each gate evaluation cycle and logged in the session record. It is reported in State Compression under "Constraint Health."

**Note on initial weights and threshold:** The values 0.4/0.3/0.3 and the threshold 0.6 are provisional. They represent a prior about relative importance (hypothesis diversity is the dominant signal; objection freshness and trajectory each contribute equally). These values should be treated as pre-registered starting points subject to calibration once simulation data is available. They must not be adjusted mid-session.

---

## Skeptical Residue

**Strongest objection — the threshold violates the charter's own Constitutional Principle:** The charter requires "No Thresholds Without Numbers. No Numbers Without a Run." The threshold of 0.6 is a number without a run. There is no calibration data supporting 0.6 as a meaningful boundary; it could be 0.5 or 0.7 and the proposal provides no basis for distinguishing them. Filing a threshold without a run is the exact failure mode the charter is designed to prevent — applied to the charter itself. Similarly, H_hyp weighted at 0.4 over H_obj at 0.3 asserts that hypothesis diversity matters more than objection freshness. This may be correct, but it is asserted, not argued.

**Response:** The alternative is the status quo: an undefined "constraint health" that drives state decisions with no visible weighting at all. A calibration-pending numeric metric is preferable to an invisible one — because it can be calibrated. Option B (observable conditions) avoids this critique by removing numeric weights entirely, but trades calibrability for precision. The human maintainer must decide whether a visible-but-uncalibrated metric is better than no metric. The proposal is filed as a competing approach, not as a superior one.

**What would change confidence:** Simulation data showing that H < 0.6 consistently identifies sessions that subsequently produce low-quality artifacts, and H ≥ 0.6 sessions produce high-quality ones. Without that data, the threshold is structural scaffolding, not a calibrated decision boundary.

---

## Gate Check

- **G2 Bounded scope:** Targets only the constraint health definition in §3. Does not alter DIVERSIFY trigger conditions, gate specifications, or any other section beyond adding H to the State Compression fields.
- **G3 Operational definitions:** H_hyp, H_obj, and H_traj are each binary, observable from session state. H is a scalar computable from them. "Two or more competing hypotheses active" requires a hypothesis count field in the structured_artifact schema — this is a dependency this proposal introduces.
- **G4 Test rigidity:** A session where H < 0.6 and the controller selects CONVERGE is a verifiable protocol violation. H is logged at each gate cycle and auditable from the session record. The threshold is pre-registered and cannot be adjusted mid-session without invalidating the evaluation.
- **G5 Mechanism:** The gap fails because a controller whose decision input is undefined cannot be audited, compared across sessions, or improved. The mechanism of this proposal: make the implicit weighting explicit and logged. The residual risk is that the weights are wrong — but wrong-and-visible is correctable; undefined-and-invisible is not.
