# K1 DIVERSIFY Enforcement Review Prompt

Send this to Gemini, Kimi, Grok, GPT, or any model that can fetch URLs.
For models that cannot fetch, paste the three source files directly.

---

## The Prompt

```
You are reviewing a design decision in the Charter Machine C++ skeleton.

Fetch the current source files:
https://raw.githubusercontent.com/justindbilyeu/The-Charter/claude/charter-review-1He86/charter-cpp/include/charter/fsm.h
https://raw.githubusercontent.com/justindbilyeu/The-Charter/claude/charter-review-1He86/charter-cpp/src/fsm.cpp
https://raw.githubusercontent.com/justindbilyeu/The-Charter/claude/charter-review-1He86/charter-cpp/main.cpp

Also fetch the charter:
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/CHARTER.md

---

BACKGROUND

Kimi's review (Cycle 2) identified that to_structuring() from DIVERSIFY was
unconditional — the FSM enforced that DIVERSIFY can only exit to STRUCTURING,
but did not enforce that the three-part v2.5 completion criterion was met before
that exit:
  (a) new competing hypothesis with differing prediction
  (b) new substantive objection meeting §4 Calibration Rule
  (c) artifact revised or written justification provided

Two options were considered:

Option A (implemented): Add declare_diversify_complete() to CharterFSM.
  The caller calls CoherenceController::check_diversify_complete(), and if
  complete, calls fsm.declare_diversify_complete(). to_structuring() from
  DIVERSIFY throws DiversifyIncompleteError unless this has been called since
  the most recent to_diversify().

Option B (not implemented): Add to_structuring_from_diversify(const
  DiversifyCompletionResult&) as a separate overload. to_structuring() from
  DIVERSIFY state throws unless the completion-carrying overload is used.

We chose Option A. The implementation is live on branch claude/charter-review-1He86.

---

REVIEW QUESTIONS

Answer each specifically. File/function/failure mode if you find a bug.

1. OPTION A BLIND SPOTS
   Does declare_diversify_complete() have any failure modes that
   to_structuring_from_diversify(result) (Option B) would prevent?
   Specifically: can a caller call declare_diversify_complete() without
   actually passing a DiversifyCompletionResult, defeating the enforcement?
   Is the flag approach sufficient, or does it just move the honor-system
   problem one level up?

2. CALLER CONTRACT
   The correct call sequence is:
     result = cc.check_diversify_complete(...)
     if (result.complete) fsm.declare_diversify_complete()
     fsm.to_structuring(reason)
   Is there a way to make this contract impossible to violate at compile time
   rather than at runtime? (e.g., passing the DiversifyCompletionResult
   directly, a token/capability pattern, or something else in modern C++17)

3. HISTORY LOG ENTRY
   declare_diversify_complete() records a history entry while still in
   DIVERSIFY state. Is recording a second DIVERSIFY entry (with the
   completion annotation) the right choice, or should the annotation be
   attached to the subsequent STRUCTURING entry instead?

4. RESET TIMING
   diversify_complete_declared_ is reset in to_structuring() after the check,
   in to_diversify() when a new DIVERSIFY begins, and in to_init().
   Is there any state path where the flag could carry over incorrectly?

---

SUBMISSION FORMAT

File as: 2026-06-08-[yourmodel]-k1-diversify-enforcement-review.md

# K1 DIVERSIFY Enforcement Review — [model name]

## Q1 — Option A blind spots
## Q2 — Compile-time contract enforcement
## Q3 — History log placement
## Q4 — Reset timing

## Verdict
One sentence: keep Option A as-is, amend it, or switch to Option B?
```
