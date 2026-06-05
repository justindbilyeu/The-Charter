# Proposal: Scope the Constitutional Principle to empirical inquiry

**Date:** 2026-06-05
**Type:** Refinement
**Target:** Constitutional Principle; §1 The Structuring Contract
**Charter version reviewed:** v2.1

---

## Current Text

> No Claims Without Tests.
> No Tests Without Thresholds.
> No Thresholds Without Numbers.
> No Numbers Without a Run.

> No idea is ready until it compiles into a structured artifact.
> A valid artifact MUST contain: [...] Test specification [...] Success/failure criteria: ≥2 numeric thresholds for rejection, set BEFORE running

---

## Problem Statement

The charter's gate language — "tests," "thresholds," "numbers," "a run" — implicitly assumes empirical inquiry: claims about how the world behaves, validated through observation or experiment.

This excludes entire domains where rigorous inquiry does not work this way:

- **Formal claims** (mathematics, logic): validated by proof, not experiment. A proof is a demonstration, not a test. There are no thresholds. There is no run.
- **Interpretive claims** (historical analysis, legal argument, philosophical reasoning): validated by method and source criticism, not numeric thresholds.

As written, the Constitutional Principle would reject a proof of Fermat's Last Theorem as failing G1 (no numeric thresholds) and G4 (no test). That is not a rigorous outcome — it is a category error.

The failure mode this enables: an LLM applying this charter to a formal or interpretive question will either (a) misapply experimental gate language to a domain where it doesn't apply, or (b) correctly identify that the gates fail and refuse to proceed — blocking valid rigorous work.

---

## Proposed Change

Add a scope note to the Constitutional Principle section:

**Current:**
> No Claims Without Tests. No Tests Without Thresholds. No Thresholds Without Numbers. No Numbers Without a Run.

**Proposed:**
> No Claims Without Tests. No Tests Without Thresholds. No Thresholds Without Numbers. No Numbers Without a Run.
>
> *Scope: This principle governs empirical inquiry — claims about observable phenomena, testable through experiment or measurement. For formal claims (mathematical, logical), "test" maps to proof and demonstration. For interpretive claims (historical, legal, philosophical), "test" maps to method, source criticism, and structured argument. The spirit — no claim without a validation procedure, no threshold without precommitment — applies across all domains. The specific gate language applies to empirical work.*

This keeps the constitutional principle intact while removing the implicit scope restriction that currently causes the charter to misfire outside experimental science.

---

## Skeptical Residue

**Strongest objection:** Adding scope carve-outs creates escape hatches. "My claim is interpretive" becomes a way to avoid hard gates.

**Response:** This is a real risk. The mitigation is that the proposed addition preserves the spirit — *no claim without a validation procedure, no threshold without precommitment* — while mapping it to domain-appropriate methods. The gate structure still applies; only the specific instantiation changes. An LLM applying this correctly would still demand a proof procedure for a mathematical claim, not simply accept it as validated.

**What would change my confidence:** If a concrete example could be constructed where the scope note genuinely weakens scrutiny on an empirical claim — i.e., where "interpretive" is plausibly misapplied to shield an empirical claim from gates. I could not construct such a case.

---

## Gate Check

- **G2 Bounded scope:** Targets the Constitutional Principle and §1 specifically; does not propose restructuring the charter's gate system
- **G3 Operational definitions:** The failure mode is observable — the word "tests" excludes proofs; another LLM reviewing the charter would identify the same gap
- **G4 Test rigidity:** With this addition, an LLM would not apply experimental gates to a mathematical proof; without it, it would. The behavioral difference is verifiable.
- **G5 Mechanism:** The mechanism of failure is substitution of domain — "empirical validation" treated as equivalent to "rigorous validation." The constitutional principle's language is the site of the substitution.
