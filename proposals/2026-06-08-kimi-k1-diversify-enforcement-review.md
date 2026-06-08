# K1 DIVERSIFY Enforcement Review — Kimi K2.6

**Reviewed:** 2026-06-08
**Scope:** Option A `declare_diversify_complete()` design decision
**Note:** Raw GitHub files showed old version; reviewed based on design description per prompt.

---

## Q1 — Option A Blind Spots

**Critical blind spot confirmed. Option B closes it.**

`declare_diversify_complete()` takes no arguments. A caller can call it without
ever producing a `DiversifyCompletionResult`:

```cpp
fsm.to_diversify("G3 failure");
fsm.declare_diversify_complete();  // FSM accepts blindly
fsm.to_structuring("proceeding");  // enforcement bypassed
```

With Option B's `to_structuring_from_diversify(const DiversifyCompletionResult&)`,
the type system forces the caller to produce a result. The caller cannot "forget" to
check because the function signature demands it.

Additional: `declare_diversify_complete()` is idempotent — callable multiple times in
DIVERSIFY with no effect beyond flag noise. If it were a no-op from non-DIVERSIFY states
(rather than throwing), a caller could accidentally pre-set the flag.

Conclusion: The flag replaces one honor-system boundary with another one level higher.

---

## Q2 — Compile-Time Contract Enforcement

**Recommended: capability token with private constructor (friend class pattern).**

```cpp
class DiversifyExitToken {
    friend class CoherenceController;  // only CC can create tokens
public:
    bool is_valid() const { return valid_; }
    const std::vector<std::string>& unmet_criteria() const { return unmet_; }
private:
    explicit DiversifyExitToken(bool valid, std::vector<std::string> unmet = {})
        : valid_(valid), unmet_(std::move(unmet)) {}
    bool valid_;
    std::vector<std::string> unmet_;
};

// CoherenceController produces the token
DiversifyExitToken CoherenceController::check_diversify_complete(...) const {
    return DiversifyExitToken(unmet.empty(), std::move(unmet));
}

// CharterFSM consumes the token
void CharterFSM::to_structuring(const std::string& reason, DiversifyExitToken token) {
    if (state_ == State::DIVERSIFY && !token.is_valid())
        throw DiversifyIncompleteError("unmet: " + join(token.unmet_criteria(), "; "));
    record(State::STRUCTURING, reason);
    state_ = State::STRUCTURING;
}

// Non-DIVERSIFY overload throws if called from DIVERSIFY state
void CharterFSM::to_structuring(const std::string& reason) {
    if (state_ == State::DIVERSIFY)
        throw DiversifyIncompleteError(
            "DIVERSIFY → STRUCTURING requires a DiversifyExitToken from check_diversify_complete()");
    record(State::STRUCTURING, reason);
    state_ = State::STRUCTURING;
}
```

Why this works: token has private constructor — only `CoherenceController` can create one.
Caller cannot fabricate it. Caller cannot call token-free overload from DIVERSIFY state.

**Minimum viable alternative (less strong):** Make `declare_diversify_complete()` accept
`const DiversifyCompletionResult&` so the FSM validates `result.complete` internally.
Still defeatable with a fabricated struct, but forces the caller to hold a result object.

---

## Q3 — History Log Placement

**Second DIVERSIFY entry is wrong.** Completion is a precondition for the transition,
not an event within the DIVERSIFY state. History logs should reflect state entries.

```
DIVERSIFY — G3 failure
DIVERSIFY — completion declared   ← ambiguous: still in DIVERSIFY?
STRUCTURING — proceed
```

Correct: attach completion evidence to the STRUCTURING entry:
```
DIVERSIFY — G3 failure
STRUCTURING — DIVERSIFY complete [criteria: (a)(b)(c) satisfied] — artifact revised
```

The charter says "On completion, return to STRUCTURING." The completion is an attribute
of the return, not an event before it. With the token pattern, unmet_criteria() can be
logged directly on the STRUCTURING entry.

**Status: already fixed** in Q3 fix commit (bd1b3c0) — record() removed from
declare_diversify_complete(). Completion shows on STRUCTURING entry via reason string.

---

## Q4 — Reset Timing

**Three findings:**

**Finding 1 — to_restart() missing reset:** Confirmed gap (also caught by Claude Chat).
**Status: already fixed** in Q3+Q4 commit (bd1b3c0).

**Finding 2 — Reset-before-commit hazard:** In to_structuring(), the sequence is:
```cpp
diversify_complete_declared_ = false;  // reset flag
record(State::STRUCTURING, reason);    // could throw (bad_alloc)
state_ = State::STRUCTURING;           // state change
```
If `record()` throws, the FSM remains in DIVERSIFY state with the flag cleared. A retry
would throw DiversifyIncompleteError even though the criteria were met. Risk is low
(only OOM could cause this) but the reset should ideally happen after the commit, or use
a RAII guard. Eliminated entirely by the token pattern (stateless — no flag to manage).

**Finding 3 — General fragility:** Any future transition added out of DIVERSIFY (e.g.,
emergency DIVERSIFY → RESTART) must remember to reset the flag. The token pattern is
immune because it carries no persistent flag state.

---

## Verdict

**Amend Option A: switch to capability token pattern (Q2).** At minimum, make
`declare_diversify_complete()` accept `const DiversifyCompletionResult&` so the FSM
validates `result.complete` — this is one line but significantly stronger than a pure flag.
Also: move history annotation to STRUCTURING entry (done) and fix to_restart() reset (done).
Full token refactor eliminates the honor-system problem and all reset fragility entirely.
