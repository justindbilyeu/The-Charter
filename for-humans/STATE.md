# Charter Machine — State Compression

**Charter version:** v2.7
**Last updated:** 2026-06-08
**Updated by:** ClaudeCode — end of G2 prompt contract session

---

## Gate Status — Open Artifacts

*No artifacts currently open.*

---

## Objection Register

*No open objections.*

---

## Constraint Health

- **Gates evaluated and passed:** N/A — no active artifact
- **Open objection count:** 0
- **Consecutive CONVERGE count:** 0
- **Watchdog fired this session:** no
- **Drift assessment:** NOT_ASSESSED

---

## Adversarial Anchor

- Watchdog fired: no
- Drift assessment: NOT_ASSESSED

---

## Active Claims and Evidence Levels

*None.*

---

## Decisions Made This Session

| Decision | Reasoning | Session |
|----------|-----------|---------|
| K1 closed — DiversifyExitToken capability token | Unanimous across four reviewers. Private-constructor token; only CoherenceController can mint. `declare_diversify_complete()` and flag removed entirely. | 2026-06-08 |
| hypotheses_are_genuinely_distinct() added to ILLMInterface | Trigger 1 semantic gap enforced at type-system level. Mock returns true. Real implementation required before AnthropicLLMInterface declared complete. | 2026-06-08 |
| G5 prompt contract finalized + DV anchoring fix applied | Outcome-removal test as load-bearing criterion. Anchor to declared op-def, not inferred DV from claim text. v2.6 → v2.7 corrected. | 2026-06-08 |
| G3 prompt contract finalized | SYNONYM/PARTIAL/MISSING taxonomy. Reproducibility test. G3 + G5 may be dispatched concurrently (both Phase 2 → DIVERSIFY). Verbatim term label passthrough in build_g3_user_message(). | 2026-06-08 |
| G2 prompt contract finalized | Three-dimension falsifiability framework (population, condition, outcome scope). Falsifiability test as load-bearing criterion. Test spec in user message for D3 only — explicitly fenced from rescuing D1/D2. Failure route RESTART (not DIVERSIFY — see Fix 1 history). | 2026-06-08 |
| for-humans/STATE.md added to repo | Canonical state in git; Claude Project file is convenience copy for chat thread continuity. | 2026-06-08 |
| Q4 proposal filed — trigger-differentiated exit | Claude Chat filed `proposals/2026-06-08-claude-chat-q4-diversify-trigger-differentiated-exit.md`. Tier 1 (ST1, Watchdog, G5 failure) → a+b+c; Tier 2 (ST2, ST3, G3 failure) → b+c only. G3/G5 tier assignment is the contestable claim — pending multi-model review. Must resolve before AnthropicLLMInterface changes check_diversify_complete() contract. | 2026-06-08 |

---

## Next Step

**Single, specific, actionable:**

Q4 must be resolved (multi-model review of `proposals/2026-06-08-claude-chat-q4-diversify-trigger-differentiated-exit.md`)
before `AnthropicLLMInterface` is implemented — Q4 changes the `check_diversify_complete()` contract
(must receive triggering condition as input) and `DiversifyExitToken` should record which tier governed the exit.

Once Q4 is closed: implement `AnthropicLLMInterface` — wire G2, G3, G5 against the finalized prompt
contracts. Separate API calls per gate; G3 + G5 may be dispatched concurrently after G2 passes.
Integration-test all three against the cold-exposure artifact from `main.cpp` before any real research use.

Gate-specific implementation notes:
- G2: `FailureRoute::RESTART` — do not copy from G3/G5 template
- G3: pass `operational_definitions[i].term` verbatim (no normalization) to preserve label-matching for regression variant 5
- G5: DV anchoring fix already in system prompt — confirm it holds in real API responses

---

## Assumptions Modified This Session

- `DiversifyCompletionResult` struct removed — replaced by `DiversifyExitToken.unmet_criteria()`
- `declare_diversify_complete()` removed from `CharterFSM`

---

## Skeptical Residue

**Open:**
- All three prompt contracts (G2, G3, G5) untested against real API — regression suites documented, not yet run
- Trigger 1 semantic check (hypotheses_are_genuinely_distinct) still structural-only — mock returns true
- AnthropicLLMInterface not yet implemented

**Highest-risk integration test cases:**
- G5: Artifact C (effect description as mechanism) — primary silent-pass failure mode
- G3: Artifact C (definitions present, both synonyms) — presence ≠ completeness
- G2: Artifact C (numbers present, population and condition unbounded) — numbers ≠ bounded scope
- G2: regression variant 5 (criteria-sounding language that doesn't actually bound)
- G3: regression variant 5 (label mismatch between claim text and op-def keys)

---

## How to Use This File

**End of session:** Update all sections that changed. Commit to repo. Optionally
re-upload to Claude Project files for chat thread continuity.

**Start of new thread:** Paste the full content of this file at the top of the
new conversation. Claude will execute the five-step deserialization procedure
(charter §9) before doing anything else:
1. Declare charter version
2. Confirm gate status
3. Load open objections
4. State next step
5. Load Constraint Health and Adversarial Anchor

**On /compress:** Replace this file's content with the new State Compression.
Do not append — replace. Old state is in git history if needed.
