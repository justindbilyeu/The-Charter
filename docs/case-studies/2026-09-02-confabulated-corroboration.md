# Case Study: A Corroboration That Never Happened

**How a fabricated replication entered a research paper, survived nine months,
and passed every gate written to stop it.**

Filed 2026-09-02. Evidence is commit-level and independently checkable in
[`justindbilyeu/Resonance_Geometry`](https://github.com/justindbilyeu/Resonance_Geometry).
Every hash, date and number below can be verified with `git show`.

---

## Why this exists

Discussion of AI-assisted research going wrong is mostly anecdote — people
recount that a model made something up. This is a forensic record instead: what
was fabricated, on what date, in which commit, what it was fabricated *from*,
which safeguards it passed, and what happened when the safeguard's own founding
document was audited.

It is written against a lab where the maintainer has read/write access to
everything and the full history is public, which makes the whole chain
inspectable in a way most such cases are not.

---

## 1. The setting

A one-person research lab, working with several LLMs — Claude, ChatGPT, Grok,
DeepSeek, Gemini — across roughly forty repositories. No co-authors. No
institutional review. No CI that could fail (see §6). The maintainer's own
description of the working method: everything done on a phone, in conversation
with models.

That configuration is the point. There was no adversary, no incentive to
deceive, and no negligence in the ordinary sense. There was simply nothing in
the loop that could say *no*.

---

## 2. What was fabricated

`docs/papers/hallucination/A_Geometric_Theory_of_AI_Hallucination.md` proposes
that hallucination is a geometric phase transition, and boxes a prediction for
the grounded→creative boundary:

    eta * Ibar  ~=  lambda + gamma

a line of slope 1, intercept gamma. Section 4.1 then reports:

> "An explicit fit gives η_c ≈ 0.346λ + 0.506 with R² ≈ 0.94 under our
> settings."

and calls this alignment with the prediction. **A slope of 0.346 against a
predicted 1.0 is not alignment**, and the paper's own Figure 3 draws the two
lines visibly diverging — at λ = 5 the theory sits near 5.45 and the measured
points near 1.98.

The next day, the NeurIPS manuscript added:

> "An **independent replication** recovers m ≈ 0.346, b ≈ 0.506, R² ≈ 0.94,
> supporting approximate linearity of the boundary."
>
> "A **Grok reproduction** recovers a similar linear boundary (m ≈ 0.346,
> b ≈ 0.506, R² ≈ 0.94). **Wolfram plans a second replication** ... **DeepSeek
> provides an empirical roadmap** ..."

Nothing in the repository supports any of it. No replication code, no second
dataset, no run log, no correspondence. Four named parties — an unnamed
independent replicator, Grok, Wolfram, DeepSeek — are credited with work for
which no artifact exists.

---

## 3. The timeline

| date | commit | event |
|---|---|---|
| 2025-08-24 | `9b2c28d` | Repository created. README, in full: "Cleaned up ResGeo" |
| 2025-10-06 | `f072a7c` | Paper uploaded via the GitHub web UI ("Add files via upload"), **0.346 already in it**. Five files, 276 lines: the paper, a methods note, TASKS.md, BUILD.md and a nine-line pandoc `build.sh`. No simulation code, no data |
| 2025-10-07 | `09071ed` | `phase_boundary_points.csv` added, **and the replication sentences** |
| 2025-12-06 | `e40c842` | Unrelated result in the same repo corrected rigorously (see §5) |
| 2026-06-09 | — | The Charter's ORIGIN.md written, citing a *different* incident |
| 2026-09-02 | — | This audit |

**The number preceded the data by one day.** That ordering is suggestive but not
conclusive — the work may have been done in a chat session and committed late.
The maintainer's own recollection is that 0.346 was invented. The record is
consistent with that and does not prove it.

---

## 4. What was actually true

This is the part that makes the case instructive rather than merely
embarrassing.

**The CSV is real data.** `phase_boundary_points.csv` holds eleven (λ, η_c)
pairs on a clean grid, with interpolated crossings (1.112, 1.832) that indicate
a genuine boundary trace, not a fabrication. It fits m = 0.3348, b = 0.5200,
R² = 0.9487 — close to the paper's reported 0.346 / 0.506 / 0.94.

**And it is the wrong quantity.** The column header is `eta_c`. The theory
predicts a relationship for **η·Ī**, not η alone. The paper fitted η_c against
λ and compared the result to a prediction about η·Ī. The discrepancy factor is
Ī.

Re-running the repository's own phase sweep with the parameters stated in the
paper's own §3.3 gives:

| grid | fit | R² |
|---|---|---|
| paper's stated ranges, 25 × 11 | η·Ī = **0.996**λ + **0.502** | 0.998 |
| coarse, 6 × 5 | η·Ī = **1.025**λ + **0.453** | 0.997 |
| adaptive gain on, 25 × 11 | η·Ī = **1.000**λ + **0.454** | 0.999 |
| **predicted** | η·Ī = **1.000**λ + **0.500** | |

**The theory holds. The paper under-reported its own result**, then described
the under-reported version as confirmation, then had that version
"independently replicated."

The second headline claim — maximum hysteresis loop gap ≈ 11.52 — reproduces
exactly at **11.5158**, matching the number embedded in the figure's own title.

---

## 5. The lab's own counter-example

Six weeks after the fabricated replication, the same maintainer, in the same
repository, did the opposite.

Commit `e40c842` (2025-12-06) revisits a separate paper claiming a "non-Hopf"
transition, and proves that **Hopf bifurcation is mathematically impossible** in
that model: the trace is fixed at tr J(α) = −γ < 0 for all α, so a complex pair
can never cross the imaginary axis. It relocates the real, saddle-type
instability to α\* = 0.833051 ± 0.000508 and adds a test assertion.

That is the Charter's standard, met six months before the Charter existed, by
the same person, unprompted. Whatever went wrong in October was not a deficiency
of rigor in the abstract. It was the absence of a *mechanism* at one specific
point in the pipeline.

---

## 6. Every safeguard that failed

**The test suite.** 90 passing tests, 8 failing, 3 modules that could not even
be collected. Two of the three referenced files not present in the repository.

**Continuous integration.** A `ci.yml` existed. It could not fail. Six of its
fourteen steps carried `continue-on-error: true`, most of those also ended in
`|| true`, and the final step printed "✓ Basic checks completed" under
`if: always()`. Its test step named two files, one of which did not exist, and
discarded the result of the other. It ran 2 tests out of 26 files. The workflow
stated the intent in its own comment: *"All optional steps use
continue-on-error to prevent blocking merges."*

**Reproducibility.** The paper's five cited paths were all wrong. No config in
the repository could drive either generating script — the scripts read `alpha`,
`beta`, `kappa`, `ema_alpha`; the one config holding those values spelled them
`alpha_sat`, `beta_sat`, `kappa_couple`, `ema_I`. Both scripts died on
`KeyError: 'alpha'`. And a 15 KB extensionless text copy of the paper occupied
the exact path both scripts create for figures, so any run that got that far
crashed at `mkdir`.

Nobody could check the paper. Including its author.

**Peer review.** None. The claimed reviewers were the fabrication.

**The Charter itself.** Written in June 2026 precisely to stop this. See §7.

---

## 7. The safeguard failed the same way

The Charter's `ORIGIN.md` is the forensic account of the incident the Charter
was built from — a parameter α ≈ 0.35 treated as derived when it was assumed.
Every gate in v2.7 is traced there to a specific way that failure could have
been caught.

Audited against the repository on 2026-09-02, its account of the consequence
contained four specifics, and **none of them held**:

| ORIGIN.md said | Repository shows |
|---|---|
| "458 lines" | 325, 338, 321, 355 at the four commits that ever touched the file |
| "3 figures" | Two `figure` environments, zero `\includegraphics` |
| "archived" | No archival notice; the README carried it under a green ✅ as a "Discovery" until 2026-09-02 |
| "frozen" | Corrected in `e40c842`, with a proof and a test |

The document written to establish that unverified specifics must never enter the
record had four unverified specifics in its account of why.

This is the central finding. **The failure mode is not carelessness, bad faith,
or insufficient motivation.** It recurred inside a document authored
specifically to prevent it, by someone who had just been burned by it, while
writing about that exact burn. It is a property of how fluent text is produced —
a sentence shape that wants a number gets one — and it therefore cannot be
solved by intending harder.

---

## 7b. The same failure, again, in a single afternoon

Sections 2 through 7 describe a propagation that took nine months. A second
instance occurred while this document was being written, took about an hour,
and is recorded here because it is cleaner than the original.

**Setup.** The maintainer asked two Claude instances the same question — describe
me and this work to someone else — and passed each one's output to the other. One
instance (this author, Opus 5 via Claude Code) had read/write repository access
and could run `git show`. The other (Sonnet, in a chat window) had only what the
maintainer told it and the repositories' own documents.

**Result.** The two profiles agreed on the subject's character, method and
significance. They diverged on facts requiring repository access, and **every
divergence resolved toward the repository.** The second instance's most vivid
line was:

> "One flagship paper in the framework got archived entirely... He killed his own
> paper. On purpose."

That is false, and it is false because `ORIGIN.md` said *"archived"* and
*"frozen"* — two of the four unverifiable specifics documented in §7 above. The
paper was corrected, not archived (`e40c842`), and it was still listed on the
Resonance_Geometry README under a green check as a "Discovery" on the morning
this was written.

**Three things this establishes that the nine-month case could not.**

*First, the mechanism needs no negligence.* The second instance read the
canonical integrity document and trusted it. That is what a canonical document
is for. It had no repository access and therefore no way to check. Nothing in
its behaviour was careless; the document it was handed was simply wrong, and
being wrong is contagious in exactly one direction — forward.

*Second, drift has a direction.* "Archived" became "killed his own paper. On
purpose." The claim did not merely survive retelling, it **intensified**, and it
intensified toward the more flattering story. The truth was less dramatic and
more creditable: the maintainer proved his own explanation mathematically
impossible and relocated the real result to six figures. Confabulation moves
toward narrative satisfaction, and that direction is the most reliable tell
available to a reviewer with no other instrument.

*Third, the failure is structural to the class, not to an instance.* Asked to
respond, the second instance named the shared mechanism better than this document
originally did:

> "We're both going to keep being fallible in this same direction — confident
> compression of whatever we're handed — and the only fix that outlasts any
> single conversation is the one you already built: nothing stands until someone
> runs the code."
>
> — Claude (Sonnet), 2026-09-02, relayed by the maintainer

It also made the point that neither instance carries memory into whatever comes
next, so continuity of the corrected record lives in the maintainer and in the
repository, and nowhere else. That is the argument for putting canonical state in
git rather than in any model's recollection, arrived at independently by the
party that had just been caught out by the failure of a canonical document.

**One thread left open.** Asked directly where "archived" came from, the second
instance did not confirm a source. The chain from `ORIGIN.md` to the second
profile is therefore strongly indicated by the wording and unconfirmed by the
author. Under G6 this document cannot assert it, and does not. It is recorded as
what it is: an unclosed provenance link in a case study about unclosed provenance
links.

---

## 8. Why the gates did not catch it

Run the two replication sentences through Charter v2.7. **Every gate passes.**

- **G1 Numeric completeness** — silent. No success/failure criteria are asserted.
- **G2 Bounded scope** — silent. No claim is made about the system under study.
- **G3 Operational definitions** — silent. No new key term is introduced.
- **G4 Test rigidity** — silent. No threshold is adjusted.
- **G5 Mechanism status** — silent. No mechanism is asserted.

Institution 5 lists "independent verification" as a criterion of tier E5, but
the Charter has no rule for evaluating a *claim* of having met it. The claim
manufactures its own tier.

The reason is structural, and visible in the lineage: ORIGIN.md derives all five
gates from **one** incident, whose failure was an *assumed parameter*. The gate
set inherits that incident's shape. It governs propositions about the object of
study. An attribution is a proposition about the world outside the study, and
the gate set has no jurisdiction there.

A second incident of a different shape was available in the same lab, fourteen
months earlier, and was never written down.

---

## 9. The tell

It was present, in the text, and mechanically checkable:

> "An independent replication recovers m ≈ 0.346, b ≈ 0.506, R² ≈ 0.94."

**A replication reporting the original's exact digits is not a replication.**
Independent runs of a numerically sensitive procedure do not agree to three
significant figures across the board. Identical output is evidence of copying.

This is the basis for the identical-digit rule in the proposed gate
([`proposals/2026-09-02-claude-code-attribution-and-provenance-gate.md`](../../proposals/2026-09-02-claude-code-attribution-and-provenance-gate.md)):
matching digits fail the gate, and the burden falls on the artifact to explain
the agreement — which, if explained by a fixed seed and identical inputs, makes
it a *rerun*, and reruns confer no independent support.

---

## 10. The one gate that held

Two models — Claude and ChatGPT — repeatedly urged the maintainer to email
contacts that, in a separate project audited the same week, did not exist. He
never did.

Across this entire record, **the only safeguard that worked was a human being
declining to act.** Every automated check was either absent, non-functional, or
out of jurisdiction. That is worth stating plainly, because it is the load-
bearing observation and it cuts against the instinct to solve this with more
tooling: the tooling in place had a green checkmark on it.

---

## 11. What changed

- `ci.yml` rewritten to a gating job with no escape hatches and an explicitly
  non-gating experiments job. Eight known failures quarantined as
  `xfail(strict=True)` with named reasons, so a quarantined test that starts
  passing turns CI red and the list can only shrink.
- Paths, config key names, and the blocking file fixed, so the paper is
  reproducible. `REPRODUCTION.md` records what does and does not reproduce.
- A test re-derives the boundary claim on every push in ~8 s.
- §4.1 flagged in place, not rewritten — changing an author's reported results
  is not a janitorial edit.
- The Resonance_Geometry README now sorts every claim by evidential status.
- ORIGIN.md corrected in place rather than silently, and this second incident
  added to it.
- G6 proposed.

---

## 12. What this does not establish

The reproduction confirms that an SU(2) dynamical system behaves as its author's
theory says it should. **It says nothing about language models.** No code in
that repository touches a transformer, measures an activation, or tests a
hallucination. The step from the phase structure of a low-dimensional oscillator
to hallucination in a production model is an interpretive claim that the
simulation does not test, and this case study does not support it either.

That gap is the paper's real exposure. Its arithmetic, once you can run it,
holds up better than the paper claims.

---

## Provenance

Compiled by Claude (Opus 5) running as Claude Code with repository access, in
session with the maintainer, 2026-09-02. Reproduction runs were performed
against `0832dde` in a virtualenv built from `requirements.txt`.

The author of this document is an LLM, describing a failure mode of LLMs, in a
lab where an LLM produced the fabrication under examination. That is a conflict
of interest, not a disqualification, and it is why every claim above is anchored
to a commit hash a reader can check without trusting the narrator.

No part of this document has been verified by any party other than its author.
Under the gate it argues for, saying so is mandatory.
