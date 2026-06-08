# K1 DIVERSIFY Enforcement Review — Claude Sonnet 4.6

**Reviewed:** 2026-06-08
**Scope:** Option A `declare_diversify_complete()` design decision
**Source state:** fsm.h + fsm.cpp fetched from main — `declare_diversify_complete()`
not present in fetched files; reviewed as designed per background specification.
Charter reference: CHARTER.md v2.6 (§3 DIVERSIFY exit criterion, v2.5).

---

## Q1 — Option A Blind Spots

**Yes. Two distinct blind spots. Option B closes both.**

**Blind spot 1 — Decoupled call, no result required.**

`declare_diversify_complete()` takes no arguments. A caller can call it without
ever calling `check_diversify_complete()`. The FSM has no visibility into whether
a `DiversifyCompletionResult` with `complete == true` was ever produced. The honor-
system problem is moved one level up, not eliminated.

Option B closes this because `to_structuring_from_diversify(result)` requires the
caller to have a `DiversifyCompletionResult` in hand — a proof of work token.

**Blind spot 2 — Stale declaration survives PSP continuation.**

If `declare_diversify_complete()` is called and then additional PSP work invalidates
condition (b), the flag stays set and `to_structuring()` proceeds on a stale result.
Option B doesn't fully close this either, but the result object makes staleness
visible in code review in a way the flag does not.

---

## Q2 — Compile-Time Contract Enforcement

**Recommended: private-constructor nested type + move-only token (C++17, no exotic machinery).**

`DiversifyCompletionResult` as a free aggregate struct is constructible by anyone —
Option B as sketched is also defeatable with `fake.complete = true`. The fix:

```cpp
// In coherence_controller.h
class CoherenceController {
public:
    class DiversifyCompletionResult {
        friend class CoherenceController;
    public:
        bool complete() const { return complete_; }
        const std::vector<std::string>& unmet() const { return unmet_; }
        // Move-only: token is consumed on use, cannot be replayed
        DiversifyCompletionResult(const DiversifyCompletionResult&) = delete;
        DiversifyCompletionResult& operator=(const DiversifyCompletionResult&) = delete;
        DiversifyCompletionResult(DiversifyCompletionResult&&) = default;
    private:
        explicit DiversifyCompletionResult(bool c, std::vector<std::string> u)
            : complete_(c), unmet_(std::move(u)) {}
        bool complete_;
        std::vector<std::string> unmet_;
    };

    [[nodiscard]] DiversifyCompletionResult check_diversify_complete(...) const;
};
```

`to_structuring_from_diversify(DiversifyCompletionResult result)` takes by value —
token is consumed. A caller cannot fabricate one without going through
`check_diversify_complete()`. `[[nodiscard]]` catches the "called and ignored" case.

---

## Q3 — History Log Placement

**Wrong placement. Second DIVERSIFY entry creates ambiguity.**

A second `(DIVERSIFY, "completion declared")` entry for one DIVERSIFY cycle
misrepresents session trajectory and complicates Watchdog log parsing.

Correct: attach completion status to the STRUCTURING entry on exit:
```
(STRUCTURING, "DIVERSIFY complete [a✓ b✓ c✓] — artifact revised with operationalized 'fatigue'")
```

The DIVERSIFY entry records *why DIVERSIFY was entered*; the STRUCTURING entry
records *that DIVERSIFY was completed and on what basis exit was authorized*.
If Option B is adopted, the unmet conditions from the token can be logged directly.

---

## Q4 — Reset Timing

**Confirmed gap: to_restart() does not reset diversify_complete_declared_.**

Path:
```
to_diversify("trigger")          // flag = false
declare_diversify_complete()     // flag = true
to_restart({"structural flaw"})  // flag still = true — dirty state
to_structuring("after restart")  // from RESTART — succeeds, flag = true but not checked
to_gate_check()
to_diversify("new trigger")      // flag reset here — saved only by accident
```

The flag is dirty in RESTART and STRUCTURING states after `to_restart()`. The carry-
over doesn't cause a bad exit in the current transition table (because `to_diversify()`
resets it before STRUCTURING is reached from DIVERSIFY again), but it is a latent defect:
the flag's value is meaningless outside a DIVERSIFY cycle.

Fix: add `diversify_complete_declared_ = false` to `to_restart()`.

---

## Verdict

**Amend Option A to become Option B with an unforgeable move-only token.**

Option A as implemented is a flag with an honor-system caller contract — structurally
identical to having no enforcement, just one abstraction level higher. The correct fix
is the private-constructor nested type (Q2), making `check_diversify_complete()` the
only legal token source, combined with a move-only token consumed by
`to_structuring_from_diversify()` on exit.

Unambiguous fixes regardless of Option A vs B:
- to_restart() must reset diversify_complete_declared_ (Q4)
- completion annotation belongs on the STRUCTURING log entry, not a second DIVERSIFY entry (Q3)
