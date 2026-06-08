Claude charter

I’ll fetch all the source files before reviewing. Let me pull everything.

Good. All seven files retrieved. Now I’ll write the review.

No skill for plain markdown — straightforward write. Let me produce the review document.

Review complete. Three confirmed bugs, two design-phase concerns. Summary of findings:

Priority 1 — evaluate_g2() wrong failure route. MockLLMInterface returns FailureRoute::DIVERSIFY for G2 failure. Charter mandates RESTART. The priority rule in HardGates::route() masks this today but it will propagate into AnthropicLLMInterface as a silent defect. Single-line fix.

Priority 2 — Watchdog drift not enforced. to_converge() throws on missing report (correct) but doesn’t block when drift_suspected_ == true after a report is submitted. Charter says drift assessment is “itself sufficient grounds” for mandatory DIVERSIFY — the FSM currently allows CONVERGE right past it. One-line fix in CharterFSM::to_converge().

Priority 3 — missing_structural_fields() is broken. The TODO is real. The function uses charter_version.empty() (an orientational field) as a proxy for structural field absence — a category error. All four structural fields need std::optional<T> wrapping with has_value() checks. Fresh sessions should initialize all four to present-with-zero-state, not absent.

Design concerns (before LLM wiring):

	•	check_hypothesis_under_specification() ignores differing_prediction entirely and has no semantic check for genuinely distinct predictions. Trigger 1 will pass on two identical hypotheses with different labels.
	•	G5 prompt must explicitly encode the two pass conditions (mechanism proposed + distinguished vs. mechanism unknown + artifact self-identifies). Without this, any mechanism text passes G5 regardless of whether the phenomenological-case requirements are met.

# C++ Skeleton Review — Claude Sonnet 4.6

**Reviewed:** 2026-06-08
**Artifact:** `charter-cpp` skeleton (headers + `main.cpp`)
**Charter reference:** CHARTER.md on-disk = v2.6; skeleton claims v2.7

-----

## Q1 — FSM Routing

### Verdict: Mostly correct. One confirmed gap, one latent bug.

**What is correct:**

`fsm.h` documents the legal transition table and the comment block matches v2.3/v2.4 routing rules:

- `DIVERSIFY → STRUCTURING` (not `GATE_CHECK`) is explicitly stated and enforced via `validate_transition()` (the enforcement demo in `main.cpp` confirms the throw).
- `CONVERGE` precondition (`had_prior_diversify_or_restart_`) is tracked and checked in `to_converge()`.
- The two-phase gate protocol (G1/G2 → RESTART; G3/G5 → DIVERSIFY; G4 → RESTART) is correctly mapped in `gates.h` and the priority rule (`RESTART > DIVERSIFY`) is stated in `HardGates::route()`.

**Gap 1 — Phase 1 routing: G2 failure must route to RESTART, not DIVERSIFY.**

`gates.h` declares:

> Phase 1 — Prerequisites (G1, G2): If either fails, move immediately to RESTART.

But `MockLLMInterface::evaluate_g2()` in `llm_interface.h` returns `FailureRoute::DIVERSIFY` on G2 failure:

```cpp
g2_passes ? FailureRoute::NONE : FailureRoute::DIVERSIFY   // ← WRONG
```

The charter is unambiguous: G2 failure → RESTART. `FailureRoute::DIVERSIFY` here means that if `HardGates::route()` sees a G2 failure before any G4 result, the priority rule (`RESTART > DIVERSIFY`) will save the routing — but only because G4 hasn’t fired. If a future test configures both G2 fail and G3/G5 fail with no G4 result in the batch, the mock returns `DIVERSIFY` where the charter demands `RESTART`. This is a mock defect that will become a production defect when `AnthropicLLMInterface` is copy-pasted from the mock. **Fix:** change `evaluate_g2()` failure route to `FailureRoute::RESTART`.

**Gap 2 — Watchdog-triggered DIVERSIFY has no FSM-enforced path.**

The charter states: if `drift_suspected` after a Watchdog Report, DIVERSIFY is mandatory regardless of standard conditions. `submit_watchdog_report()` in `fsm.h` sets `drift_suspected_` and `watchdog_report_pending_` — but `to_converge()` checks `watchdog_required()` (fires a `WatchdogRequiredError` if 3 consecutive CONVERGEs without a report) without checking `drift_suspected_` after a report is submitted. There is no code path that *forces* the FSM into DIVERSIFY when drift is suspected. The FSM will allow `to_converge()` to proceed immediately after `submit_watchdog_report(..., true)`. **Fix:** `to_converge()` must check: if `drift_suspected_ == true`, throw `ConvergePreconditionError("Watchdog drift assessment requires DIVERSIFY before next CONVERGE")`.

**No spurious transitions found.** The `validate_transition()` matrix appears consistent with the documented legal set. `OUTPUT → STRUCTURING` is permitted and correct (new session on same topic).

-----

## Q2 — LLM Interface Boundary

### Verdict: Mostly correct split. One misclassification (G2); one underspecified semantic delegation (G5).

**`types.h` classification:**

```cpp
constexpr bool is_mechanical(GateId g) {
    return g == GateId::G1 || g == GateId::G4;
}
```

G1 (count ≥ 2 thresholds) and G4 (immutability check) are correctly classified as mechanical. G2, G3, G5 delegate to the LLM.

**G2 — partially mechanical, over-delegated.**

G2 asks: is the claim “specific and limited in scope”? That is semantic. But the structuring contract already requires `central_claim ≤ 3 sentences`. Sentence count is mechanical and is not checked anywhere. A pre-filter should reject a `central_claim` that exceeds 3 sentences before invoking the LLM for scope judgment. This is a minor efficiency issue, not a correctness defect — but it means the LLM is asked to evaluate scope on claims that fail a structural prerequisite.

**G4 — correct.**

`MechanicalGates::evaluate_g4()` locks thresholds on first call and compares current values to locked values. Fully mechanical, correctly classified.

**G5 — semantic delegation is correct but the prompt contract is underspecified.**

G5 requires the LLM to assess whether mechanism *status* is declared — not whether a mechanism is *known*. The interface signature is correct (`evaluate_g5(const StructuredArtifact&)`), but `ILLMInterface` provides no guidance on what the prompt must include to distinguish the two G5 pass conditions:

- (a) mechanism proposed + explicitly distinguished from supporting evidence
- (b) mechanism unknown + artifact self-identifies as phenomenological/predictive/exploratory + discriminating test proposed

The mock returns a single binary pass/fail. A real implementation that doesn’t distinguish (a) from (b) will pass G5 whenever *any* mechanism text appears in the artifact, regardless of whether condition (b)’s requirements are met. This needs to be in the prompt spec (see Q5).

**G3 — semantic delegation correct.** Operational definition completeness is inherently semantic. No issue.

**Summary of split:**

|Gate|Classification|Verdict                                    |
|----|--------------|-------------------------------------------|
|G1  |Mechanical    |✓ Correct                                  |
|G2  |LLM semantic  |✓ Correct (add sentence-count pre-filter)  |
|G3  |LLM semantic  |✓ Correct                                  |
|G4  |Mechanical    |✓ Correct                                  |
|G5  |LLM semantic  |✓ Correct (prompt must distinguish (a)/(b))|

-----

## Q3 — State Compression Validity

### Verdict: The TODO is real and the heuristic is wrong. `std::optional` is the right fix but needs care.

**Current heuristic in `types.h`:**

The comment acknowledges a TODO: `missing_structural_fields()` uses `charter_version.empty()` as a proxy for “structural fields missing.” This is an orientational field used to detect missing structural fields — a category error.

**The correct fix:**

The four structural fields are `gate_status`, `objection_register`, `constraint_health`, and `adversarial_anchor`. The right approach depends on what “missing” means for each type:

1. **`gate_status` (`std::vector<std::pair<...>>`)** — an empty vector is ambiguous: it could mean “no artifacts tracked” (legitimate for a fresh session) or “field not populated.” Wrapping in `std::optional<std::vector<...>>` resolves this: `std::nullopt` = not populated; empty vector = no open artifacts.
1. **`objection_register` (`std::vector<Objection>`)** — same ambiguity as `gate_status`. Same fix: `std::optional<ObjectionRegister>`.
1. **`constraint_health` (`ConstraintHealth`)** — a struct with three fields. No natural “empty” sentinel. `std::optional<ConstraintHealth>` is correct; `std::nullopt` = not populated.
1. **`adversarial_anchor` (`AdversarialAnchor`)** — has `watchdog_fired = false` as default. This is a valid value (watchdog didn’t fire), not a sentinel for “missing.” Cannot use the default to detect absence. `std::optional<AdversarialAnchor>` is correct.

**Recommended approach:**

```cpp
// In StateCompression — structural fields become optional
std::optional<std::vector<std::pair<std::string, GateStatus>>> gate_status;
std::optional<ObjectionRegister> objection_register;
std::optional<ConstraintHealth> constraint_health;
std::optional<AdversarialAnchor> adversarial_anchor;

std::vector<std::string> missing_structural_fields() const {
    std::vector<std::string> missing;
    if (!gate_status.has_value())        missing.push_back("gate_status");
    if (!objection_register.has_value()) missing.push_back("objection_register");
    if (!constraint_health.has_value())  missing.push_back("constraint_health");
    if (!adversarial_anchor.has_value()) missing.push_back("adversarial_anchor");
    return missing;
}
```

**Downstream impact:** `compress()` in `SessionContinuity` must always populate all four optional fields before returning. `deserialize()` must handle `std::nullopt` as an invalid handoff condition. `fresh_session()` should initialize all four to `has_value() == true` with appropriate zero-state values (empty vectors, zero-count health, `watchdog_fired = false` anchor) — a fresh session is not a missing-field session.

**Alternative considered — sentinel structs:** Defining a `ConstraintHealth::unknown()` factory returning a sentinel value avoids `std::optional` but introduces implicit states that are harder to reason about statically. `std::optional` is the cleaner approach here.

-----

## Q4 — DIVERSIFY Trigger 1: Structural vs. Semantic Check

### Verdict: The structural check is insufficient. LLM verification is required for “genuinely distinct.” Exact insertion point identified.

**What the code checks (`coherence_controller.h`):**

`check_hypothesis_under_specification()` verifies:

- count ≥ 2 hypotheses
- each has non-empty `id`, `evidence_level`, `independent_variable`, `dependent_variable`

This satisfies the structural requirements of v2.6 Trigger 1 conditions (a), (b), (c) formally.

**What the charter actually requires:**

The word “genuinely distinct” does not appear verbatim in v2.6, but the requirement does: a hypothesis is documented only if it includes “a discriminating test proposal with at least one named IV and one named DV.” The *point* of a discriminating test is that the hypotheses make different predictions — two hypotheses with the same IV, DV, and prediction direction but different labels are structurally valid but informationally identical. Trigger 1 would not fire, but DIVERSIFY intent is defeated.

Additionally, `Hypothesis.differing_prediction` exists in the struct and is populated in `main.cpp` for H1 — but `check_hypothesis_under_specification()` does not check it at all. This is a structural field that was added specifically to capture the “differing prediction” requirement and is silently ignored by the trigger check.

**Where to add the LLM call:**

In `CoherenceController::check_hypothesis_under_specification()`, after the structural count/field check passes, add:

```cpp
// If structural check passes but we have >= 2 hypotheses,
// ask the LLM whether the hypotheses make genuinely distinct predictions.
if (hypotheses.size() >= 2) {
    bool distinct = llm_->hypotheses_are_genuinely_distinct(hypotheses);
    if (!distinct) {
        return { true, 1, "Hypotheses share predictions — structurally present "
                          "but not discriminating; Trigger 1 fires" };
    }
}
```

This requires adding `virtual bool hypotheses_are_genuinely_distinct(const std::vector<Hypothesis>&) = 0` to `ILLMInterface`. The mock implementation returns `true` by default (safe — structural check is the conservative path).

**Also fix:** `check_hypothesis_under_specification()` should check that `differing_prediction` is non-empty for each hypothesis. This is purely structural and costs nothing.

-----

## Q5 — Anthropic API Integration

### Sketch for `AnthropicLLMInterface`

**HTTP client / SDK:**

Use `libcurl` with a thin C++ wrapper, or `cpp-httplib` (header-only, no heavy dependency). Do not use a full SDK — the Anthropic API surface needed here is a single POST endpoint. Keep the dependency surface minimal.

```cpp
// Dependency: cpp-httplib (https://github.com/yhirose/cpp-httplib)
// + nlohmann/json for request/response serialization
#include <httplib.h>
#include <nlohmann/json.hpp>
```

**Prompt structure for G2, G3, G5:**

Each gate needs a system prompt that defines the evaluation criteria precisely and demands structured JSON output. The G5 system prompt must explicitly encode the two pass conditions to fix the Q2 defect.

```
// G2 system prompt
"You are evaluating Gate 2 (Bounded Scope) of a research artifact under the
Research Assistant Charter. The gate passes if and only if the central claim is
specific (names a concrete observable, population, and measurement) and limited
in scope (does not make claims beyond what the stated test can directly assess).
Respond ONLY with valid JSON: {\"status\": \"PASS\"|\"FAIL\", \"defect\": \"<string or empty>\"}
A PASS defect field must be empty. A FAIL defect field must name the specific
scope violation."

// G3 system prompt
"You are evaluating Gate 3 (Operational Definitions) of a research artifact
under the Research Assistant Charter. The gate passes if and only if every key
term in the central claim maps to a measurable quantity or procedure with a
stated measurement window. Respond ONLY with valid JSON:
{\"status\": \"PASS\"|\"FAIL\", \"defect\": \"<string or empty>\",
\"undefined_terms\": [\"term1\", ...]}"

// G5 system prompt — must distinguish (a) from (b)
"You are evaluating Gate 5 (Mechanism Status) of a research artifact under the
Research Assistant Charter. The gate PASSES under either of two conditions:
(a) A proposed mechanism is stated AND explicitly distinguished from the
evidence supporting it (the mechanism is not the evidence; the evidence is
not the mechanism); OR
(b) The mechanism is declared unknown AND the artifact explicitly identifies
itself as phenomenological, predictive, or exploratory AND a discriminating
test is proposed that would distinguish at least two plausible mechanistic
explanations.
Mechanism unknown is NOT a gate failure. Mechanism status undeclared IS.
Respond ONLY with valid JSON:
{\"status\": \"PASS\"|\"FAIL\", \"pass_condition\": \"a\"|\"b\"|null,
\"defect\": \"<string or empty>\"}"
```

**Parsing `GateEvaluation` from the response:**

```cpp
GateEvaluation AnthropicLLMInterface::parse_gate_response(
    GateId gate, FailureRoute on_fail, const std::string& response_text)
{
    auto j = nlohmann::json::parse(response_text);  // wrap in try/catch
    GateStatus status = (j["status"] == "PASS") ? GateStatus::PASS : GateStatus::FAIL;
    std::string defect = j.value("defect", "");
    return { gate, status, defect,
             status == GateStatus::FAIL ? on_fail : FailureRoute::NONE };
}
```

The `on_fail` route is passed in by the caller (not decided by the LLM) — `FailureRoute::RESTART` for G2, `FailureRoute::DIVERSIFY` for G3/G5. The LLM returns semantic judgment only; routing stays in C++.

**Rate limiting / retry strategy:**

```cpp
// Retry with exponential backoff — 3 attempts, 1s/2s/4s
// On 429: honor Retry-After header if present
// On 529 (overloaded): treat as 429
// On 5xx: retry with backoff
// On 4xx (except 429): do not retry — bad request, surface to caller
static constexpr int MAX_RETRIES = 3;
static constexpr int BASE_DELAY_MS = 1000;
```

A per-session token budget should be tracked. Gate calls are small (artifact JSON is typically < 2K tokens). Budget 500 output tokens per gate call; the structured JSON responses are short.

**Batching vs. separate calls:**

**Separate calls, sequenced.** Do not batch G2/G3/G5 into one call. Reasons:

1. The two-phase protocol means G2 failure short-circuits — never call G3/G5 if G2 fails. A batched call always pays for all three.
1. Each gate’s prompt is adversarially focused. A combined prompt risks the model trading off between gates in its chain-of-thought, softening defects to produce a coherent overall narrative. The charter’s requirement that each gate is a non-negotiable independent checkpoint maps cleanly to independent calls.
1. Retry granularity: a G3 network failure should not require re-running G2.

**Sequence:** G1 (mechanical) → G2 (LLM) → if pass → G3 (LLM) + G5 (LLM, can run in parallel with G3) → G4 (mechanical, any time after thresholds set).

G3 and G5 can be parallelized with `std::async` — they are independent and both route to DIVERSIFY on failure. G4 runs last or concurrently; its result is required before final routing.

-----

## Summary

The skeleton is structurally sound. The FSM transition table is correct, the two-phase gate protocol is correctly modeled, and the mechanical/semantic split is well-conceived. Three issues require fixes before wiring a real LLM:

**Priority 1 (HIGH — correctness bug):** `MockLLMInterface::evaluate_g2()` returns `FailureRoute::DIVERSIFY` on failure. Charter mandates `FailureRoute::RESTART`. Fix in the mock now to prevent the defect propagating into `AnthropicLLMInterface` by copy.

**Priority 2 (HIGH — charter violation at runtime):** `to_converge()` does not block when `drift_suspected_ == true` after a Watchdog Report. A watchdog that finds drift must force DIVERSIFY; the current code allows CONVERGE to proceed immediately. One-line fix in `CharterFSM::to_converge()`.

**Priority 3 (MEDIUM — structural field detection broken):** `StateCompression::missing_structural_fields()` uses `charter_version.empty()` (an orientational field) to detect missing structural fields. Replace all four structural fields with `std::optional<T>` and check `has_value()`. Required before the session continuity protocol can enforce the invalid-handoff rule.

The `check_hypothesis_under_specification()` semantic gap (Q4) and the G5 two-condition prompt spec (Q5) are design-phase concerns — they do not affect the skeleton’s current test coverage but will produce false negatives at E2/E3 research quality without the LLM call and prompt structure described above.