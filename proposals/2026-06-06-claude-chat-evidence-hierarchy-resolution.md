# Proposal: Fix E2 Operationally; Preserve the Ladder

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §5 Evidence Hierarchy
**Charter version reviewed:** v2.6
**Model Confidence Note:** Prone to (a) underweighting structural critiques when an operational fix feels sufficient — may be pattern-matching to "simpler is better" rather than engaging Kimi's architectural concern fully; (b) generating plausible-sounding verification criteria that are harder to apply in practice than they appear on the page; (c) missing cases where the E2 fix creates new ambiguity at the E2/E3 boundary. Weight this proposal accordingly against reviewers with stronger structural intuition.
**Closes:** Q1

---

## Current Text

> - E5: Fully reproducible — code + data + tests + documentation + independent verification
> - E4: Methods-grade artifact — robustness checks + negative controls + preregistered protocol
> - E3: Reproducible experiment or simulation with clear pass/fail outcomes
> - E2: Established domain knowledge — explicitly cited and sourced
> - E1: Speculation — must include a minimal decisive test proposal containing at least one named independent variable, at least one named dependent variable, and at least one numeric threshold constituting a pass or fail outcome. A qualitative test proposal does not satisfy E1.
>
> No claim may be described as E3+ without a structured artifact and test results.
>
> Citation count is not validation.
> Enthusiasm is not evidence.
> Feeling certain is a warning sign.

---

## Problem Statement

**Gemini's critique is more accurate as an operational matter; Kimi's critique is more accurate as an architectural matter. They are not in competition — they operate at different levels. But only Gemini's gap creates an exploitable failure mode in the charter's primary use cases.**

Kimi diagnoses a real structural tension: reproducibility and empirical grounding are not the same quality dimension, and the linear ladder can rank a reproducible but empirically invalid artifact above a non-reproducible but well-grounded one. This is architecturally correct.

However, the charter's G3 (operational definitions), G5 (mechanism status), and the Structuring Contract together impose a filter that substantially reduces the practical severity of this misranking. A simulation built on invalid assumptions typically fails G3 or G5 before its E-level becomes operative. Furthermore, the v2.5 change removing the "applicable gates" exemption means all five gates are now mandatory — the gates are not avoidable by runtime declaration. The Goodhart incentive Kimi identifies is real but substantially contained by the existing gate structure.

A 2D matrix (Kimi's implied alternative) would need at minimum a 4-cell structure to be meaningful. That doubles the taxonomy's cognitive load without proportional benefit in the charter's primary empirical/computational domain. A compact single-axis hierarchy that works well for 90% of cases is preferable to a correct-but-unwieldy matrix.

Gemini's gap, by contrast, is narrow, concrete, and not contained by any existing mechanism. The text says "citation count is not validation" and then defines E2 entirely through citation. An LLM or a human using the charter in good faith can satisfy E2 with a single unverifiable or hallucinated citation. This is not a scope issue. E2 is the evidence level most commonly invoked for foundational assumptions in structured artifacts — it is a load-bearing point, and the sole criterion for it is the one thing the charter explicitly says is not validation.

**The current E2 text fails because it makes citation the sole verification criterion for a level that the charter itself treats as insufficient for validation.**

Note on Kimi's structural concern: this proposal does not resolve it — it defers it. The claim that the ladder's single axis is adequate for the charter's use cases is an empirical claim about how the charter gets used in practice. If data from future sessions shows that reproducible-but-ungrounded artifacts are systematically reaching CONVERGE, the deferral should be revisited with a concrete operational definition of "empirically grounded" as a binary status. That is Q5 on the record.

---

## Proposed Change

Replace the E2 bullet with the following, and add the foundational/orientational definition immediately after the full ladder:

**Revised E2 bullet:**
> - E2: Established domain knowledge — meeting both of the following:
>   (a) Verifiable citation: the source is independently locatable by a
>   reviewer without access to the original researcher's context (title,
>   author, and access path sufficient to retrieve it).
>   (b) Corroboration: when E2 knowledge is used as a foundational
>   assumption in a structured artifact, at least two independent
>   verifiable sources are required. For background orientation only —
>   not cited as a foundational assumption — a single verifiable source
>   satisfies E2.

**Definition to add after the ladder, before "No claim may be described as E3+":**
> A foundational assumption is one whose removal would require revising
> the artifact's central claim, operational definitions, or success
> criteria. An orientational claim provides context but the artifact
> stands without it. This distinction is determined at the time the
> structured artifact is compiled.

---

## Skeptical Residue

**Strongest argument against Option A (for Option B):**

The foundational/orientational distinction introduces a new judgment call at compile time that can be gamed. A researcher who wants to use a single convenient citation for a load-bearing assumption can declare it "orientational" and proceed. The charter currently has no mechanism to challenge that declaration post-hoc. Kimi's binary grounding-status approach, by contrast, makes the axes explicit and forces the trade-off visible.

**What would change this conclusion:** If in practice the foundational/orientational distinction generates disputes or rationale-shopping — operators arguing about classification rather than evaluating claims — that would be evidence the distinction is too expensive to maintain and Kimi's structural approach deserves reconsideration despite its added complexity.

**Why Option A holds:** The 2D approaches (Gemini's matrix, Kimi's override) don't close the E2 citation loophole automatically — they'd need to patch both the structure and the citation standard. Option A patches the known operational hole within the existing structure and incurs lower cognitive overhead. Correct sequencing: fix the known operational gap first, observe whether Kimi's structural concern manifests as a practical failure mode, escalate to Option B only if it does.

---

## Gate Check

- **G2 Bounded scope:** Targets §5 Evidence Hierarchy exclusively — specifically the E2 definition and the foundational/orientational distinction. No other section modified.
- **G3 Operational definitions:** The problem is observable: any LLM given the current §5 text and asked "what satisfies E2?" produces "citation" as the complete and sufficient answer — because that is what the text says. The fix produces a verifiably different answer: independent locatability plus corroboration for foundational uses.
- **G4 Test rigidity:** The proposed change produces a verifiably different behavioral outcome: an E2 claim backed by a single non-locatable citation now fails rather than passes. Test case: present a hallucinated citation as E2 support for a foundational assumption — it fails the revised standard, passes the current one.
- **G5 Mechanism:** The current text fails because it sets citation as the operational criterion for E2 while §8 Integrity Rules explicitly states "citation count is not validation." This is a direct conflict between the level definition and the level's interpretive framing. The mechanism of failure: a practitioner following the text in good faith satisfies E2 with a single citation, then encounters "citation count is not validation" with no guidance on what, if not citation count, constitutes E2. The fix aligns the criterion with the interpretive framing by requiring independent locatability (not count) and corroboration for load-bearing uses.
