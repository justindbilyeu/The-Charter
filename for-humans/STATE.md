# Charter Machine — State Compression

**Charter version:** v2.7
**Last updated:** 2026-06-08
**Updated by:** ClaudeCode — end of G3 prompt contract session

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
| K1 closed — capability token pattern (DiversifyExitToken) | Unanimous across four reviewers (Claude Chat, Grok, Kimi, Gemini). Flag pattern was honor-system one level up; private-constructor token makes fabrication a compile error. | 2026-06-08 skeleton review |
| G3 prompt contract finalized | No mechanical pre-check; LLM carries full load. SYNONYM/PARTIAL/MISSING distinction in output schema. | 2026-06-08 |
| G5 DV anchoring fix applied | System message now anchors outcome-removal test to declared operational definition, not inferred DV from central claim text. | 2026-06-08 |
| for-humans/STATE.md added to repo | Canonical state copy in git; Project file is convenience copy. | 2026-06-08 |
| G3 and G5 may be dispatched concurrently | Both Phase 2 validators routing to DIVERSIFY on fail — safe to run as parallel std::async calls after G2 passes; collect all futures before HardGates::route(). | 2026-06-08 |
| Trigger 1 hypotheses_are_genuinely_distinct() wired to ILLMInterface | Method added to interface now (not deferred to comment); MockLLMInterface returns true. Real implementation required before AnthropicLLMInterface declared complete. | 2026-06-08 |

---

## Next Step

**Single, specific, actionable:**

Write G2 prompt contract (bounded scope gate) in same format as G3/G5. File as
`2026-06-08-claude-chat-g2-prompt-contract.md`. Adversarial case: claim that
sounds specific but whose test specification cannot actually bound it — scope
is asserted in the claim text but not enforced by any named constraint.

---

## Assumptions Modified This Session

- `DiversifyCompletionResult` struct removed from `CoherenceController` — replaced by `DiversifyExitToken.unmet_criteria()`
- `declare_diversify_complete()` removed from `CharterFSM` — replaced by token-consuming `to_structuring()` overload

---

## Skeptical Residue

**Open questions:**
- G3 label-matching robustness (regression variant 5) not yet tested — dependent on LLM integration; labels in central claim vs. operational_definitions keys must be matched semantically, not by exact string
- G2 prompt contract not yet written
- Trigger 1 semantic check still structural-only in skeleton (hypotheses_are_genuinely_distinct() mock returns true)
- AnthropicLLMInterface not yet implemented — all gate evaluation uses MockLLMInterface

**What would change our confidence:**
- G5 DV anchoring fix not yet integration-tested — risk that model anchors on claim text anyway despite instruction
- G3 and G5 concurrent dispatch not yet validated — std::async approach is sound but race conditions in shared state (if any) need verification

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
