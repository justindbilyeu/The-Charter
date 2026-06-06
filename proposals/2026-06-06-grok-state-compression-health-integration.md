# Proposal: Require Constraint Health state and anchor status in State Compression

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §9 Session Continuity Protocol — State Compression required fields
**Charter version reviewed:** v2.2
**Model Confidence Note:** Grok's strength here is identifying cross-session integration gaps. The risk is over-specifying the handoff format in ways that interact poorly with whichever G-08 approach (numeric metric vs. observable conditions) the maintainer accepts. This proposal is written to be compatible with either; the specific encoding of "constraint health state" defers to the G-08 decision.
**Source:** Grok structural analysis — integration of G-02, G-03, G-08 into State Compression
**Relationship to existing proposals:** `2026-06-06-claude-g07-deserialization-protocol.md` defines the deserialization procedure for a loaded State Compression. `2026-06-06-claude-g03-watchdog-degradation-detection.md` requires Watchdog Reports to be logged in State Compression. This proposal adds two required fields to the State Compression format itself.

---

## Current Text

From §9, State Compression required fields:

> - Active claims with evidence levels
> - Gate status for each open artifact
> - Decisions made
> - Skeptical residue — open objections and their status
> - Next step — single, specific, bounded
> - Assumptions modified

And from the Convergence Watchdog proposal (G-03, pending):

> The Watchdog Report is logged in the next State Compression under "Watchdog" in the skeptical residue section.

---

## Problem Statement

The current State Compression format captures what was claimed, what gates passed, what objections are open, and what comes next. It does not capture the health state of the Coherence Controller at the time of compression.

This creates a deserialization problem: a session loading a State Compression can reconstruct the artifact's content and the objection register, but cannot reconstruct whether the prior session was in a healthy or drifted control state. Two compressions with identical artifact content, gate status, and objection register entries may have been produced by sessions with radically different control histories — one that actively triggered DIVERSIFY when warranted, one that coasted through consecutive CONVERGEs without adversarial challenge.

The deserialization procedure (G-07 proposal) requires the loading session to confirm gate status and load the objection register. But it has no field to load. There is no field for "how healthy was the CC when this was compressed" — no trajectory signal, no record of whether the adversarial anchor fired, no constraint health snapshot.

Without this, State Compression is epistemically incomplete: it carries the content of the session but not the quality-of-scrutiny signal that characterizes the session that produced it.

---

## Proposed Change

Add two required fields to the State Compression format in §9:

> **Required fields (additions):**
>
> - **Constraint Health** — the constraint health state at the time of compression. If a numeric metric is in use (Option A, G-08): report the last computed H score and the component values (H_hyp, H_obj, H_traj). If observable conditions are in use (Option B, G-08): report the three condition states (gates evaluated/passed count; OPEN objection count; consecutive CONVERGE count without DIVERSIFY/RESTART). If no G-08 resolution has been adopted: report whether the last state decision was CONVERGE, DIVERSIFY, or RESTART and whether it followed a watchdog-triggered or standard trigger path.
>
> - **Adversarial Anchor Status** — whether the scheduled adversarial anchor (Mandatory Adversarial Reset or equivalent) fired during this session, and if so, at which gate evaluation cycle. If it did not fire, state whether the threshold was approached (within one cycle of triggering) or not.

Update the deserialization procedure (§9, per the G-07 proposal) to add a sixth step:

> 6. **Load constraint health and anchor status.** Report the last Constraint Health state from the compression and whether the adversarial anchor fired. If Constraint Health was below the intervention threshold at compression time, treat the loaded session state as requiring immediate Constraint Health re-evaluation before proceeding to new work.

---

## Skeptical Residue

**Strongest objection — this proposal is contingent on two pending decisions:** The Constraint Health field requires a resolution to the G-08 competing proposals (numeric metric vs. observable conditions). The Adversarial Anchor Status field requires a resolution to which anchor mechanism is adopted (G-02/G-03 pending proposals). Filing a State Compression requirement that depends on two undecided upstream proposals means this proposal cannot be fully specified until those decisions are made. It may need to be revised once the G-08 and G-03 questions are settled.

**Response:** The integration requirement is valid regardless of which upstream choices are made. The field names and the deserialization step are independent of their content. "Report the Constraint Health state" is meaningful whether that state is a scalar, a tuple of observables, or a qualitative description. Filing the integration requirement now establishes that State Compression must include health state data; the specific encoding follows from whichever G-08 approach is accepted. The proposal explicitly defers the encoding to that decision.

**What would change confidence:** Evidence that sessions loading State Compressions make equivalent-quality decisions regardless of whether the prior session's Constraint Health state is known — i.e., that the health field carries no predictive signal for the loading session. That would indicate the field adds format overhead without operational value.

---

## Gate Check

- **G2 Bounded scope:** Targets only the required fields of State Compression in §9 and the deserialization procedure. Does not alter gate specifications, Coherence Controller logic, or any other section.
- **G3 Operational definitions:** "Last Constraint Health state" is defined by whichever G-08 approach is adopted — both produce observable outputs. "Whether the adversarial anchor fired" is a binary, observable from the session history. "Approached within one cycle" is countable from the gate evaluation log.
- **G4 Test rigidity:** A State Compression that does not include a Constraint Health field and an Adversarial Anchor Status field is an incomplete compression — observable by inspection. A deserialization that skips step 6 is a protocol violation auditable from the session transcript.
- **G5 Mechanism:** The gap fails because State Compression serializes content (claims, gates, objections) but not process quality (was the CC operating in a healthy control state?). A loading session inherits the artifact but not the scrutiny signal. The mechanism of failure: a session that produced a compression while drifting passes that drift forward invisibly — the loading session sees clean artifact content and has no signal that the prior session's control state was degraded.
