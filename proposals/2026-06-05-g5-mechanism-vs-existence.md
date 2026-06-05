# Proposal: Separate mechanism from existence in G5

**Date:** 2026-06-05
**Type:** Refinement
**Target:** §2 Hard Gates, G5
**Charter version reviewed:** v2.1

---

## Current Text

> G5 Mechanism declared — we can explain HOW this works, not just that it does. If we cannot, we propose the smallest test that would reveal the mechanism.

---

## Problem Statement

G5 conflates two distinct epistemic questions:

1. **Does this effect exist?** (existence claim)
2. **Why does this effect occur?** (mechanistic claim)

These are separable. Historically, many real, reproducible effects were validated before their mechanisms were understood:

- Gravity: Newton described the law before anyone understood the mechanism (resolved ~300 years later by general relativity)
- Mendelian inheritance: Mendel's laws preceded any understanding of DNA or chromosomes
- Aspirin: used for decades before cyclooxygenase inhibition was identified
- Superconductivity: observed in 1911, mechanism not understood until BCS theory in 1957

In each case, a strict reading of G5 as written ("we can explain HOW this works") would have rejected the finding as failing the gate.

The exception clause — "If we cannot, we propose the smallest test that would reveal the mechanism" — partially mitigates this. But the gate header still reads as a requirement: "mechanism declared" implies mechanism is *known* and *stated*, not merely *sought*. The exception is buried, and the header wins in a fast read.

The result: G5 as written risks rejecting valid E3+ claims because their mechanism is not yet understood, conflating "mechanism unknown" (epistemically acceptable) with "mechanism undeclared" (the actual gate failure).

---

## Proposed Change

Rewrite G5 to gate on transparency of mechanism status, not on mechanism being known:

**Current:**
> G5 Mechanism declared — we can explain HOW this works, not just that it does. If we cannot, we propose the smallest test that would reveal the mechanism.

**Proposed:**
> G5 Mechanism status declared — the state of mechanistic understanding is explicitly stated. If mechanism is known: declare it. If mechanism is unknown: (a) confirm the effect is reproducible independent of mechanism, and (b) propose the smallest test that would reveal the mechanism. Unknown mechanism is not a gate failure. Undeclared mechanism status is.

This preserves G5's intent — forcing honesty about *how* something works — while removing the implicit requirement that mechanism be understood before a finding can proceed.

---

## Skeptical Residue

**Strongest objection:** "Unknown mechanism" becomes a universal exit. "We don't know why it works" + "here's a test we'll never run" satisfies the gate forever, enabling sloppy science to proceed indefinitely.

**Response:** The proposed language requires two things when mechanism is unknown: (a) reproducibility independent of mechanism — the effect must stand on its own evidence — and (b) a concrete next-test proposal, not an open-ended gesture. This raises the bar compared to the current exception clause, which only requires proposing a test without requiring the effect to already be reproducible.

**What would change my confidence:** A concrete scenario where the proposed wording produces a worse outcome than the current wording — i.e., where a claim advances that should have been blocked. I could not construct one where the reproducibility requirement (a) does not provide adequate protection.

---

## Gate Check

- **G2 Bounded scope:** Targets G5 specifically; does not alter other gates or the evidence hierarchy
- **G3 Operational definitions:** The failure mode is observable — an LLM reading G5's header applies it as a requirement for known mechanism; the historical examples are concrete and would reproduce the gate failure
- **G4 Test rigidity:** With this rewording, a reproducible effect with unknown mechanism passes G5 if mechanism status is declared and a test proposed; without it, the same finding fails G5. The behavioral difference is verifiable.
- **G5 (recursive):** The mechanism of G5's failure is a contradiction in the current text — the gate header implies mechanism must be *known*, the exception clause implies it may be *unknown*. The proposed rewording resolves the contradiction by making declaration (not knowledge) the gate condition.
