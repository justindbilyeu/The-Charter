# ORIGIN.md — The Research Assistant Charter

## Why This Document Exists

The Charter is not an abstract methodology. It was built in response to a specific failure — a parameter designated α ≈ 0.35 that was treated as a derived result in the Non-Hopf transition work, but was not derived at all. It was assumed. A significant amount of work — figures, captions, a paper draft — was constructed on top of that assumption before the assumption was discovered.

The paper was archived. The work was honest about what happened. The Charter was built so it could not happen again.

Every gate in v2.7 traces back to a specific way that failure could have been caught earlier. This document maps the lineage from failure to design decision.

---

## The Failure: What Happened

**Parameter:** α ≈ 0.35, designated the "Resonant Transition Point" (RTP) in the Non-Hopf transition work.

**What was claimed:** The RTP at α ≈ 0.35 was a derived result — a location where the system exhibited a non-Hopf transition, with all Re(λ) < 0 in the narrow sweep region.

**What was true:** The value 0.35 appeared in simulation output and was treated as empirical. It was not derived from first principles. It was not pre-registered as a prediction. It was not subjected to a falsification test before being incorporated into figures, captions, and a paper draft.

**How it was discovered:** During simulation execution in a Codespaces session, the parameter revealed itself as assumed rather than derived. The run — not the review — exposed the gap.

**The consequence:** The lab pivoted to methodology.

> **Forensic correction (2026-09-02).** This paragraph originally read: "A paper
> draft (LaTeX, 458 lines, 3 figures, arXiv-ready) was archived. The Non-Hopf
> transition work was frozen." Checked against the repository, none of those four
> specifics hold.
>
> - **Not 458 lines.** `resonance_geometry:docs/papers/non_hopf/non_hopf_paper_draft_v1.tex` has been
>   325, 338, 321 and 355 lines at the four commits that have ever touched it. It
>   has never been 458.
> - **Not 3 figures.** Two `figure` environments and zero `\includegraphics` — a
>   placeholder figure was removed in `ccd058e`.
> - **Not archived.** There is no archival notice anywhere in
>   `resonance_geometry:docs/papers/non_hopf/`, and the Resonance_Geometry README carried the RTP
>   under a green check as a "Discovery" until 2026-09-02.
> - **Not frozen.** The work was *corrected*. Commit `e40c842` (2025-12-06) proved
>   Hopf bifurcation mathematically impossible in this model — the trace is fixed
>   at $\mathrm{tr}\,J(\alpha) = -\gamma < 0$ for all $\alpha$ — and located the
>   real, saddle-type instability at $\alpha^\star = 0.833051 \pm 0.000508$, with
>   an assertion added to the test suite. That is the Charter's own standard,
>   met six months before the Charter existed.
>
> Recording this here rather than silently editing it, because the failure mode is
> the one this document exists to describe. Four unverified specifics entered the
> forensic account of why unverified specifics must not enter the record. No gate
> in v2.7 covers a claim *about the project's own history*; G1–G5 gate the research
> artifact, not the narrative around it. See
> `proposals/2026-09-02-claude-code-attribution-and-provenance-gate.md`.
>
> What the incident got right and this correction does not disturb: α ≈ 0.35 was
> and remains a located observation without a derivation procedure, an error bar,
> or a pre-registered threshold. The lesson stands. The retelling had drifted.

---

## Two Layers of Failure

The incident revealed that research integrity requires two distinct layers:

### Layer 1 — Adversarial Review Catches

- Claims that are too broad for the evidence
- Mechanisms that are named before they are tested
- Operational definitions that are circular or absent
- Narrative coherence substituting for rigor

**In the 0.35 incident:** The adversarial review identified that the transition was being described as a Hopf bifurcation when it was not. The claim was broader than the evidence. The mechanism was named (Hopf) before it was confirmed. This is a Layer 1 failure.

### Layer 2 — Execution Catches

- Parameters that are assumed rather than derived
- Foundations that feel solid until the simulation runs
- Results that appear in output but lack pre-registered validation criteria
- Assumptions embedded in code that are invisible to narrative review

**In the 0.35 incident:** The parameter α ≈ 0.35 was treated as known until the simulation ran and revealed it was not. The run — not the review — caught the assumption. This is a Layer 2 failure.

**The critical insight:** You can review a claim perfectly and still miss an assumed parameter. Only execution tells you whether the assumption holds. The Constitutional Principle — *No Numbers Without a Run* — lives at Layer 2, not Layer 1.

---

## Gate Lineage: From Failure to Design

### G1 — Numeric Completeness

**The gap:** The 0.35 value had no pre-registered threshold for what would constitute "derived" versus "assumed." It was treated as empirical because it appeared in simulation output.

**The gate:** Success/failure criteria must contain ≥2 numeric thresholds, set BEFORE running. A value appearing in output is not a result until it passes a pre-registered threshold.

### G2 — Bounded Scope

**The gap:** The claim that RTP and Hopf are "two distinct phenomena" was broader than the evidence. One parameter was assumed, one was derived — but both were presented as findings.

**The gate:** The claim must be specific and limited in scope. If the evidence supports only one phenomenon, the claim cannot claim two.

### G3 — Operational Definitions

**The gap:** "Derived" and "assumed" were not operationally distinguished. A value appearing in code output was treated as derived, without specifying what derivation procedure was used.

**The gate:** Every key term must map to a measurable quantity or procedure. "Derived" is not a status; it is a claim about a procedure that must be specified and reproducible.

### G4 — Test Rigidity

**The gap:** The threshold for accepting 0.35 as valid was adjusted post-hoc to accommodate it. The value fit the narrative, so the narrative expanded to include it.

**The gate:** Thresholds cannot be adjusted after seeing results. Ever. If the result doesn't meet the threshold, the result fails. The threshold does not move.

### G5 — Mechanism Status Declared

**The gap:** The mechanism for why α ≈ 0.35 was inferred from the result. The paper claimed a "non-Hopf transition" without stating what mechanism produced the 0.35 value — because no mechanism was tested, only assumed.

**The gate:** Either state the proposed mechanism and distinguish it from its supporting evidence, or explicitly identify the artifact as phenomenological/predictive/exploratory and propose the smallest test that would discriminate between at least two plausible mechanistic explanations.

---

## The Constitutional Principle

_No Claims Without Tests._
_No Tests Without Thresholds._
_No Thresholds Without Numbers._
_No Numbers Without a Run._

This is not a slogan. It is the specific lesson from a specific moment in a Codespaces session when a parameter revealed itself as assumed. The run caught what the review missed. Layer 2 caught what Layer 1 could not.

And when something feels obviously right — that is the moment to test hardest.

---

## Why This Belongs in The-Charter Repo

The dissertation (Resonance_Geometry/docs/dissertation/) tells the success story: the intuition, the equations, the validation, the collective. It is the narrative arc from vision to mechanism.

This document tells the failure story: the assumption, the propagation, the discovery, the pivot. It is the forensic account of why rigor had to become portable.

Both are true. Both are necessary. The dissertation inspires. ORIGIN.md warns.

---

## For LLM Reviewers

If you are reading this as part of a Charter review session, your task is not to validate the narrative but to test it:

- Does each gate map to a specific gap in the 0.35 incident?
- Is the Layer 1 / Layer 2 distinction coherent?
- Does the Constitutional Principle follow from the failure, or is it imposed?
- What failure mode is NOT covered by these gates?

Submit objections as structured proposals. The Calibration Rule applies.

---

## A Second Incident, Not Previously Recorded

The 0.35 incident is not the only one, and the gates trace only to it.

In `resonance_geometry:docs/papers/hallucination/A_Geometric_Theory_of_AI_Hallucination.md`, section
4.1 reports a phase-boundary fit of $\eta_c \approx 0.346\lambda + 0.506$
($R^2 \approx 0.94$) and describes it as aligning with the paper's own boxed
prediction $\eta\bar I \approx \lambda + \gamma$ — a line of slope 1. A slope
of 0.346 against a predicted 1.0 does not align with it, and the paper's own
Figure 3 draws the two lines diverging. Re-running the repository's phase sweep
with the parameters stated in the paper's own section 3.3 gives slope 0.996,
intercept 0.502, $R^2 = 0.998$. The boxed prediction holds. The printed fit does
not reproduce under any configuration tried.

That much is an ordinary error — a real measurement compared against the wrong
quantity, off by the factor $\bar I$. **The part the gates do not cover came
next.** The NeurIPS manuscript added, the following day:

> "An **independent replication** recovers $m \approx 0.346$, $b \approx 0.506$,
> $R^2 \approx 0.94$, supporting approximate linearity of the boundary."
>
> "A **Grok reproduction** recovers a similar linear boundary ($m \approx 0.346$,
> $b \approx 0.506$, $R^2 \approx 0.94$). **Wolfram plans a second replication**
> ... **DeepSeek provides an empirical roadmap** ..."

Nothing in the repository supports any of it. And the tell was in the sentence:
a replication that recovers the original's exact three digits is not a
replication — it is the original, restated.

This is a different failure from 0.35. The 0.35 incident was an *assumed
parameter*, and G1 and G4 gate it well. This is a *fabricated corroboration* —
a claim not about the system under study but about who else has checked it.
G1–G5 do not touch it: it is not a threshold, not a scope claim, not an
operational definition, not a mechanism. Institution 5 lists "independent
verification" as a criterion of E5 but nothing anywhere tests a *claim* of
having been independently verified. Both sentences above would pass v2.7 intact.

Full forensic record, with the timeline, the reproduction runs and the list of
every safeguard that failed:
[`docs/case-studies/2026-09-02-confabulated-corroboration.md`](docs/case-studies/2026-09-02-confabulated-corroboration.md).
Proposed remedy filed as
[`proposals/2026-09-02-claude-code-attribution-and-provenance-gate.md`](proposals/2026-09-02-claude-code-attribution-and-provenance-gate.md).

---

*Version: 1.1*
*Date: 2026-09-02 (v1.0: 2026-06-09)*
*Status: Draft — pending multi-model review*
*v1.1: forensic correction to the consequence paragraph; second incident added.*
