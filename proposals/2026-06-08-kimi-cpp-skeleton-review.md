# C++ Skeleton Review — Kimi K2.6

**Reviewed:** 2026-06-08
**Artifact:** `charter-cpp` skeleton (headers + `main.cpp`)
**Charter reference:** v2.7

---

## Q1 — FSM Routing

**What is correct:**
- DIVERSIFY → STRUCTURING only (v2.3 routing fix confirmed) ✓
- G1/G2 failure → RESTART (enforced by HardGates::evaluate() short-circuit) ✓
- G3/G5 failure → DIVERSIFY; G4 failure → RESTART (enforced by HardGates::route() priority) ✓
- CONVERGE preconditions (all gates, no open objections, prior DIVERSIFY/RESTART) ✓

**Bug 1 — DIVERSIFY completion not enforced before DIVERSIFY → STRUCTURING**

File: `fsm.cpp`
Function: `CharterFSM::to_structuring()`

The validate_transition() table correctly forbids DIVERSIFY → GATE_CHECK. However, the FSM
permits to_structuring() from DIVERSIFY unconditionally. The charter (v2.5) makes the
three-part completion condition mandatory — new competing hypothesis, new substantive
objection, artifact revised or justified — "On completion" is not agent-discretionary.
An incomplete DIVERSIFY can currently escape to STRUCTURING, potentially reaching a false
CONVERGE without the required adversarial work.

Fix: to_structuring() should check DIVERSIFY completion criteria when transitioning from
DIVERSIFY. Options: (a) add `declare_diversify_complete()` to set a flag the FSM checks,
(b) add a `to_structuring_from_diversify(const DiversifyCompletionResult&)` overload.

**Bug 2 — OUTPUT and INIT not blocked when watchdog pending or drift suspected**

File: `fsm.cpp`
Functions: `to_output()`, `to_init()`

After `submit_watchdog_report(drift_suspected=true)`, the charter says DIVERSIFY is
mandatory. The code blocks to_converge() when drift_suspected_ is true (correct), but
to_output() and to_init() remain unblocked. A caller can skip DIVERSIFY entirely by
going directly to OUTPUT or starting a new session (INIT), defeating the mandatory
adversarial challenge. Additionally, to_output() does not check watchdog_report_pending_,
so the Watchdog can be bypassed by going CONVERGE → OUTPUT before submitting a report.

Fix: to_output() must check watchdog_report_pending_ (throw if true). Both to_output()
and to_init() must check drift_suspected_ (throw if true).

---

## Q2 — LLM Interface Boundary

**Correct splits:** G1/G4 mechanical, G2/G3/G5 semantic — confirmed correct.

**Bug — G5 needs mechanical pre-check before LLM delegation**

File: `gates.h` / `gates.cpp`
Function: `HardGates::evaluate()`

G5 has a mechanical component: the artifact must explicitly identify itself as
phenomenological/predictive/exploratory when mechanism is unknown. This is a structural
presence check (does the mechanism_status declaration exist and is non-empty?) that can
be done before delegating semantic judgment to the LLM.

If the artifact lacks a mechanism_status field entirely, the LLM might incorrectly pass
it based on surrounding context. A missing declaration is an immediate structural FAIL;
only when the field is present should the LLM judge whether the declaration is correct
(condition a vs. condition b).

Fix: Add a MechanicalGates pre-check for G5 structural completeness before calling
llm_->evaluate_g5(). If the relevant field is absent, return FAIL immediately.

---

## Q3 — State Compression Validity

Agrees with std::optional fix. Correctly identifies that charter_version proxy is
fragile. Recommends the same std::optional<T> pattern for the four structural fields.

Status: Implemented in Cycle 2 fixes (commit c4517b5).

---

## Q4 — DIVERSIFY Trigger 1

Structural check is insufficient. Two hypotheses with identical IVs/DVs/predictions
but different labels pass the count. Recommends adding `assess_hypothesis_distinctness()`
to ILLMInterface, called after structural count passes.

Proposed new ILLMInterface method:
```
struct DistinctnessAssessment {
    bool genuinely_distinct;
    std::string reason;
};
virtual DistinctnessAssessment assess_hypothesis_distinctness(
    const std::vector<Hypothesis>& hypotheses) = 0;
```

Status: differing_prediction structural check added (Cycle 2). LLM semantic verification
deferred — design-phase concern.

---

## Q5 — Anthropic API Integration

- HTTP client: libcurl + nlohmann/json; connection pooling + HTTP/2 if available
- Rate limit: ~40 req/min for Sonnet; token-bucket limiter
- Retry: exponential backoff 1s/2s/4s/8s, max 4 retries; 429/502/503/504 only
- Circuit breaker: 5 consecutive failures → open circuit 60s → FAIL + RESTART
- Batching: separate calls per gate (correct); exception: generate_competing_hypotheses()
  and generate_objections() could be batched since both are needed together in DIVERSIFY
- Parsing: strict JSON schema validation before parsing; malformed response → FAIL + RESTART

---

## Summary

The skeleton correctly captures the routing topology. Three issues before LLM wiring:
(1) DIVERSIFY completion must be enforced before STRUCTURING re-entry — highest priority,
because an incomplete DIVERSIFY reaching GATE_CHECK produces false convergence;
(2) to_output() and to_init() must check watchdog_report_pending_ and drift_suspected_
to prevent Watchdog/drift bypass;
(3) G5 needs a mechanical presence pre-check before LLM delegation.
