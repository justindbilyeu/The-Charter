Grok charter

File: 2026-06-08-grok-cpp-skeleton-review.md
C++ Skeleton Review — Grok
Q1 — FSM Routing
Yes, CharterFSM.cpp (and fsm.h) correctly enforces all listed rules.
	•	DIVERSIFY → STRUCTURING only: validate_transition() explicitly allows only STRUCTURING from DIVERSIFY (with a clear error message for the old GATE_CHECK shortcut).
	•	G1/G2 failure → RESTART: HardGates::evaluate() short-circuits on G1 or G2 FAIL and route() prioritizes RESTART (G1/G2 set FailureRoute::RESTART).
	•	G3/G5 failure → DIVERSIFY; G4 → RESTART: Phase 2 evaluates all validators; route() checks for any RESTART first (G4 priority), then DIVERSIFY.
	•	CONVERGE requires all gates pass + no open objections + prior DIVERSIFY/RESTART: to_converge() explicitly validates artifact.all_gates_pass(), !has_open_objections(), and had_prior_diversify_or_restart_. Watchdog enforcement and 3x CONVERGE handling are also present.
No forbidden transitions permitted, no permitted transitions forbidden. The FSM is strict and matches v2.3/v2.4 routing precisely. No bugs found.910
Q2 — LLM Interface Boundary
The mechanical/semantic split in gates.h/types.h is correct and well-implemented.
	•	Mechanical: G1 (threshold count in MechanicalGates::evaluate_g1) and G4 (immutability/locking in evaluate_g4) — fully in C++, no LLM.
	•	Semantic: G2 (scope), G3 (operational defs), G5 (mechanism status) delegated to ILLMInterface::evaluate_g2/3/5 — correct per charter §2.
	•	No mechanical checks incorrectly sent to LLM. No semantic checks hardcoded mechanically (e.g., G3 is not a simple keyword search).
The boundary is clean; C++ owns structure/routing/invariants, LLM owns meaning. Matches charter intent perfectly.3
Q3 — State Compression Validity
The current heuristic in StateCompression::missing_structural_fields() (types.cpp) is inadequate — it relies on charter_version.empty() as a proxy, which is brittle and noted as TODO.
Correct fix: Wrap the structural fields (gate_status, objection_register, constraint_health, adversarial_anchor) in std::optional<...> (already partially supported via headers). Update is_valid() / missing_structural_fields() to check !field.has_value(). This makes “missing” unambiguous vs. empty/default.
Alternative (lighter): Add explicit bool flags (bool gate_status_present = false;, etc.) set during compression, but std::optional is cleaner and aligns with modern C++. Production serialization (JSON) should respect optionals. This is the highest-priority pre-LLM fix to prevent invalid handoffs.8
Q4 — DIVERSIFY Trigger 1 — Structural VS Semantic Check
The current structural check in check_hypothesis_under_specification() (coherence_controller.cpp) is insufficient for full charter fidelity.
It correctly counts well-formed structs (ID + E-level + IV + DV) but does not verify “genuinely distinct” predictions (charter v2.5: “at least one prediction that differs from the primary claim”). This is a semantic judgment.
Recommendation: Add LLM verification. Extend ILLMInterface with bool hypotheses_are_distinct(const std::vector&, const StructuredArtifact& primary) or integrate into generate_competing_hypotheses() (which already aims for differing predictions). Call it inside check_hypothesis_under_specification() (or a new verify_distinct_predictions()) and combine with the structural count. Structural check remains a fast pre-filter; LLM provides the decisive semantic layer. Update DiversifyCompletionResult similarly.11
Q5 — Anthropic API Integration
Sketch for AnthropicLLMInterface : public ILLMInterface:
	•	HTTP Client/SDK: Use curl + nlohmann/json (lightweight, no heavy deps) or the official Anthropic C++ SDK if available. Wrap in a simple AnthropicClient class handling auth (x-api-key), base URL, and messages endpoint.
	•	Prompt structure: System prompt enforcing charter §2/§3/§4 (strict JSON output schema). User message: artifact + context + specific gate instruction (e.g., for G2: “Is the central claim bounded in scope? Output JSON with pass/fail + defect”). Use structured outputs / tool calling for GateEvaluation (or parse JSON response with fields: {"gate": "G2", "status": "PASS/FAIL", "defect": "...", "route": "..."}). Similar for G3/G5, generate_objections, generate_competing_hypotheses, etc.
	•	Rate limiting/retry: Token-based limiter (e.g., 50 req/min for Sonnet); exponential backoff (1s → 4s → 16s) with jitter; max 3 retries on 429/5xx. Circuit breaker for prolonged outages. Log usage for cost monitoring.
	•	Separate vs. batched: Separate API calls per gate for isolation, clear attribution, and short-circuiting (Phase 1). Batch only non-critical calls like generate_objections + generate_competing_hypotheses during DIVERSIFY if latency is an issue. Prefer clarity over batching initially.5
Summary
The skeleton is excellent — FSM routing, gate phasing, structural triggers, and state management are rigorously implemented and faithful to the charter. The LLM boundary and mock are production-ready seams. Highest-priority fixes before real LLM wiring: (1) proper std::optional structural fields in StateCompression (v2.5 handoff safety), (2) add semantic distinctness check for Trigger 1 via LLM. Minor: flesh out remaining TODOs (JSON serialization, full Mock impls). This is a strong foundation for a charter-enforcing research assistant.
