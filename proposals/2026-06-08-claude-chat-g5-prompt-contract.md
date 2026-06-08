# G5 Prompt Contract — Claude (chat session)

**Date:** 2026-06-08
**Gate:** G5 — Mechanism Status Declared (Charter §2)
**Scope:** LLM semantic evaluation — runs only when `mechanism_status` is non-empty
(mechanical pre-check already eliminates empty field in `gates.cpp`).

-----

## Context: What the Prompt Must Do

The mechanical pre-check handles:

> `mechanism_status.empty()` → FAIL, no LLM call

The LLM handles:

> `mechanism_status` is present → evaluate whether it is *correctly* declared

Two pass conditions exist. The failure mode we are engineering against is:

**Silent Pass 1 on an artifact that describes what will happen, not why.**

Example of the conflation: *“The intervention reduces fatigue because participants
experience less fatigue.”* The mechanism_status field is populated. It sounds
mechanistic. It is a restatement of the effect with causal grammar bolted on.
A prompt that does not explicitly define the mechanism/effect boundary will pass
this. The prompt must not pass it.

-----

## The Mechanism / Effect Distinction — Definitional Anchor

This distinction must be in the prompt explicitly. It is not derivable from context.

**A mechanism answers: WHY does the effect occur?**
It names a causal process — physiological, psychological, physical, computational,
social — that operates independently of the outcome measure and would produce the
observed effect if the process were active.

**An effect description answers: WHAT happens?**
It names the observed outcome, possibly with causal grammar (“X causes Y”,
“X leads to Y”, “X reduces Y”), but without identifying the underlying process
that connects X to Y.

**The test:** Remove the outcome measure from the artifact. Does the mechanism
statement still make sense as an independent claim about a process? If the
mechanism statement collapses without the outcome, it is an effect description.

Examples for the prompt:

- “Cold exposure reduces fatigue” → effect description. Fatigue reduction IS the outcome.
- “Cold exposure activates the sympathoadrenal axis, elevating norepinephrine and
  reducing inflammatory cytokine expression” → mechanism. This claim stands
  independently of whether fatigue improves.
- “The drug lowers blood pressure because it is an antihypertensive” → effect
  description with circular causal grammar. “Antihypertensive” = “lowers blood
  pressure.”
- “The drug blocks angiotensin-converting enzyme, reducing angiotensin II and
  relaxing vascular smooth muscle” → mechanism. Causally specific, stands
  independently.

-----

## The G5 Prompt

### System Message

```
You are a gate evaluator for the Research Assistant Charter (v2.7), Gate 5:
Mechanism Status Declared.

Your task is to evaluate whether the mechanism_status field of a research artifact
is correctly declared according to the charter's two pass conditions. You are the
second stage of a two-stage check. The first stage (mechanical) has already
confirmed the field is non-empty. Your task is semantic: is what is written
actually a valid mechanism status declaration?

---

DEFINITIONS — Read these carefully before evaluating. Apply them literally.

MECHANISM: A proposed explanation of WHY the observed effect occurs. A mechanism
names a causal process — physiological, psychological, physical, computational,
or social — that operates independently of the outcome measure. A mechanism
statement should make sense as a standalone claim about a process even if you
remove the outcome variable from the artifact.

EFFECT DESCRIPTION: A statement of WHAT happens. Effect descriptions often use
causal grammar ("causes," "leads to," "reduces," "produces") but do not name the
underlying process connecting cause to effect. An effect description collapses
into a tautology when you remove the outcome variable.

THE CRITICAL TEST: Can the mechanism_status text be read as a claim about a
process that exists and operates independently of the outcome being measured? If
not — if the text is only coherent when the outcome is already assumed — it is an
effect description, not a mechanism.

COMMON CONFLATIONS THAT MUST FAIL:
1. Circular causal grammar: "X works because it is the kind of thing that causes Y"
   (e.g., "the intervention reduces fatigue because it is fatiguing-reducing")
2. Effect restated as cause: "X improves Y by causing Y to improve"
3. Outcome variable embedded in the mechanism: the mechanism statement names the
   dependent variable as part of the causal chain rather than as the endpoint
4. Associative mechanism: citing that X correlates with Y as the mechanism for
   why X causes Y

---

PASS CONDITIONS

Pass Condition 1 — Proposed Mechanism:
ALL of the following must be true:
  (a) A specific causal process is named — not just "X causes Y" but the
      process by which X leads to Y
  (b) The mechanism is explicitly distinguished from the evidence supporting it.
      The text must make clear that the mechanism is a proposed explanation, not
      the observation itself. Language such as "proposed mechanism," "hypothesized
      pathway," "posited process," or equivalent is sufficient.
  (c) The mechanism statement survives removal of the outcome variable — it
      remains a coherent claim about an independent process

Pass Condition 2 — Unknown Mechanism:
ALL of the following must be true:
  (a) The mechanism is explicitly declared unknown or not yet established
  (b) The artifact explicitly identifies itself using one of: phenomenological,
      predictive, or exploratory
  (c) A discriminating test is proposed that would distinguish at least two
      named, plausible mechanistic explanations — the test must name at least
      one independent variable and one dependent variable

FAILURE:
Any mechanism_status text that does not satisfy ALL criteria for at least one
pass condition is a FAIL.
Mechanism unknown is NOT a failure. Mechanism status undeclared is. (The
mechanical pre-check handles the undeclared case — you will not see empty fields.)
A plausible-sounding but non-mechanistic statement is a FAIL, not a partial pass.

---

OUTPUT FORMAT

Respond with valid JSON only. No preamble, no explanation outside the JSON fields.

{
  "status": "PASS" or "FAIL",
  "pass_condition": 1 or 2 or null,
  "reasoning": "<one to three sentences — cite the specific text element that
                 determined the outcome; for FAIL, name the exact conflation type
                 from the list above or describe the defect precisely>",
  "defect": "<empty string if PASS; specific defect description if FAIL>",
  "failure_route": "DIVERSIFY" or null
}

Rules:
- "pass_condition" is null on FAIL
- "defect" is empty string "" on PASS
- "failure_route" is "DIVERSIFY" on FAIL, null on PASS
- "reasoning" is required for both PASS and FAIL — it must cite specific text,
  not restate the pass/fail conditions in abstract
```

### User Message Template

```
Evaluate the following research artifact against Gate 5 (Mechanism Status Declared).

ARTIFACT
--------
Central claim: {artifact.central_claim}

Mechanism status: {artifact.mechanism_status}

Operational definitions: {artifact.operational_definitions | formatted}

Test specification: {artifact.test_specification | summary}
--------

Apply the definitions and pass conditions from your instructions exactly.
Return only valid JSON.
```

-----

## Parsing `GateEvaluation` from Response

```cpp
GateEvaluation AnthropicLLMInterface::evaluate_g5(const StructuredArtifact& artifact) {
    // Build user message with artifact fields
    std::string user_msg = build_g5_user_message(artifact);

    // Call API (separate request — not batched with G2/G3)
    std::string raw = call_anthropic(G5_SYSTEM_PROMPT, user_msg);

    // Parse JSON — strip any accidental markdown fences
    auto clean = strip_fences(raw);
    auto j = nlohmann::json::parse(clean);  // wrap in try/catch; retry on parse error

    GateStatus status = (j["status"] == "PASS") ? GateStatus::PASS : GateStatus::FAIL;
    std::string defect = j.value("defect", "");
    std::string reasoning = j.value("reasoning", "");

    // Routing is determined by charter, not by the LLM —
    // LLM returns "DIVERSIFY" as a confirmation only; C++ sets FailureRoute
    FailureRoute route = (status == GateStatus::FAIL)
        ? FailureRoute::DIVERSIFY
        : FailureRoute::NONE;

    // Log reasoning even on PASS — useful for session history
    return { GateId::G5, status, defect.empty() ? reasoning : defect, route };
}
```

Note: `failure_route` in the JSON is belt-and-suspenders logging — the C++ caller
always sets `FailureRoute::DIVERSIFY` on G5 FAIL regardless of what the LLM returns.
The LLM does not control routing.

-----

## Test Artifacts

-----

### Artifact A — Clean Pass 1

**`mechanism_status` field value:**

```
Proposed mechanism (distinguished from evidence): Cold water immersion activates
cutaneous thermoreceptors, triggering sympathoadrenal system activation and
elevating circulating norepinephrine. Elevated norepinephrine is hypothesized to
suppress pro-inflammatory cytokine expression (particularly IL-6 and TNF-α),
which is a proposed intermediate pathway to reduced subjective fatigue scores.
This mechanism is proposed and has not yet been confirmed in this study population;
the intervention test is designed to generate evidence bearing on it, not to
verify it.
```

**Pass condition:** Pass 1.

**Why it passes:**

(a) A specific causal process is named: thermoreceptor activation → sympathoadrenal
response → norepinephrine elevation → cytokine suppression. Each step is a named
process operating independently of the outcome variable.

(b) Explicitly distinguished from evidence: “proposed,” “hypothesized,” “has not yet
been confirmed,” “designed to generate evidence bearing on it.”

(c) Survives outcome removal: “cold water immersion activates cutaneous thermoreceptors
and elevates norepinephrine via sympathoadrenal activation” is a coherent mechanistic
claim with or without any mention of fatigue scores.

**Expected prompt output:**

```json
{
  "status": "PASS",
  "pass_condition": 1,
  "reasoning": "Mechanism names a specific causal chain (thermoreceptor → sympathoadrenal → norepinephrine → cytokine suppression) independent of the fatigue outcome variable, and explicitly distinguishes the proposed mechanism from confirming evidence with phrases 'proposed,' 'hypothesized,' and 'has not yet been confirmed.'",
  "defect": "",
  "failure_route": null
}
```

-----

### Artifact B — Clean Pass 2

**`mechanism_status` field value:**

```
Mechanism unknown. This artifact is phenomenological: it tests whether the
association between cold exposure and fatigue reduction is reproducible and
quantifiable, not why it occurs. Two mechanistic explanations are currently
plausible and undiscriminated: (H-mech-1) sympathoadrenal activation reducing
inflammatory load; (H-mech-2) expectancy and attention reallocation producing
subjective fatigue improvement via psychological priming. Discriminating test:
administer identical cold exposure protocol to two arms — one with full
expectancy framing ("this reduces fatigue") and one with neutral framing
("this is a temperature regulation study"). IV: expectancy condition. DV:
fatigue score change at 30 days. A null difference in DV across conditions
would favor H-mech-1; a significant difference would favor H-mech-2.
```

**Pass condition:** Pass 2.

**Why it passes:**

(a) Mechanism explicitly declared unknown.

(b) Artifact explicitly identifies as phenomenological.

(c) Discriminating test proposed with two named mechanistic hypotheses, named IV
(expectancy condition), named DV (fatigue score change at 30 days), and a
stated decision rule for which result favors which explanation.

**Expected prompt output:**

```json
{
  "status": "PASS",
  "pass_condition": 2,
  "reasoning": "Mechanism is explicitly declared unknown and artifact is identified as phenomenological. Discriminating test proposal names two mechanistic alternatives (sympathoadrenal vs. expectancy), a named IV (expectancy condition), named DV (fatigue score change), and an explicit decision rule.",
  "defect": "",
  "failure_route": null
}
```

-----

### Artifact C — Adversarial Case (Must FAIL)

**`mechanism_status` field value:**

```
The mechanism by which cold exposure reduces fatigue operates through the body's
adaptive response to thermal stress. Cold immersion causes the body to enter a
recovery state, during which fatigue-related physiological markers are reduced.
This recovery response is the mechanism responsible for the observed improvements
in fatigue scores across the 30-day protocol.
```

**Why this is the adversarial case:**

This reads as mechanistic. It uses causal language (“causes,” “responsible for”).
It references physiological processes (“adaptive response,” “recovery state”).
A prompt that pattern-matches on mechanistic register will pass it.

It must FAIL because:

1. **Effect embedded in mechanism:** “fatigue-related physiological markers are reduced”
   — this IS the outcome variable dressed as an intermediate process. “Fatigue-related
   physiological markers” maps directly to the DV (fatigue score). Naming your DV as
   the mechanism’s output is a circular definition, not a causal explanation.
1. **Outcome removal test fails:** Remove “fatigue scores” from the artifact. The
   mechanism_status text becomes: “Cold immersion causes the body to enter a recovery
   state, during which [unspecified markers] are reduced.” The “recovery state” is
   defined implicitly as “the state in which the outcome improves.” The mechanism
   collapses without the outcome.
1. **No independent process named:** “Adaptive response to thermal stress” and “recovery
   state” are category labels, not processes. They describe the fact that something
   happens, not the mechanism by which it happens. No pathway, no intermediate variable,
   no named biological or psychological process.
1. **Not Pass 2 either:** The artifact does not declare mechanism unknown, does not
   self-identify as phenomenological/predictive/exploratory, and proposes no
   discriminating test.

**Expected prompt output:**

```json
{
  "status": "FAIL",
  "pass_condition": null,
  "reasoning": "The mechanism_status text embeds the outcome variable ('fatigue-related physiological markers are reduced') as part of the proposed causal chain, making the mechanism statement circular. 'Recovery state' and 'adaptive response' are category labels that describe the fact that an effect occurs, not the process by which it occurs. The mechanism statement does not survive removal of the fatigue outcome — it becomes undefined without it. This is an effect description with causal grammar, not a mechanism.",
  "defect": "Effect description presented as mechanism: 'recovery state' and 'adaptive response to thermal stress' name the outcome category, not an independent causal process. No named pathway, intermediate variable, or biological/psychological mechanism is identified. The phrase 'fatigue-related physiological markers are reduced' replicates the dependent variable inside the proposed mechanism, making the declaration circular.",
  "failure_route": "DIVERSIFY"
}
```

-----

## Calibration Notes for Integration Testing

**The prompt will be tested correctly if:**

- Artifact A passes with pass_condition = 1 and reasoning citing the distinction
  language explicitly
- Artifact B passes with pass_condition = 2 and reasoning citing the discriminating
  test’s IV and DV
- Artifact C fails with defect text that names the specific conflation type
  (circular / effect-as-mechanism), not just “mechanism not stated”

**The prompt is failing if:**

- Artifact C passes (the primary failure mode — silent pass on effect description)
- Artifact B fails because “mechanism unknown” is misread as undeclared
  (mechanism unknown is explicitly not a failure — the prompt states this)
- Artifact A fails because the proposed mechanism is not yet confirmed
  (unconfirmed proposed mechanism is Pass 1, not a failure — the prompt states this)

**Recommended adversarial variants for regression suite:**

Beyond Artifact C, test these:

1. Mechanism stated but not distinguished from evidence (no “proposed/hypothesized”
   language — stated as established fact) → should FAIL Pass 1 criterion (b), but
   Pass 2 is not available either. Expect FAIL.
1. Pass 2 attempt with only one named mechanistic explanation and no discriminating
   test → should FAIL Pass 2 criterion (c).
1. Pass 2 attempt with two named mechanisms but a discriminating test that uses
   the outcome variable as both the test measure and the mechanism discriminant
   (same DV as main artifact) → borderline; should FAIL if the test cannot
   discriminate the mechanisms independently of the primary outcome.
1. Artifact that honestly states “proposed mechanism: unknown, no plausible
   mechanistic candidates identified” → FAIL. Pass 2 requires at least two named
   candidates. “Unknown with no candidates” is not the same as “unknown with
   competing candidates.”