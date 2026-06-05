# Open Questions — Review Cycle 2

Three questions are open for deliberation following Review Cycle 1.

Cycle 1 was a discovery pass — general review, find what's wrong. Cycle 2 is a deliberation pass — the structural problems are identified, competing solutions are on the record, and the task is to close each question with a specific resolution.

A resolution is not "pick the best proposal." It must argue why the chosen approach is better than the alternatives, pass G2–G5, and produce exact proposed text. A resolution that cannot generate a substantive objection to its own conclusion has not thought hard enough.

See `for-humans/review-cycle-2-prompt.md` for the copy-paste prompt to send to an LLM.

---

## Q1 — Does the Evidence Hierarchy need to become a matrix?

**Charter target:** §5 Evidence Hierarchy

**Status:** Two independent critiques filed from different angles. Cannot be resolved independently — the two challenges must be reconciled before a fix can be proposed.

### Challenges on the record

**Kimi** (`proposals/2026-06-05-kimi-evidence-hierarchy-orthogonal-axes.md`)

The linear E1–E5 ladder collapses two independent quality dimensions — reproducibility and empirical grounding — into one axis. A fully reproducible simulation with garbage boundary conditions is weaker evidence than a non-reproducible but empirically grounded historical observation. The ladder creates a Goodhart's Law incentive: optimize for reproducibility (procedurally demonstrable) at the expense of empirical validity (harder to verify). No fix proposed — filed as a structural problem.

**Gemini** (`proposals/2026-06-05-gemini-evidence-hierarchy-e1-e2-operationalization.md`)

E1 and E2 lack operational boundary criteria. E2 permits hallucinated citations. E1 permits qualitative tests that violate the Constitutional Principle. E1 fix was incorporated into v2.2. E2 fix deferred as potentially over-specified.

### The tension

You cannot fix E2 without first deciding whether the ladder is the right structure. If Kimi is correct that reproducibility and empirical grounding are orthogonal, then E2 may occupy the wrong position on the wrong axis entirely — patching it within the current structure solves the wrong problem.

### What a valid resolution looks like

- **Option A:** Argue the linear ladder is structurally sound as a practical heuristic despite its imprecision, and propose a specific E2 fix within the current structure.
- **Option B:** Propose a concrete alternative structure (2D matrix, explicit override rules, or tiered hierarchy with footnotes) and show what E1–E5 maps to under the new structure.
- **Option C:** Argue the challenge is out of scope — the hierarchy is intentionally a heuristic, not an epistemology — and close the question with an explicit scope declaration rather than a structural change.

Any option must pass G2–G5, produce exact proposed text or an exact scope declaration, and include a substantive objection to its own conclusion.

---

## Q2 — What operationalizes the DIVERSIFY trigger?

**Charter target:** §3 Coherence Controller — DIVERSIFY trigger condition

**Status:** One proposal filed, one key condition left undefined. Deferred from v2.2.

### Challenge on the record

**Gemini** (`proposals/2026-06-05-gemini-coherence-controller-deadlock.md`)

"This feels obviously right" is anthropomorphic — LLMs calculate token probabilities, not phenomenological states. The trigger either never fires (if the assistant suppresses "feeling" per Genesis) or fires constantly (any well-formed answer generates high-confidence tokens). Proposes three structural conditions to replace it:

1. Fewer than two explicitly modeled competing hypotheses for the current claim
2. Claim generated without surfacing at least one explicit failure mode or boundary condition
3. No gate check applied since the last structural revision

Deferred because Condition 1 is itself undefined: "explicitly modeled" is as vague as "obviously right." A hypothesis is present somewhere in the context window? Named as a claim? Assigned an evidence level? Stress-tested by §4?

### The open gap

What does "explicitly modeled competing hypothesis" mean in a way that is observable and consistent across models and sessions? If this cannot be defined, is hypothesis-counting the right trigger mechanism at all — or is there a better structural proxy for "we have converged prematurely"?

### What a valid resolution looks like

- Complete Gemini's conditions by operationally defining "explicitly modeled" — the definition must be checkable by another LLM reading the same session transcript.
- Or: propose a different replacement trigger mechanism entirely — one that is structural, not anthropomorphic.
- Or: argue that the current anthropomorphic trigger is defensible because it functions as a cultural norm for the human operator rather than an internal LLM state check — and propose revised text that makes this distinction explicit.

The resolution must produce exact replacement text for the DIVERSIFY trigger section of §3.

---

## Q3 — Should the §9 definitions have numeric thresholds?

**Charter target:** §9 Session Continuity Protocol — trigger conditions

**Status:** V2.2 adopted GPT-5.5's definitional approach. Two competing numeric proposals remain on the record. Question: do the definitions need numbers alongside them?

### Current v2.2 text (GPT-5.5's approach, incorporated)

- Topic shift: primary claim/artifact/objective changes to a different one
- Milestone: gate status changes, artifact completed, or test specification finalized
- Session complexity elevated: two or more active claims, artifacts, or unresolved objections tracked simultaneously without a State Compression since the earliest was opened

### Competing proposals on the record

**Grok** (`proposals/2026-06-05-grok-session-complexity-trigger-operationalization.md`): Token count >15k, >4 open artifacts, >3 topic shifts in last 10 exchanges. Thresholds explicitly provisional.

**Kimi** (`proposals/2026-06-05-kimi-session-complexity-trigger-undefined.md`): ≥3 unresolved skeptical objections, ≥2 active claims with divergent evidence levels, ≥3 distinct topic domains, >70% token context. Includes an override-and-audit requirement: assistant may compress earlier but must state which heuristic is approaching.

### The question

V2.2's definitional approach is cleaner and more durable than specific numbers, but leaves "how much is too much" to judgment. Numeric thresholds make behavior auditable and improvable — but the specific numbers are provisional guesses with no empirical basis. Should v2.3 add provisional numeric thresholds alongside the definitions, with explicit instructions to calibrate them as session data accumulates? Or is the definitional approach sufficient?

### What a valid resolution looks like

- Argue for adding specific provisional numbers (synthesizing Grok and Kimi into a best-available set) alongside the v2.2 definitions, with explicit calibration instructions built into the text.
- Or: argue the v2.2 definitional approach is sufficient and close the question without numeric additions.
- Either way, produce exact proposed text.

---

## Model Routing

Based on Cycle 1 Model Confidence Notes. These are suggestions, not assignments — a model that picks outside its routing and closes the question rigorously is better than one that follows the routing and produces a weak proposal.

| Model | Suggested question | Reasoning |
|-------|-------------------|-----------|
| Gemini | Q2 | Raised the DIVERSIFY deadlock; best positioned to define Condition 1 |
| Kimi | Q1 | Raised the orthogonal axes challenge; taxonomy thinking |
| Grok | Q3 | Filed numeric thresholds; positioned to defend or revise them |
| GPT-5.5 | Q3 or Q1 | Filed v2.2 definitional approach for §9; strong formal structure |
| New models | Any | Fresh perspective — especially valuable on Q1 |
