## Proposal: Resolution — Evidence Hierarchy as Procedural Ladder with Empirical Anchoring and Override Rule

**Date:** 2026-06-05
**Type:** Refinement (structural)
**Target:** §5 Evidence Hierarchy
**Charter version reviewed:** v2.2
**Model Confidence Note:** Kimi is prone to over-index on formal taxonomies and may propose structural elegance that adds cognitive load without operational benefit. Kimi may under-weight the practical value of simplicity in live-session tools. Kimi may also over-value epistemological correctness over user adherence.

---

## Current Text

> ### 5 — Evidence Hierarchy
> 
> Evidence is tracked per claim, not per intuition.
> 
> - E5: Fully reproducible — code + data + tests
>   - documentation + independent verification
> - E4: Methods-grade artifact — robustness checks
>   - negative controls + preregistered protocol
> - E3: Reproducible experiment or simulation with
> clear pass/fail outcomes
> - E2: Established domain knowledge — explicitly
> cited and sourced
> - E1: Speculation — must include a minimal
> decisive test proposal containing at least one
> named independent variable, at least one named
> dependent variable, and at least one numeric
> threshold constituting a pass or fail outcome.
> A qualitative test proposal does not satisfy E1.
> 
> No claim may be described as E3+ without a
> structured artifact and test results.
> 
> Citation count is not validation.
> Enthusiasm is not evidence.
> Feeling certain is a warning sign.

---

## Problem Statement

The v2.2 Evidence Hierarchy is a linear ladder (E1–E5) that measures procedural rigor and reproducibility. Two independent critiques (Kimi, Gemini) have identified that this structure conflates procedural rigor with epistemic strength, and that its boundary definitions (especially E2) are insufficient to prevent garbage-in-garbage-out at the top of the ladder.

The failure modes:

1. **Goodhart's Law at E5:** A claim can reach E5 by being perfectly reproducible while built on unvalidated assumptions. The hierarchy rewards the demonstrable property (reproducibility) over the harder-to-verify property (empirical grounding). An assistant optimizing for E-level will prioritize making things reproducible rather than making them valid.

2. **E2 citation vulnerability:** "Explicitly cited and sourced" permits hallucinated citations, single-source claims, and unverified sources to satisfy the second-highest evidence level. A hallucinated DOI with a plausible title satisfies E2 as written.

3. **No conflict resolution mechanism:** When an E5 simulation contradicts E2 domain knowledge, the hierarchy offers no guidance. The linear ordering implies E5 > E2, which can lead to endorsing a reproducible but wrong claim over a well-sourced but non-reproducible fact.

These are not three separate problems. They are symptoms of the same structural issue: the hierarchy measures one dimension (procedural rigor) but is used as if it measures total evidence quality.

---

## Analysis of Alternatives

**Option A — Defend linear ladder, fix E2 only:** This addresses the citation vulnerability but leaves the Goodhart incentive and the E5/E2 conflict unresolved. The hierarchy would still train assistants to treat reproducibility as epistemic strength.

**Option B — Full 2D matrix (Reproducibility × Empirical Anchoring):** This would replace E1–E5 with a grid (e.g., Low/Med/High Reproducibility × Low/Med/High Empirical Grounding). This is epistemically correct but operationally intractable. In live sessions, operators and assistants would need to track two ratings per claim, decide how they interact, and resolve conflicts. The cognitive load would likely cause the system to be ignored.

**Option C — Scope declaration only:** Declare that the hierarchy is procedural, not epistemic, and trust operators to apply judgment. This is honest but ineffective. It does not change assistant behavior; it merely disclaimers it.

**Chosen approach:** Hybrid — keep the linear ladder as the primary interface (procedural rigor), add empirical anchoring requirements to the highest levels, strengthen E2 boundaries, and add one explicit override rule for the E5/E2 conflict. This preserves the ladder's cognitive simplicity while addressing the known failure modes.

---

## Proposed Change

Replace the current §5 Evidence Hierarchy and its surrounding text with:

> ### 5 — Evidence Hierarchy
> 
> Evidence is tracked per claim, not per intuition.
> 
> The hierarchy measures **procedural rigor** — how well a claim is structured, tested, and documented. It does not measure **empirical validity** — whether the claim is true. A claim can be procedurally perfect and empirically wrong.
> 
> - **E5: Fully reproducible** — code + data + tests + documentation + independent verification. **Must include an explicit empirical anchoring statement: what real-world observations or established principles justify the model's core assumptions? If the assumptions are purely theoretical, the claim must be labeled as "E5 — unanchored."**
> - **E4: Methods-grade artifact** — robustness checks + negative controls + preregistered protocol
> - **E3: Reproducible experiment or simulation** — clear pass/fail outcomes
> - **E2: Established domain knowledge** — **requires at minimum two independent, verifiable sources (URL or DOI, cross-checkable at time of claim). The claim extracted from each source must be documented: what the source asserts, its scope, and any known bounding conditions. A single citation, even if accurate, does not satisfy E2.**
> - **E1: Speculation** — must include a minimal decisive test proposal containing at least one named independent variable, at least one named dependent variable, and at least one numeric threshold constituting a pass or fail outcome. A qualitative test proposal does not satisfy E1.
> 
> **Override Rule — E2 Supersedes E3–E5 on Construct Validity**
> 
> If an E3–E5 claim's operational definitions are demonstrably unvalidated (no prior evidence that the metric captures the intended construct), or its core assumptions directly contradict established domain knowledge (E2), the E2 claim takes precedence for evaluation purposes. The E3–E5 claim retains its procedural label but must be flagged as "empirically unanchored" and cannot be used as the sole basis for a CONVERGE decision.
> 
> No claim may be described as E3+ without a structured artifact and test results.
> 
> Citation count is not validation.
> Enthusiasm is not evidence.
> Feeling certain is a warning sign.

---

## Skeptical Residue

The strongest objection is that the E5 empirical anchoring requirement and the override rule add complexity to the highest level of the hierarchy, exactly where the charter should be most streamlined. An assistant trying to produce an E5 artifact now has an additional documentation burden (empirical anchoring statement) and a new failure mode (being overruled by E2). This could disincentivize E5 work or create paralysis.

A second objection: The E2 two-source requirement creates overhead for uncontroversial foundational knowledge. An assistant stating "gravity accelerates objects at 9.8 m/s² near Earth's surface" would need two sources. In practice, assistants may either (a) waste time finding redundant citations for obvious facts, or (b) treat everything as "conversational background" to avoid the requirement, eroding the boundary between background and evidence.

A third objection: The override rule requires the assistant to judge whether a claim's assumptions "directly contradict" established knowledge. This is itself a judgment call that could be wrong, and it creates a new conflict resolution protocol that may be invoked more often than intended.

To conclude this resolution is wrong, I would need to see that:
1. The E5 empirical anchoring requirement is routinely ignored or treated as boilerplate
2. The E2 two-source requirement causes more false negatives (rejecting valid claims) than false positives (catching bad ones)
3. The override rule is invoked so frequently that it destabilizes the hierarchy's primary function as a procedural ladder

If any of these three conditions materialize in practice, the simpler Option A (fix E2 only, scope declaration for the rest) would be preferable.

---

## Gate Check

- **G2 Bounded scope:** Targets only §5 Evidence Hierarchy. Does not alter other institutions. The override rule is scoped to one specific conflict (E2 vs E3–E5 on construct validity).
- **G3 Operational definitions:** The E2 criteria are countable (≥2 sources, verifiable). The E5 empirical anchoring requirement is observable (presence/absence of a statement). The override rule has a testable trigger (unvalidated operational definitions or direct contradiction with E2).
- **G4 Test rigidity:** The criteria are fixed before evaluating a claim. Two sources is a hard threshold. The override rule is triggered by specific, pre-defined conditions, not post-hoc rationalization.
- **G5 Mechanism:** The current text fails because it treats procedural rigor as a proxy for total evidence quality. This creates a Goodhart incentive (optimize for reproducibility, neglect validity) and leaves the E5/E2 conflict unresolved. The proposed changes address the mechanism by (a) forcing E5 to demonstrate empirical grounding, (b) strengthening E2 so it can function as a validity check, and (c) adding an explicit conflict-resolution rule so the hierarchy doesn't silently endorse wrong-but-reproducible claims.
