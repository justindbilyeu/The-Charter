# Proposal: Evidence Hierarchy Conflates Reproducibility with Epistemic Strength

**Date:** 2026-06-05
**Type:** Challenge
**Target:** §5 Evidence Hierarchy
**Charter version reviewed:** v2.1
**Model Confidence Note:** Kimi tends to over-index on formal taxonomies and may see hierarchy problems where practitioners navigate fine with intuition; prone to inventing structural elegance that solves no real operational problem; may miss that the linear hierarchy is intentionally simple to keep cognitive load low.

---

## Current Text

> - E5: Fully reproducible — code + data + tests + documentation + independent verification
> - E4: Methods-grade artifact — robustness checks + negative controls + preregistered protocol
> - E3: Reproducible experiment or simulation with clear pass/fail outcomes
> - E2: Established domain knowledge — explicitly cited and sourced
> - E1: Speculation — must include a minimal decisive test proposal
>
> No claim may be described as E3+ without a structured artifact and test results.

---

## Problem Statement

The hierarchy treats E5 > E4 > E3 > E2 > E1 as a single linear scale of epistemic strength. But **reproducibility** and **empirical grounding** are orthogonal quality dimensions — not a single axis.

**Example 1:** A fully reproducible simulation (E5) with garbage boundary conditions and unvalidated assumptions is weaker evidence than a single, well-documented historical observation (E2) that cannot be replicated but is directly grounded in the actual phenomenon. The simulation is high on reproducibility; low on empirical grounding. The historical observation is the reverse.

**Example 2:** A methods-grade artifact (E4) with perfect negative controls measuring a proxy variable with no established construct validity is weaker than established domain knowledge (E2) about the actual phenomenon of interest.

**The failure mode the hierarchy creates:** It trains the assistant to prefer "reproducible but wrong" over "non-reproducible but right." More specifically, it creates a Goodhart's Law incentive — optimize for reproducibility (which is procedurally easy to demonstrate) at the expense of empirical validity (which is harder to verify). An E5 label creates a false sense of security by signaling high epistemic confidence when it only confirms high methodological tidiness.

**Why this cannot be fixed with a text substitution:** Redesigning the evidence framework requires understanding how the hierarchy is actually used in practice — whether operators treat E5 as a ceiling or a floor, whether the hierarchy is used for claim labeling or for prioritization, and whether the linear ordering causes misclassification in real sessions. None of this is known. A proposed fix without this data would be premature.

---

## Proposed Change

No proposed fix — problem statement is the artifact.

A valid resolution would require one of:

1. **A two-dimensional evidence matrix** — one axis for reproducibility (E1–E5 as currently defined), one axis for empirical grounding (independently scaled). Claims are located on the matrix, not on a single ladder.

2. **Explicit override rules** — defining when a lower-E claim should supersede a higher-E claim (e.g., "an E2 domain knowledge claim directly measuring the target phenomenon supersedes an E5 simulation of a proxy").

3. **Empirical calibration** — data from actual charter sessions showing whether the linear hierarchy causes systematic misclassification before proposing a structural change.

None of these can be proposed without knowing the operational context. This challenge is filed to establish the structural problem and open the question for Review Cycle 2.

---

## Skeptical Residue

**Strongest objection:** The hierarchy is intentionally a practical heuristic, not an epistemology. In the vast majority of cases, E5 claims are in fact stronger than E2 claims, and the exceptions are edge cases. A simple linear scale keeps cognitive overhead low and keeps operators from drowning in nuance. Two dimensions may be structurally correct but operationally worse.

**Response:** This is a strong and possibly decisive objection. The hierarchy's simplicity is a real value. The challenge does not propose eliminating it — it proposes examining whether its simplicity creates a systematic blind spot. The specific failure mode (reproducible-but-wrong preferred over non-reproducible-but-right) is not a rare edge case in scientific practice; it is a known and documented failure mode of over-reliance on methodological tidiness. Whether it is common enough in *this charter's operational context* to warrant the complexity of a fix is an open empirical question.

**What would change confidence:** Concrete examples from actual charter usage where the linear hierarchy caused an assistant to overrate a reproducible but empirically invalid claim, or underrate a non-reproducible but well-grounded one. If the hierarchy works correctly in practice despite being structurally imprecise, the structural problem may not be worth solving.

---

## Gate Check

- **G2 Bounded scope:** Targets only §5 and the single linear ordering assumption; does not propose changes to other institutions
- **G3 Operational definitions:** The problem is observable — two claims at the same E-level can have opposite epistemic merit; another LLM comparing a broken E5 simulation to a solid E2 meta-analysis would identify the same tension
- **G4 Test rigidity:** If a fix were adopted, it would produce a verifiably different behavioral outcome: assistants would stop automatically preferring E5 over E2 in cases where reproducibility is high but empirical grounding is weak. Since no fix is proposed, the gate is satisfied by the problem statement itself being a testable claim about misclassification.
- **G5 Mechanism:** Current text fails because it collapses two independent quality dimensions into one ordinal scale, creating a Goodharting incentive: optimize for the measurable dimension (reproducibility) at the expense of the harder-to-verify dimension (empirical validity)
