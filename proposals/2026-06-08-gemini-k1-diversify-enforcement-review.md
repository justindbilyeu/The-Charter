# K1 DIVERSIFY Enforcement Review — Gemini

**Reviewed:** 2026-06-08
**Scope:** Option A `declare_diversify_complete()` design decision

---

## Q1 — Option A Blind Spots

Option A suffers from a structural decoupled-state vulnerability that Option B entirely prevents. Because `declare_diversify_complete()` relies on an internal boolean flag (`diversify_complete_declared_`), it decouples the *validation proof* from the *state transition action*.

**The failure mode:** A caller can bypass actual validation by calling `fsm.declare_diversify_complete()` blindly, passing no empirical evidence, or using a stale/hardcoded local block. It reduces a structural contract down to an honor-system flag toggle.

**The blind spot:** Option B treats the `DiversifyCompletionResult` as a structural passkey. Under Option A, the FSM has no visibility into *why* diversification is complete; it blindly trusts that a previous line of code executed the check truthfully. The flag approach pushes the honor-system problem one level up to the orchestration loop.

---

## Q2 — Compile-Time Contract Enforcement

Use a strict **Capability Token / Typestate Pattern** in C++17. Instead of maintaining a mutable flag inside the FSM, force `to_structuring` to require a move-only token that can only be minted by the `CoherenceController` upon successful validation.

```cpp
// 1. Define a non-copyable, move-only proof token
class DiversifyProofToken {
    friend class CoherenceController; // Only CC can construct this
    DiversifyProofToken() = default;
public:
    DiversifyProofToken(const DiversifyProofToken&) = delete;
    DiversifyProofToken& operator=(const DiversifyProofToken&) = delete;
    DiversifyProofToken(DiversifyProofToken&&) = default;
    DiversifyProofToken& operator=(DiversifyProofToken&&) = default;
};

// 2. CoherenceController mints the token upon actual validation
class CoherenceController {
public:
    std::pair<DiversifyCompletionResult, std::optional<DiversifyProofToken>>
    verify_diversify_complete(const CoherenceState& state) {
        // ... execute checks (a), (b), and (c) ...
        if (all_conditions_met) {
            return {result, DiversifyProofToken{}};
        }
        return {result, std::nullopt};
    }
};

// 3. FSM demands the token directly in the method signature
void CharterFSM::to_structuring(DiversifyProofToken token, const std::string& reason) {
    // If it compiles, the caller MUST have passed through the CC.
    // The state transition is statically guaranteed to be authentic.
    state_ = State::STRUCTURING;
    record(State::STRUCTURING, reason);
}
```

This forces compile-time compliance: the orchestrator cannot step into STRUCTURING without providing the token, eliminating runtime `DiversifyIncompleteError` exceptions and protecting the FSM boundary from developer oversight.

---

## Q3 — History Log Placement

Recording a second `DIVERSIFY` entry inside `declare_diversify_complete()` while the machine is still in DIVERSIFY state creates a fragmented trace. It implies a state transition occurred when only a state *qualification* changed.

**Correct approach:** Bundle the completion annotation payload with the subsequent STRUCTURING entry.

**Justification:** The transition *out* of diversification is the functional action driven by the completion criteria. Logging `STRUCTURING [Reason: Diversification Criteria Met: (a) Hypo-3, (b) Obj-12, (c) Revision-v2]` keeps the history cleaner, preserves the alternating state rhythm, and provides a clear audit trail explaining why the machine was authorized to advance.

**Status:** Already fixed — `declare_diversify_complete()` no longer records a DIVERSIFY entry; completion shows on the STRUCTURING entry.

---

## Q4 — Reset Timing

Resetting `diversify_complete_declared_` in `to_structuring()`, `to_diversify()`, and `to_init()` covers standard sequential tracks, but there is a hidden vulnerability during abnormal exits.

**The carrying leak:** If the FSM is forced from DIVERSIFY back to an intermediate state without cycling through `to_structuring()` or a clean `to_diversify()`, the boolean flag remains set to `true`.

**The vulnerability:** If the FSM later returns to DIVERSIFY via a non-standard pathway, the stale flag would allow it to exit immediately to STRUCTURING without validating the new context. Relying on manually placing resets across distributed transition paths is error-prone. The flag should be managed by a scoped RAII object tied to the lifetime of the active DIVERSIFY state instance.

**Note:** The token pattern eliminates this entirely — no persistent flag, no reset management problem.

---

## Verdict

Switch to Option B, enhanced with the move-only Capability Token pattern described in Q2, to completely replace runtime flag verification with compile-time contract enforcement.
