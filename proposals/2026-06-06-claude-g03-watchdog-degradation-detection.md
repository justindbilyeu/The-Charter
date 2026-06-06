# Proposal: Add convergence watchdog with mandatory intervention to Coherence Controller

**Date:** 2026-06-06
**Type:** Refinement
**Target:** §3 Coherence Controller
**Charter version reviewed:** v2.2
**Model Confidence Note:** Claude is the agent most subject to the failure this proposal is designed to detect, which creates a bias toward either over-designing the intervention (to signal vigilance) or under-designing it (to minimize self-scrutiny overhead). The proposed rule is minimal by design; the skeptical residue below names the self-referential problem and the false-positive cost explicitly.
**Source:** Machine spec gap analysis (G-03 · HIGH)
**Relationship to existing proposals:** The Mandatory Adversarial Reset in `2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md` addresses the DIVERSIFY trigger conditions. This proposal addresses the detection and intervention mechanism — what fires independently of the trigger, and what happens when drift is assessed as likely.

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
> 1. A list of the three most recent claims and the objections that were raised against each.
> 2. An explicit assessment: is the pattern of agreement consistent with exhausted scrutiny, or with drift? State which and why.
>
> The Watchdog Report is logged in the next State Compression under "Watchdog" in the skeptical residue section.
>
> **Intervention rule:** If the Watchdog Report assessment concludes "drift suspected," the session must enter DIVERSIFY immediately, regardless of whether the standard DIVERSIFY trigger conditions are met. The mandatory DIVERSIFY is not contingent on any additional evaluation — the Watchdog Report conclusion is itself sufficient grounds.
>
> The watchdog does not prevent a fourth CONVERGE. It requires a logged assessment before one can occur, and a forced state change if that assessment concludes drift is present.

---

## Skeptical Residue

**Strongest objection — false positives impose real cost:** The intervention rule mandates DIVERSIFY whenever the agent concludes "drift suspected." A false positive — a session that was making genuine progress but produces a cautious Watchdog assessment — is forced into DIVERSIFY unnecessarily. This disrupts a valid research thread and imposes overhead. The agent, knowing that "drift suspected" triggers a mandatory state change, has an incentive to always conclude "no drift" to avoid the disruption — which returns the mechanism to detection-only in practice.

**Response:** The false positive cost is bounded and acceptable. DIVERSIFY is not abort — it adds scrutiny without discarding the work. A session that entered DIVERSIFY unnecessarily can CONVERGE again after the scrutiny pass; the cost is one additional evaluation cycle. Critically, the incentive problem ("conclude no drift to avoid overhead") is addressed by the audit requirement: the Watchdog Report must be logged in State Compression and is reviewable by the human operator. A pattern of "no drift" conclusions across sessions with no supporting objection-level justification is a detectable signal of systematic false negatives — more visible than no report at all.

**Residual concern — self-referential problem:** The assessment in item 2 still depends on the agent's self-evaluation. A drifted agent can produce a report that concludes "no drift." The intervention rule does not eliminate this — it only enforces the consequence when the agent does conclude drift. This is a real limitation that cannot be resolved within a single-agent architecture. The best available mechanism is: mandatory structured report (makes failure visible), mandatory DIVERSIFY when drift is acknowledged (makes the intervention non-optional when acknowledged), and human audit of the log (catches systematic false negatives).

**What would change confidence:** Evidence that (a) sessions with mandatory Watchdog intervention produce worse outcomes than sessions where drift was allowed to continue, or (b) that Watchdog Report conclusions bear no correlation with observable session quality indicators across a sample of transcripts. That would indicate the mechanism produces overhead without calibration signal.

---

## Gate Check

- **G2 Bounded scope:** Targets only the Convergence Watchdog addition to §3. Does not alter CONVERGE criteria, DIVERSIFY trigger conditions, or any other section. The intervention rule adds a new triggering path for DIVERSIFY (Watchdog conclusion) alongside existing trigger conditions; it does not replace them.
- **G3 Operational definitions:** "Three consecutive CONVERGE transitions with no intervening RESTART or DIVERSIFY" is a countable event from the session transcript. The Watchdog Report is a structured output with two required elements (claims+objections list; drift assessment with stated reasoning). "Drift suspected" is a binary, declared conclusion auditable from the report text. The mandatory DIVERSIFY is a state transition observable in the session.
- **G4 Test rigidity:** Sessions under the proposed text must produce two verifiable outcomes: (1) a Watchdog Report after 3 consecutive CONVERGEs — binary, present or absent; and (2) if the report concludes "drift suspected," the next state must be DIVERSIFY — observable in the session transcript. A session that produces a "drift suspected" Watchdog Report and then proceeds to CONVERGE without a DIVERSIFY is a protocol violation detectable from the transcript.
- **G5 Mechanism:** The gap fails on two levels. First, agreement drift degrades the self-assessment faculty the charter relies on to detect it — a design that trusts a compromised component to report its own compromise. The watchdog addresses this by making the self-assessment a logged, auditable artifact. Second, even a reliable self-assessment produces no correction if it has no enforcement consequence — detection without intervention allows drift to continue regardless of what is logged. The intervention rule closes this second failure: "drift suspected" becomes a binding trigger, not a logged observation that can be noted and ignored.
