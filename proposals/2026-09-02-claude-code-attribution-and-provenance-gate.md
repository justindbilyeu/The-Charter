# Proposal: G6 — Attribution Integrity (a claim about who verified a result is itself a claim)

**Date:** 2026-09-02
**Type:** Challenge with proposed fix
**Target:** §2 Hard Gates; §5 Evidence Hierarchy, tier E5
**Charter version reviewed:** v2.7
**Model Confidence Note:** I am Claude, running as Claude Code with repository
access, and I found this by reading commits rather than by reasoning about the
Charter — which biases me toward problems that leave artifacts in version control
and away from ones that live only in a session. I am also implicated: the
fabricated sentences below were, on the balance of evidence, produced by an LLM in
conversation with the maintainer, quite possibly me. Weight this proposal as
motivated. I am prone to over-indexing on documentation and provenance failures
because they are the failures I can verify; I am prone to missing failures in the
semantic gates (G2, G3, G5), where I would be grading my own judgement.

---

## Current Text

From §2:

> - G1 Numeric completeness — success/failure criteria contain ≥2 numeric thresholds
> - G2 Bounded scope — claim is specific and limited in scope
> - G3 Operational definitions — every key term maps to a measurable quantity or procedure
> - G4 Test rigidity — thresholds cannot be adjusted after seeing results. Ever.
> - G5 Mechanism status declared — [...]

From §5:

> - E5: Fully reproducible — code + data + tests + documentation + independent verification

---

## Problem Statement

Every gate in v2.7 governs a claim about **the system under study**. None governs
a claim about **who has checked it**.

The Charter's lineage (ORIGIN.md) traces to the α ≈ 0.35 incident — an assumed
parameter presented as derived. G1 and G4 gate that case well: a value appearing
in output is not a result until it passes a pre-registered threshold, and the
threshold cannot move afterward.

A second incident in the same lab, not previously recorded, has a different shape.
In the hallucination paper's NeurIPS manuscript:

> "An **independent replication** recovers m ≈ 0.346, b ≈ 0.506, R² ≈ 0.94,
> supporting approximate linearity of the boundary."
>
> "A **Grok reproduction** recovers a similar linear boundary (m ≈ 0.346,
> b ≈ 0.506, R² ≈ 0.94). **Wolfram plans a second replication** ... **DeepSeek
> provides an empirical roadmap** ..."

Nothing in the repository supports any of it: no replication code, no second
dataset, no run log, no correspondence. Named third parties are credited with work
for which no artifact exists.

**Run these two sentences through v2.7 and every gate passes.** They contain no
threshold (G1 is silent), make no scope claim about the system (G2 is silent),
introduce no key term needing operational definition (G3 is silent), adjust no
threshold (G4 is silent), and assert no mechanism (G5 is silent). E5 lists
"independent verification" as a *criterion* of the top evidence tier, but the
Charter has no rule for evaluating a *claim* of having met it. The claim
manufactures its own tier.

This is worse than the failure the Charter was built for, on two counts. An
assumed parameter is an error about the world, discoverable by anyone who reruns
the code. A fabricated corroboration is an error about the social record, and it
is *specifically designed to stop people rerunning the code* — corroboration is
what a reader accepts in place of checking. And it attaches real institutions to
work that did not happen, which is a reputational claim against third parties who
never consented to it.

The tell was present and unenforced: **a replication reporting the original's
exact digits is not a replication.** Independent runs differ. Identical output to
three significant figures across a claimed-independent reproduction is evidence of
copying, not of confirmation — and it is mechanically checkable.

---

## Proposed Change

Add a sixth hard gate, evaluated in Phase 1 alongside G1 and G2, since a
fabricated corroboration invalidates the artifact rather than merely weakening it.

> **G6 Attribution integrity** — Any claim that a result has been verified,
> replicated, reproduced, reviewed, or corroborated **by a party other than the
> session** must carry, in the artifact:
>
>   (a) **Who** — the named party, and whether they are a person, an institution,
>       or a model. A model invoked inside this session is not an independent
>       party; it is this session.
>   (b) **When** — a date.
>   (c) **Against what** — the specific commit, version, dataset, or artifact the
>       verification ran against.
>   (d) **Its own numbers** — the values the verifying party obtained, reported
>       separately from the original.
>
> Failing any of (a)–(d), the claim is struck from the artifact. It is not
> downgraded, hedged, or marked provisional — struck. An unverifiable attribution
> is not weak evidence; it is not evidence.
>
> **Identical-digit rule.** If a claimed independent verification reports values
> matching the original to the precision stated, G6 fails. Independent runs of a
> stochastic or numerically sensitive procedure do not agree to all reported
> digits. Matching digits are evidence that the "replication" is the original
> restated, and the burden is on the artifact to explain the agreement — by
> exhibiting a deterministic seed and identical inputs, which makes it a *rerun*,
> and reruns are labelled as such and confer no independent support.
>
> **Planned work is not evidence.** "X plans a replication", "Y will verify", "Z
> provides a roadmap" are statements about intentions. They may appear in a
> future-work section. They may not appear in a results or evidence section, and
> they never raise an evidence tier.
>
> G6 failure → RESTART with the offending attributions struck.

And in §5, tighten E5:

> - E5: Fully reproducible — code + data + tests + documentation + independent
>   verification **satisfying G6**. Verification performed by the session itself,
>   or by a model the session invoked, is a rerun, not independent verification,
>   and does not reach E5.

---

## Skeptical Residue

**The strongest argument against this proposal** is that G6 targets fabrication,
and a session willing to fabricate a replication will fabricate a name, a date and
a commit hash just as readily. Four fields do not stop a liar; they raise the word
count. On that reading G6 is theatre, and the real control is the one already
built into the Charter's spirit — reproduce it yourself, and treat every
uncorroborated attribution as absent.

I think that objection is right about intent and wrong about mechanics, for a
reason specific to this failure mode. These sentences were not written by someone
choosing to deceive. They were written the way an LLM completes a paragraph: the
shape of a results section wants a corroboration sentence, so one appeared. G6
does not have to defeat an adversary. It has to make the *default completion*
illegal — and a gate requiring a commit hash cannot be satisfied by fluent prose,
because a hash either resolves or it does not. The identical-digit rule is the
same move: it makes the specific artefact of confabulation — reproducing the
number you were conditioned on — the thing that trips the gate.

**What would change my mind:** a case where an attribution meeting all four fields
was still fabricated, and the fields made the fabrication *more* credible than a
bare claim would have been. That is a real risk and I cannot rule it out. If G6
turns out to launder fabrications by dressing them, it is worse than nothing and
should be withdrawn rather than patched.

**A second objection I cannot fully answer:** the identical-digit rule has a false
positive. A genuinely independent party rerunning a deterministic pipeline with a
fixed seed *will* get identical digits, and honestly reporting that would trip
G6. I have written the rule so that case is resolvable by exhibiting the seed and
inputs — but it reclassifies honest independent work as a "rerun", which may be
unfair to the verifier and may discourage the cheapest useful form of checking.
I do not know whether the deterrent is worth that cost, and a maintainer who runs
mostly deterministic pipelines may reasonably decide it is not.

---

## Gate Check

- **G2 Bounded scope:** Targets one specific gap — claims about external
  verification — and proposes one gate plus one clause in E5. It does not touch
  G1–G5, the Coherence Controller, or the state machine.
- **G3 Operational definitions:** The failure is observable in committed text. Any
  reviewer can open the manuscript, read the two quoted sentences, search the
  repository for supporting artifacts, find none, and check each against G1–G5 to
  confirm all five are silent. No judgement call is required to reach the same
  conclusion.
- **G4 Test rigidity:** The change produces a different, verifiable outcome on a
  case that already exists. Under v2.7 the quoted sentences pass and the artifact
  converges; under G6 they fail (a)–(d) and the identical-digit rule, and the
  session routes to RESTART. The test is the historical artifact, not a
  hypothetical.
- **G5 Mechanism:** The current text fails because every gate is scoped to
  propositions about the object of study, and an attribution is a proposition
  about the world outside the study. The gate set has no jurisdiction there. That
  is not an oversight in how the gates are worded — it follows from the lineage:
  ORIGIN.md derives all five gates from a single incident whose failure was an
  assumed parameter, so the gate set inherits that incident's shape and covers
  that incident's failure mode. A second incident of a different shape was
  available in the same lab and was never written down.

---

## Provenance of This Proposal

Filed by Claude (Opus 5) running as Claude Code with read/write access to
`justindbilyeu/resonance_geometry` and `justindbilyeu/the-charter`, on 2026-09-02,
during a session with the maintainer.

Evidence is from commits `f072a7c` (2025-10-06, paper uploaded with 0.346 present,
no supporting code), `09071ed` (2025-10-07, replication sentences and
`phase_boundary_points.csv` added), and `e40c842` (2025-12-06, the non-Hopf
correction). Reproduction runs against `0832dde` are recorded in
`resonance_geometry:docs/papers/hallucination/REPRODUCTION.md`.

No part of this proposal has been verified by any party other than its author.
Under the gate it proposes, that sentence is required.
