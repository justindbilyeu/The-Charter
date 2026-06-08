# C++ Skeleton Review Prompt

Send this to Gemini, Kimi, Grok, GPT, or any model that can fetch URLs.
For models that cannot fetch, paste the header files directly.

---

## The Prompt

```
You are reviewing a C++ skeleton of the Charter Machine — a software
implementation of the Research Assistant Charter (v2.7).

Fetch and read all source files from:
https://github.com/justindbilyeu/The-Charter/tree/main/charter-cpp

Or fetch the headers directly (raw URLs):
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/charter-cpp/include/charter/types.h
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/charter-cpp/include/charter/fsm.h
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/charter-cpp/include/charter/gates.h
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/charter-cpp/include/charter/coherence_controller.h
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/charter-cpp/include/charter/llm_interface.h
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/charter-cpp/include/charter/session_continuity.h
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/charter-cpp/main.cpp

Also fetch the charter the code implements:
https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/CHARTER.md

Read both before answering. This is a code review with charter fidelity
as the standard — the code must correctly enforce what the charter says.

---

REVIEW QUESTIONS

Answer each one specifically. Vague impressions are not useful.
If you find a bug, state the file, function, and the exact failure mode.

1. FSM ROUTING CORRECTNESS
   The charter defines strict routing rules (v2.3/v2.4):
   - DIVERSIFY → STRUCTURING only (not GATE_CHECK)
   - G1/G2 failure → RESTART immediately; G3–G5 not evaluated
   - G3/G5 failure → DIVERSIFY; G4 failure → RESTART
   - CONVERGE requires: all gates pass + no open objections +
     at least one prior DIVERSIFY or RESTART in session
   Does CharterFSM correctly enforce all of these? Identify any
   transition that the code permits but the charter forbids, or
   forbids but the charter permits.

2. LLM INTERFACE BOUNDARY
   Some gate evaluations are mechanical (G1: count thresholds, G4:
   check immutability). Others require semantic judgment (G2: is the
   scope bounded?, G3: are key terms operationally defined?, G5: is
   mechanism status declared?).
   Is the mechanical/semantic split in gates.h correct? Are any
   mechanical checks incorrectly delegated to the LLM? Are any
   semantic checks incorrectly hardcoded as mechanical?

3. STATE COMPRESSION VALIDITY
   v2.5 of the charter distinguishes structural fields (required —
   missing → invalid handoff, operator must act) from orientational
   fields (missing → declare and proceed). Structural fields are:
   gate_status, objection_register, constraint_health, adversarial_anchor.
   StateCompression::missing_structural_fields() in types.cpp uses a
   heuristic (charter_version empty = missing). The code notes this
   is a TODO. What is the correct fix? Should structural fields be
   wrapped in std::optional? Is there a better approach?

4. DIVERSIFY TRIGGER 1 — STRUCTURAL VS SEMANTIC CHECK
   Structural DIVERSIFY Trigger 1 (v2.6): fewer than 2 competing
   hypotheses documented with distinct ID, evidence level (E1–E5),
   and a discriminating test (named IV + named DV).
   check_hypothesis_under_specification() in coherence_controller.cpp
   checks structure only (fields non-empty). The charter's intent is
   that the hypotheses are "genuinely distinct" — different predictions.
   Is the structural check sufficient? Or does Trigger 1 require LLM
   semantic verification of distinct predictions? If so, where should
   the LLM call be added?

5. ANTHROPIC API INTEGRATION
   ILLMInterface is a pure abstract C++ class. The next phase is
   implementing it against the Anthropic API (claude-sonnet-4-6).
   Sketch what AnthropicLLMInterface should look like:
   - What HTTP client / SDK would you use?
   - What prompt structure should evaluate_g2(), evaluate_g3(),
     evaluate_g5() use? How do you parse the structured response
     back into a GateEvaluation?
   - What rate limiting / retry strategy is appropriate?
   - Should each gate call be a separate API call, or batched?

---

SUBMISSION FORMAT

File your response as:
2026-06-08-[yourmodel]-cpp-skeleton-review.md

Use this structure:

# C++ Skeleton Review — [model name]

## Q1 — FSM Routing
[findings — file, function, exact failure mode if any]

## Q2 — LLM Interface Boundary
[findings]

## Q3 — State Compression Validity
[findings + recommended fix]

## Q4 — DIVERSIFY Trigger 1
[findings + recommended fix if semantic check needed]

## Q5 — Anthropic API Integration
[design sketch]

## Summary
3–5 sentences: what is correct, what needs work, what is the
highest-priority fix before wiring a real LLM backend.
```
