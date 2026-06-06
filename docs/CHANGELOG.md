# Changelog

All notable changes to The Charter are documented here.

---

## v2.7

**Review Cycle 2 concluded — Q1 closed (Claude Chat)**

One proposal incorporated. Closes the last unresolved open question from Review Cycle 1.

Changes:
- **§5 E2 revised** — "explicitly cited and sourced" replaced with a two-part requirement: (a) verifiable citation — the source is independently locatable by a reviewer without access to the original researcher's context; (b) corroboration — when E2 knowledge is used as a foundational assumption in a structured artifact, at least two independent verifiable sources are required. A single verifiable source satisfies E2 for background orientation only. Foundational/orientational distinction defined: foundational = removal would require revising the artifact's central claim, operational definitions, or success criteria; orientational = provides context but artifact stands without it; determined at compile time. (Claude Chat — Q1 resolution, Option A)

Deferred:
- Q5 (new): operational definition of "empirically grounded" as a binary status — Kimi's structural concern that reproducibility and empirical grounding are orthogonal axes remains on the record. Deferred pending a definition of "grounded" that is checkable in a session transcript.

Closes: Q1 (evidence hierarchy structure — open since v2.2).

Review Cycle 2 status: Q1 closed (v2.7), Q2 closed (v2.6), Q3 rejected (v2.4), Q4 open (trigger-differentiated DIVERSIFY exit), Q5 open (grounded definition).

---

## v2.6

**Review Cycle 2 continued — Q2 closed (Gemini)**

One proposal incorporated. Closes the last unresolved structural trigger gap in §3.

Changes:
- **§3 Structural DIVERSIFY Triggers** — new named subsection added parallel to the Convergence Watchdog. DIVERSIFY is mandatory if ANY of three structural conditions are met: (1) Hypothesis Under-Specification — fewer than two competing hypotheses documented with distinct identifier, explicit evidence level, and discriminating test proposal naming at least one IV and DV; (2) Asymmetric Risk Assessment — active claim advanced without objection register update or Failure Mode Probe entry detailing failure conditions; (3) Gate Omission — new claims, metrics, or parameter ranges incorporated into the active artifact since the last formal gate evaluation. When any condition is met, the assistant must state the violated condition and execute DIVERSIFY — CONVERGE is not available. Anthropomorphic "This feels obviously right" preserved as operator-facing cultural framing. (Gemini — Q2 resolution)

Note on Condition 3: the charter explicitly scopes it to artifact-level changes — "incorporated into the active artifact," not "introduced into the dialogue." Conversational clarifications and examples do not trigger this condition.

Closes: Q2 (DIVERSIFY trigger operationalization — open since v2.2).

---

## v2.5

**Review Cycle 2 continued — Structural gap closures (Kimi)**

Three proposals incorporated. Primary work: closing two §3 Coherence Controller gaps and one §9 Deserialization contradiction.

Changes:
- **§3 "applicable gates" removed** — "all applicable gates pass" (CONVERGE) and "one or more applicable gates have not been evaluated" (DIVERSIFY) replaced with "all gates" / "one or more gates." Runtime applicability exemptions removed; domain accommodation via Constitutional Principle scope note, not in-session declarations. (Kimi — applicable gates bypass)
- **§3 DIVERSIFY completion condition added** — "On completion" replaced with explicit three-part exit criterion: (a) new competing hypothesis explicitly modeled with differing prediction, (b) new substantive objection raised and logged per §4 Calibration Rule, (c) artifact revised or written justification for no revision. Exit is now protocol-determined, not agent-discretionary. (Kimi — DIVERSIFY exit criterion)
- **§9 Degraded handoff replaced** — "proceed but declare" contradiction resolved. State Compression fields classified as structural (gate status, objection register, Constraint Health, Adversarial Anchor — required, missing → invalid handoff requiring operator action) and orientational (active claims summary, decisions log, next step, assumption log — missing → declare and proceed). (Kimi — degraded handoff contradiction)

Deferred:
- Trigger-differentiated DIVERSIFY exit conditions — whether low-stakes DIVERSIFY triggers (undocumented objection, unevaluated gate) require all three completion criteria or only (b)+(c). Open Q4.
- Q1 (evidence hierarchy structure), Q2 (DIVERSIFY trigger operationalization) — remain open.

---

## v2.4

**Review Cycle 2 continued — Gap closures (Claude, Gemini, Grok, Sage, DeepSeek)**

Seven proposals incorporated. Primary work: closing machine spec gaps G-01, G-03, G-04, G-07 and integrating the Grok health fields into State Compression.

Changes:
- **§2 Gate evaluation order** — Two-phase protocol. G1+G2 are prerequisites evaluated first; failure → RESTART immediately without evaluating G3–G5. G3 and G5 failures → DIVERSIFY. G4 failure → RESTART. (Claude — G-04)
- **§3 Convergence Watchdog** — After 3 consecutive CONVERGEs, a Watchdog Report is required before the next CONVERGE decision. Report must include: the three most recent claims and objections against each; at least one new competing hypothesis not active in the last two evaluations and the smallest discriminating test; a drift vs. exhausted scrutiny assessment. If the assessment concludes drift suspected, DIVERSIFY is mandatory regardless of standard conditions. Grok+Sage Mandatory Adversarial Reset integrated into the Watchdog structure. (Claude — G-03; Grok+Sage)
- **Communication Hooks — Handshake** — Charter version declaration, session context (fresh/loaded), and objection register initialization added as required Handshake fields. (Claude — G-01)
- **§9 State Compression fields** — Two new required fields: Constraint Health state (three monitoring condition values at compression time) and Adversarial Anchor status (whether the Watchdog fired and what it concluded). (Grok — health integration)
- **§9 Deserialization Procedure** — Five-step procedure required before new work when loading a State Compression: declare charter version, confirm gate status, load open objections, state next step, load Constraint Health and Anchor status. Degraded handoffs (missing fields) must be declared before proceeding. (Claude — G-07)

Rejected:
- Kimi G4 escape hatch — G4 absolute prohibition maintained. Any escape hatch becomes the primary exploit route.
- Grok G-08 Option A (numeric metric) — already rejected in v2.3.
- Claude G-06 (Objection Register schema) — prose sufficient at current maturity.
- Kimi §9 numeric thresholds — v2.2 definitional approach sufficient; numbers deferred to when calibration data is available.

Deferred:
- Grok+Sage Rival Sufficiency Requirement — accepted the Adversarial Reset component; Rival Sufficiency criteria need operationalization of "explains ≥50% of observations" before acceptance.
- Q1 (evidence hierarchy structure), Q2 (DIVERSIFY trigger operationalization), Q3 (§9 numeric thresholds) — remain open.

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
