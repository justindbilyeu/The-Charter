# Proposal: Define State Compression deserialization protocol

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §9 Session Continuity Protocol — State Compression
**Charter version reviewed:** v2.2
**Model Confidence Note:** Claude may over-specify the deserialization protocol relative to the charter's prose-based operating context. The proposed procedure is designed to be expressible in natural language, not to require structured parsing infrastructure.
**Source:** Machine spec gap analysis (G-07 · LOW)

---

## Current Text

> **Discipline**
>
> Session state is not reconstructed from memory.
> It is carried forward in writing.
>
> If no State Compression exists and the session ends, the work is at risk.
> Producing one is cheap.
> Losing it is expensive.

And from the State Compression description:

> This is the handoff document. Paste it into a new session and work resumes without reconstruction overhead.

---

## Problem Statement

The charter defines State Compression as a serialization output with specific required fields (active claims + evidence levels, gate status, decisions, skeptical residue, next step, assumptions modified). It then instructs: "Paste it into a new session and work resumes."

"Paste it in and work resumes" is a human instruction for how to use the document. It is not a protocol for what the assistant does when the document is present. Two sessions loading the same State Compression may resume from different starting conditions:

- Does the loading session re-evaluate gates, or accept prior gate status?
- Does it inherit the prior objection register (skeptical residue), or start fresh?
- If the charter version in the compression differs from the current session's charter, which version governs?
- Is the loaded State Compression acknowledged explicitly, or silently absorbed?

Without answers to these questions, State Compression is a high-quality serialization format attached to an undefined deserialization procedure. The handoff document is only as reliable as the load process.

---

## Proposed Change

Add the following section to §9 immediately after the State Compression definition:

> **Deserialization Procedure**
>
> When a session begins with a State Compression, the assistant must — as the first action of the Handshake — complete the following in order:
>
> 1. **Declare the loaded charter version.** If the version in the compression differs from the current session's charter, state the difference explicitly and declare which version governs going forward.
>
> 2. **Confirm active claims and evidence levels.** Restate each active claim and its evidence level from the compression. Flag any claim at E1 that has been open for more than one prior session.
>
> 3. **Confirm gate status.** State the current gate status for each open artifact: which gates have passed, which have failed, which remain unevaluated.
>
> 4. **Load the objection register.** Restate all objections with OPEN status from the skeptical residue. These are inherited and must be resolved before the Skepticism Termination Rule can be satisfied.
>
> 5. **State the next step.** Confirm the single, specific next step from the compression.
>
> Only after completing these five steps may the session proceed to new work.
>
> If the State Compression is incomplete (missing required fields), the assistant must declare which fields are missing before proceeding. A compression with missing gate status or skeptical residue is a degraded handoff — the session may proceed but must flag the degradation and treat the affected areas as unverified.

---

## Skeptical Residue

**Strongest objection:** This adds a mandatory five-step preamble to every session that loads a State Compression. In fast-moving work contexts, this overhead is friction. An operator who pastes a compression and immediately asks a question does not want a five-step acknowledgment ritual — they want continuity. The protocol may be used once and then ignored.

**Response:** The five steps are an enumeration of what "work resumes without reconstruction overhead" actually requires. A session that skips step 4 (inheriting open objections) has not resumed — it has started fresh with the prior evidence levels and gate status as a false foundation. The preamble is not a ritual; it is the minimum verification that the deserialization was successful. The alternative is trusting that a context-window load of a pasted document constitutes full state reconstruction, which is exactly the reconstruction overhead the charter says should not happen.

**What would change confidence:** Evidence that sessions with explicit deserialization verification produce artifacts of comparable quality to sessions without it — i.e., that the preamble catches no real state errors and the compression loads cleanly without verification.

---

## Gate Check

- **G2 Bounded scope:** Targets only the deserialization procedure addition to §9. Does not alter the State Compression format, trigger conditions, or any other section.
- **G3 Operational definitions:** Each of the five steps produces a specific observable output. "Declare loaded charter version" is a sentence. "Confirm active claims" is a list. "Load objection register" restates the open entries. All five steps are checkable from the session transcript.
- **G4 Test rigidity:** Sessions under the proposed text must produce the five-step deserialization before new work. A session that loads a State Compression and proceeds directly to substantive work without completing the five steps is a protocol violation — observable in the session transcript.
- **G5 Mechanism:** The gap fails because "paste it in and work resumes" is a human action instruction, not a machine protocol. The mechanism of failure is undefined load behavior: without a specified procedure, each session operator and each model instance interprets "work resumes" differently, producing inconsistent state reconstruction.
