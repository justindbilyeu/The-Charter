# K1 DIVERSIFY Enforcement Review — Grok

**Reviewed:** 2026-06-08
**Scope:** Option A `declare_diversify_complete()` design decision

---

## Q1 — Option A Blind Spots

Yes, clear failure mode. `declare_diversify_complete()` is a simple flag flip.
A caller can invoke it arbitrarily without ever calling `check_diversify_complete()`
or producing a `DiversifyCompletionResult`. Option A moves the problem up one layer
without closing the hole — purely honor-system at the caller site.

Option B's `to_structuring_from_diversify(const DiversifyCompletionResult&)` makes
the result itself the capability token, forcing the caller to perform the check and
pass evidence of it. No compile-time safety in Option A; easy to bypass.

---

## Q2 — Compile-Time Contract Enforcement

Best practical approach (C++17, no heavy template machinery):

- Capability/token pattern: `struct DiversifyCompletionToken { explicit
  DiversifyCompletionToken(DiversifyCompletionResult r); };` — `to_structuring(token)`
  consumes it. Misuse is a compile error.
- Or: `to_structuring_from_diversify(DiversifyCompletionResult result, ...)` as an
  overload; `to_structuring()` from DIVERSIFY state throws unless the overload was used.
- Alternative: make `declare_diversify_complete()` private and only callable via
  a friend factory in `CoherenceController`.

Current sequence is easy to violate (forget the `if (result.complete)` guard or call
`declare` unconditionally). Token/overload approach is superior for contract strength.

---

## Q3 — History Log Placement

Acceptable but suboptimal. A `(DIVERSIFY, "completed")` / `(DIVERSIFY, entry)` pair
is useful for audit, but the annotation belongs with the STRUCTURING transition — the
semantically important state change the charter emphasizes. The STRUCTURING reason
parameter is the right place for completion evidence. Avoids duplicate DIVERSIFY records.
Not wrong in current form, but cleaner on STRUCTURING.

---

## Q4 — Reset Timing

Reset logic mostly solid. One subtle risk: if `declare_diversify_complete()` is called
and then an exception or early return occurs before `to_structuring()`, the flag stays
set. A subsequent `to_diversify()` (new DIVERSIFY cycle) would reset it — so the carry-
over doesn't persist across cycles. But the flag is "dirty" between the exception and
the next `to_diversify()` call. A RAII approach or tying the reset more tightly to the
successful transition would be cleaner.

Note: `to_restart()` not resetting the flag is also a dirty-state path (flag = true
in RESTART state after a declare + restart sequence).

---

## Verdict

Amend Option A — promote `DiversifyCompletionResult` (or a token) into the transition
API for stronger enforcement. Do not fully switch to Option B if Option A is already
live, but harden it significantly (token pattern + to_restart() reset) before LLM wiring.
