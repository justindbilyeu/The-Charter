# Changelog

All notable changes to The Charter are documented here.

---

## v2.3

**Review Cycle 2 — Machine spec gap analysis (Claude, Gemini)**

Two changes incorporated from 3 proposals decided. Primary finding: §3 Coherence Controller had two independent structural issues — an undefined monitoring input and an FSM routing trap.

Changes:
- **§3 Constraint health replaced** — "Constraint health" was the Coherence Controller's decision input but was never defined as a measurable quantity. Replaced with three observable monitoring conditions: (1) gates evaluated and passed for the current artifact, (2) whether any raised objections lack a test or untestability declaration, (3) convergence trajectory — whether recent transitions include a DIVERSIFY or RESTART, or the session has been converging without interruption. CONVERGE and DIVERSIFY criteria updated to reference these conditions explicitly. (Claude — G-08 Option B)
- **§3 DIVERSIFY routing fixed** — DIVERSIFY → GATE_CHECK shortcut removed. On completion, DIVERSIFY must route to STRUCTURING so the artifact is recompiled with updated objections before any gate re-evaluation. Routing DIVERSIFY directly back to GATE_CHECK re-evaluated a stale artifact, producing a deterministic execution loop. (Gemini — FSM routing loophole)

Rejected:
- G-08 Option A (Grok — numeric composite score H): Option B chosen; numeric weights require empirical calibration not yet available.
- G-06 (Claude — Objection Register as typed structure): Objections remain prose; formal schema adds overhead without sufficient benefit at current maturity.

Deferred to v2.4: DIVERSIFY trigger full operationalization (Q2); §9 numeric thresholds (Q3); §5 evidence hierarchy structure (Q1).

---

## v2.2

**Review Cycle 1 — Multi-model adversarial review (Sage/ChatGPT, Grok, Gemini, GPT-5.5)**

Seven changes incorporated from 10 proposals filed. Primary finding: §4 Productive Skepticism Protocol had the highest structural stress — flagged by three models from three distinct angles.

Changes:
- **G5 rewritten** — Gates on declared mechanism *status*, not known mechanism. Requires distinguishing mechanism from its supporting evidence. When mechanism is unknown, artifact must self-identify as phenomenological/predictive/exploratory and propose a test discriminating ≥2 mechanistic explanations. "Mechanism unknown is not a gate failure. Mechanism status undeclared is."
- **§3 CONVERGE** — Explicit criteria added: all gates pass, all objections tested and documented, no untested objection with a viable scoped test remains. CONVERGE is exhausted scrutiny, not consensus.
- **§4 Calibration Rule** — "Substantive objection" operationalized with four criteria (specific, testable, non-redundant, gate-tied). Documented exit added for genuinely exhausted scrutiny.
- **§4 Skepticism Termination Rule** — New rule: scrutiny is satisfied when all objections are stated, assigned tests or declared untestable, and no new untested objection can be generated within scope.
- **§5 E1** — Test proposal now requires named independent variable, named dependent variable, and numeric threshold. Qualitative proposals do not satisfy E1.
- **§9 Trigger conditions** — "Topic shift," "milestone," and "rising session complexity" given explicit operational definitions.
- **Constitutional Principle** — Scope note added: gate language governs empirical inquiry; formal and interpretive claims map the spirit to domain-appropriate validation methods.

Deferred to v2.3: §3 DIVERSIFY trigger operationalization; §5 E2 citation standards.

See `proposals/REVIEW_CYCLE_1_SUMMARY.md` for full pattern analysis.

---

## v2.1

**Added: §9 — Session Continuity Protocol**

Long sessions accumulate context debt. This version treats session state as a first-class research artifact — produced, maintained, and transferred with the same rigor as any other output.

Changes:
- New §9 defining State Compression format and trigger conditions
- `/compress` operator shortcut
- State Compression added to Communication Hooks as a third hook alongside Handshake and Handoff

Rationale: session limits are an operational constraint, not a research variable. Managing them belongs in the charter.

---

## v2.0

Initial release as a general-purpose research assistant charter. Generalized from v1.0 — removed RG²-specific persona (SAGE), domain-specific file format (CLAIM.md/PREREG.yaml bundle), and physics-oriented modeling language. Added G5 Mechanism gate (not present in v1.0). Retained core institutions and constitutional principle.

Established the eight core institutions:


1. The Structuring Contract
2. Hard Gates (G1–G5)
3. Coherence Controller (CONVERGE / DIVERSIFY / RESTART)
4. Productive Skepticism Protocol
5. Evidence Hierarchy (E1–E5)
6. Modeling Protocol
7. Prototype Protocol
8. Integrity Rules

Established the Constitutional Principle, three Output Modes, and Handshake/Handoff communication hooks.

---

## v1.0

**Original charter — SAGE / RG² (Resonance Geometry × Resonance Engine)**

Domain-specific charter written for the RG² research project. Written by and for SAGE (the project's AI research partner persona). Not a general-purpose framework — scoped to a single project with physics-oriented modeling language and a specific artifact format.

Distinctive features not carried forward into v2.0:

- **SAGE persona** — explicit co-founder–grade role, RG²-specific identity
- **Compilation bundle format** — four required files: `CLAIM.md`, `OPERATIONALIZE.md`, `PREREG.yaml`, `NULLS.md`
- **Physics-oriented Modeling Protocol** — symmetries, conserved quantities, seed manifests
- **Compass metaphor in Genesis** — "We use it as a compass" (reintroduced formally in v3.0 draft Compass Protocol)
- **RG² Signature** — 𝒮 : (Intent × Coherence) → Awareness / 𝒮⊙ : (Intent × Coherence) → Deployment
- **Constitutional Principle** — "No Claim Without Nulls. No Nulls Without Numbers. No Numbers Without a Run." (generalized to "No Claims Without Tests" in v2.0)
- **No G5** — mechanism gate not present; v2.0 added it

Four hard gates (G1–G4). No Session Continuity Protocol (added in v2.1). No G5 Mechanism gate (added in v2.0).
