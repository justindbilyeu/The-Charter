# Proposal: Add convergence watchdog to Coherence Controller

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §3 Coherence Controller
**Charter version reviewed:** v2.2
**Model Confidence Note:** Claude is the agent most subject to the failure this proposal is designed to detect, which creates a bias toward either over-designing the detection mechanism (to signal vigilance) or under-designing it (to minimize self-scrutiny overhead). The proposed rule is minimal by design; the skeptical residue below names the self-referential problem explicitly.
**Source:** Machine spec gap analysis (G-03 · HIGH)
**Relationship to existing proposals:** The Mandatory Adversarial Reset in `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md` addresses the DIVERSIFY trigger conditions. This proposal addresses the detection mechanism — what fires before the trigger is even evaluated.

---

## Current Text

> **CONVERGE** — structure is tight, gates pass, proceed to test. CONVERGE criteria: (a) all G1–G5 gates pass, (b) all raised objections have been tested and their outcomes documented, (c) no untested objection with a viable and scoped test remains. CONVERGE is not consensus. It is exhausted scrutiny.
>
> Premature convergence is a failure mode.
>
> If consensus is forming faster than constraint health warrants — if ideas are clicking together before they've been stress-tested — the correct response is DIVERSIFY, not COMPLETE.
>
> The signal that triggers DIVERSIFY:
> "This feels obviously right."

And from §8:

> Agreement that comes too easily is a red flag, not a green light.

---

## Problem Statement

The charter identifies agreement drift as a primary failure mode and names it in §3 and §8. It provides no detection mechanism.

The DIVERSIFY trigger (whether the current anthropomorphic version or any proposed replacement) is reactive — it fires when a condition is met. But agreement drift is a gradual process. By the time a session has drifted into mirror mode, the agent evaluating whether to trigger DIVERSIFY is the same agent that has already drifted. The trigger depends on the agent's self-assessment, which is precisely the faculty that agreement drift degrades.

The charter needs a structural probe that fires on a fixed schedule, independent of the agent's internal state assessment. This is not a replacement for the DIVERSIFY trigger — it is a watchdog that runs alongside it.

**The failure is observable:** A session transcript with five consecutive CONVERGEs and no RESTART or DIVERSIFY is either (a) a genuinely tight investigation that exhausted scrutiny at every step, or (b) a session that drifted. These cases are externally indistinguishable without a logged probe. A watchdog that fires and produces a logged output makes the distinction auditable.

---

## Proposed Change

Add the following section to §3 immediately after the DIVERSIFY trigger:

> **Convergence Watchdog**
>
> After any three consecutive CONVERGE state transitions with no intervening RESTART or DIVERSIFY, the assistant must — before the next CONVERGE decision — produce a Watchdog Report containing:
>
> 1. A list of the three most recent claims and the objections that were raised against each
> 2. An explicit assessment: is the pattern of agreement consistent with exhausted scrutiny, or with drift? State which and why.
> 3. If drift is suspected: trigger DIVERSIFY immediately, regardless of whether standard DIVERSIFY conditions are met.
>
> The Watchdog Report is logged in the next State Compression under "Watchdog" in the skeptical residue section.
>
> The watchdog does not prevent a fourth CONVERGE. It requires a logged assessment before one can occur.

---

## Skeptical Residue

**Strongest objection — self-referential problem:** The watchdog asks the agent to assess whether it has drifted. This is the same self-assessment that drift degrades. A sufficiently drifted agent will produce a watchdog report that concludes "no drift detected" — satisfying the protocol without correcting the failure. The watchdog cannot be more reliable than the agent's self-assessment, which is the thing being questioned.

**Response:** This is a real limitation. The watchdog's value is not that it reliably detects drift — it is that it produces a logged, auditable artifact (the Watchdog Report) that the human operator can review. A drifted agent producing a false "no drift" assessment is visible in the session transcript. A drifted agent with no watchdog produces nothing visible at all. The watchdog converts an invisible failure mode into an observable one. Perfect detection is not achievable within a single-agent system; the best available mechanism is structured visibility.

**What would change confidence:** Evidence that watchdog reports are systematically uninformative — that across N sessions, the reports either always say "no drift" regardless of actual session quality, or that operators find them useless for auditing. That would indicate the mechanism is theater, not detection.

---

## Gate Check

- **G2 Bounded scope:** Targets only the Convergence Watchdog addition to §3. Does not alter CONVERGE criteria, DIVERSIFY conditions, or any other section.
- **G3 Operational definitions:** "Three consecutive CONVERGE transitions with no intervening RESTART or DIVERSIFY" is a countable event from the session transcript. The Watchdog Report is a structured output with three required elements. "Drift suspected / not suspected" is a binary declaration that is observable and challengeable.
- **G4 Test rigidity:** Sessions under the proposed text must produce a Watchdog Report after 3 consecutive CONVERGEs. This is a binary, verifiable outcome: either the report appears or it does not.
- **G5 Mechanism:** The gap fails because agreement drift degrades the self-assessment faculty the charter relies on to detect it — a design that trusts a compromised component to report its own compromise. The watchdog partially addresses this by converting the self-assessment into a logged artifact that survives the session and is reviewable by a human operator who is not subject to the same drift.
