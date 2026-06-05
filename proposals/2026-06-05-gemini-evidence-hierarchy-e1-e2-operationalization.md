# Proposal: Add operational boundary criteria to Evidence Hierarchy E1 and E2

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §5 Evidence Hierarchy — E1 and E2 definitions
**Charter version reviewed:** v2.1
**Model Confidence Note:** Gemini is prone to missing real-world citation nuances and the messy nature of human academic literature; prone to over-indexing on strict mathematical constraints that may make adoption of foundational literature unnecessarily cumbersome.

---

## Current Text

> - E2: Established domain knowledge — explicitly cited and sourced
> - E1: Speculation — must include a minimal decisive test proposal

---

## Problem Statement

E1 and E2 lack operational boundary criteria, creating quality control failures before claims reach the E3 experimental stage.

**E2 vulnerability — citation without validation:** "Explicitly cited and sourced" permits the assistant to accept hallucinated academic papers, non-peer-reviewed blog posts, or low-quality sources as valid E2 domain knowledge. The charter states elsewhere that "Citation count is not validation" — yet E2 establishes citation as the *sole* criterion for acceptance. A hallucinated DOI with a plausible title satisfies E2 as written.

**E1 vulnerability — qualitative tests satisfy a quantitative charter:** "A minimal decisive test proposal" is un-numeric and un-bounded. An E1 claim can satisfy the requirement with a test like "survey users to see if they like it" — which lacks an independent variable, a dependent variable, and any numeric threshold. This violates the Constitutional Principle directly: *"No Tests Without Thresholds. No Thresholds Without Numbers."* E1's test requirement is the last checkpoint before a claim enters the evidence hierarchy; if it admits qualitative tests, the entire ladder is undermined.

---

## Proposed Change

**E2 — tighten citation to require minimal source verification:**

**Current:**
> E2: Established domain knowledge — explicitly cited and sourced

**Proposed:**
> E2: Established domain knowledge — requires at minimum two independent, verifiable sources (URL or DOI, cross-checkable at time of claim). The claim extracted from each source must be documented: what the source asserts, its scope, and any known bounding conditions. A single citation, even if accurate, does not satisfy E2.

**Note:** The proposal filed here is intentionally lighter than Gemini's original suggestion (which required sample size extraction and replication rates). The lighter version addresses the hallucination and single-source vulnerability without imposing a full academic citation protocol on every foundational claim. The heavier version may be warranted for E4 artifacts.

**E1 — require numeric test specification:**

**Current:**
> E1: Speculation — must include a minimal decisive test proposal

**Proposed:**
> E1: Speculation — must include a minimal decisive test proposal containing: at least one named independent variable, at least one named dependent variable, and at least one numeric threshold that would constitute a pass or fail outcome. A qualitative test proposal (e.g., "observe whether users respond positively") does not satisfy E1.

---

## Skeptical Residue

**Strongest objection (E2):** Requiring two independent sources with documented scope creates prohibitive overhead for uncontroversial foundational knowledge — basic physics, standard software architecture patterns, well-established mathematical facts. The assistant would need to produce citation chains for claims that any informed reader would accept without them, degrading conversational velocity.

**Response:** The two-source requirement applies to claims used as evidence in a research artifact, not to conversational background. The distinction between "claim being advanced as E2 evidence" and "conversational context" should govern when the requirement applies. This boundary is not drawn in the current proposal and may need its own refinement.

**Strongest objection (E1):** Requiring IV/DV/threshold at E1 may be premature — E1 is speculation, and the purpose of the test proposal is directional (what would we look for?) rather than fully preregistered. Over-specifying E1 conflates early-stage test design with E3+ rigor.

**Response:** The Constitutional Principle already requires numeric thresholds universally. E1 is not exempt. The IV/DV/threshold requirement is the minimum instantiation of "No Thresholds Without Numbers" at the speculation stage. If the Constitutional Principle has an E1 exemption, that exemption should be explicit — not implied by a vague test requirement.

---

## Gate Check

- **G2 Bounded scope:** Targets E1 and E2 definitions in §5 only; does not alter E3–E5 or the evidence tracking principle
- **G3 Operational definitions:** Adds countable criteria — source count, verifiability, IV/DV presence, numeric threshold presence — each observable by another LLM reviewing the same artifact
- **G4 Test rigidity:** The criteria (≥2 sources, named variables, numeric threshold) are fixed before evaluating whether a claim satisfies E1 or E2
- **G5 Mechanism:** Current text fails because it allows non-rigorous text strings (a plausible-sounding citation, a qualitative test description) to satisfy criteria for structural progression, bypassing the core mission of preventing narrative coherence from substituting for rigor
