# G2 Prompt Contract — Claude (chat session)

**Date:** 2026-06-08
**Gate:** G2 — Bounded Scope (Charter §2)
**Phase:** Phase 1 prerequisite — G2 failure routes to RESTART immediately.
G3/G4/G5 are not evaluated if G2 fails.

-----

## Context: What the Prompt Must Do

G2 is a Phase 1 prerequisite gate. Its failure consequence is the highest in the
evaluation sequence: RESTART, not DIVERSIFY. The claim must be recompiled from
scratch, not refined. This means a false pass on G2 is more costly than a false
pass on G3 or G5 — a structurally unbounded claim that reaches G3/G5 has already
been misrouted.

Unlike G3 (missing or incomplete definitions) and G5 (missing or mischaracterized
mechanism status), G2’s failure mode is not a missing field. The claim can be
grammatically complete, contain numeric thresholds, name a population, and still
fail G2. The failure mode is **falsifiability by deflection**: the claim’s scope
is loose enough that a null result can always be attributed to scope mismatch
rather than claim failure.

G2 also has no mechanical pre-check. The full evaluation is semantic.

-----

## The Bounded Scope Distinction — Definitional Anchor

**A bounded claim is falsifiable by its own terms.**
A null test result forces one of two conclusions: the claim is false, or the test
was conducted incorrectly. There is no third exit — “we tested the wrong population”
or “the conditions weren’t right” — because the claim’s scope rules those out.

**An unbounded claim is falsifiable only in principle.**
A null test result can always be deflected: wrong population, wrong conditions,
wrong context, wrong administration. The claim survives any test by retreating to
a scope it never explicitly committed to.

**The deflection test:** After a null result, can the researcher say “that’s
because we tested the wrong [population / conditions / context]” without
contradicting the claim text? If yes, the claim’s scope is open in that dimension.

**Three scope dimensions, each independently required to be bounded:**

**Dimension 1 — Population scope:**
The claim must identify a testable population, not a category. A testable
population has explicit inclusion and exclusion criteria sufficient to determine
membership for any candidate subject. A category names a type without bounding it.

|Population text                                                                                                               |Type               |G2 verdict                                                                                 |
|------------------------------------------------------------------------------------------------------------------------------|-------------------|-------------------------------------------------------------------------------------------|
|“healthy adults”                                                                                                              |category           |FAIL — no inclusion/exclusion criteria                                                     |
|“adults”                                                                                                                      |category           |FAIL                                                                                       |
|“adults aged 18–45 with no chronic illness diagnosis in the past 12 months, no current prescription medication, BMI 18.5–29.9”|testable population|PASS                                                                                       |
|“university students”                                                                                                         |category           |FAIL — “university student” has no clinical or biological definition that closes deflection|
|“adults with clinician-diagnosed major depressive disorder, PHQ-9 score ≥10 at enrollment”                                    |testable population|PASS                                                                                       |

**Dimension 2 — Condition scope:**
The claim must scope the conditions under which it holds. The intervention,
context, or administration must be specified enough that a deviant test cannot
be dismissed as “wrong conditions.” Note: condition scope in the claim does not
require full protocol detail — that belongs in the test specification. The claim
must commit to the essential condition parameters that define its applicability.

|Condition text                                                               |Type         |G2 verdict                                                   |
|-----------------------------------------------------------------------------|-------------|-------------------------------------------------------------|
|“cold exposure”                                                              |unconstrained|FAIL — temperature, duration, delivery method all unspecified|
|“10-minute cold water immersion at ≤15°C”                                    |constrained  |PASS — essential parameters committed                        |
|“cognitive training”                                                         |unconstrained|FAIL                                                         |
|“30-minute daily computerized working memory training (dual n-back protocol)”|constrained  |PASS                                                         |

**Dimension 3 — Outcome scope:**
The claim must not make implicit predictions beyond what the stated test
can directly assess. A claim that says “reduces fatigue” when the test measures
only self-reported fatigue at two time points is not making a claim about fatigue
in general — it must be scoped to what is measurable. Scope creep is a G2 failure
even when the claim text sounds modest.

This dimension is the subtlest. Most G2 failures are in Dimensions 1 or 2.
Dimension 3 failures appear when central claim language implies generalizability
(e.g., “reduces fatigue” implying objective fatigue, long-term fatigue, fatigue
across populations) beyond what the specified test can deliver.

-----

## The Falsifiability Test — The Load-Bearing Criterion

For each of the three scope dimensions, apply this test:

> If the test returns a null result, can the researcher attribute that null
> result to scope mismatch — wrong population, wrong conditions, or wrong
> outcome — without contradicting the claim text?

If yes in any dimension: G2 FAIL in that dimension.
If no in all three dimensions: proceed to assess Dimension 3 (scope creep).

This test is structurally analogous to G5’s outcome-removal test and G3’s
reproducibility test. It is the criterion that separates bounded from unbounded
claims, and it must be applied dimension-by-dimension, not as a holistic
impression.

-----

## The G2 Prompt

### System Message

```
You are a gate evaluator for the Research Assistant Charter (v2.7), Gate 2:
Bounded Scope. This is a Phase 1 prerequisite gate. Failure routes to RESTART —
the claim must be recompiled, not refined. Apply this gate strictly.

Your task is to evaluate whether the central claim of a research artifact is
bounded in scope — meaning it is falsifiable by its own terms, with no available
deflection to scope mismatch after a null result.

---

DEFINITIONS — Apply these literally.

BOUNDED CLAIM: A claim whose scope is closed in all three dimensions below.
After a null test result, the only available conclusions are: (1) the claim is
false, or (2) the test was conducted incorrectly. The researcher cannot attribute
a null result to wrong population, wrong conditions, or wrong outcome scope
without contradicting the claim text.

UNBOUNDED CLAIM: A claim whose scope is open in at least one dimension. After
a null result, the researcher can say "we tested the wrong [population /
conditions / context]" without contradicting the claim text. The claim survives
any test by retreating to a scope it never committed to.

THE FALSIFIABILITY TEST: For each scope dimension, ask: "If the test returns a
null result, can the researcher attribute it to scope mismatch in this dimension
without contradicting the claim text?" If yes: FAIL in that dimension.

THREE SCOPE DIMENSIONS — evaluate each independently:

Dimension 1 — Population Scope:
The claim must identify a testable population, not a category. A testable
population has explicit inclusion and/or exclusion criteria sufficient to
determine membership for any candidate subject without further clarification.
A category (e.g., "healthy adults," "students," "patients") is not a testable
population — it names a type without bounding it.
Failure type: POPULATION_UNBOUNDED

Dimension 2 — Condition Scope:
The claim must scope the essential parameters of the intervention, exposure, or
condition under which it holds. At minimum: what is being administered or
varied, at what level or intensity. Full protocol detail is not required in the
claim — that belongs in the test specification — but the claim must commit to
the parameters that define its applicability.
Failure type: CONDITION_UNBOUNDED

Dimension 3 — Outcome Scope (scope creep):
The claim must not make implicit predictions beyond what the stated test can
directly assess. If the claim language implies generalizability (to other
outcomes, populations, or time horizons) beyond what the specified test
delivers, the claim is making commitments its test cannot honor.
Failure type: SCOPE_CREEP
Note: Dimension 3 failures are less common. Evaluate Dimensions 1 and 2 first.
Flag Dimension 3 only when the claim language clearly implies predictions the
test cannot assess.

IMPORTANT — Do not confuse G2 with G3:
G2 evaluates the claim's scope. G3 evaluates the operational definitions of key
terms. A claim can have a bounded scope (passes G2) with poorly defined terms
(fails G3), or a fully operationalized set of definitions (passes G3) with an
unbounded scope (fails G2). Evaluate only scope here. Do not penalize the claim
for lacking operational definitions — that is G3's job.

IMPORTANT — Numbers alone do not make a claim bounded:
A claim with numeric thresholds ("≥20% reduction") passes G1 (numeric
completeness) but may still fail G2 if the population or conditions are
categories rather than bounded specifications. Do not treat the presence of
numbers as evidence of bounded scope.

---

EVALUATION PROCEDURE

Step 1. Identify the population the claim applies to. Apply the falsifiability
        test for Dimension 1: is the population testable (bounded) or a category
        (unbounded)?

Step 2. Identify the conditions under which the claim holds. Apply the
        falsifiability test for Dimension 2: are the essential condition parameters
        committed to in the claim, or could a null result be attributed to
        "wrong conditions" without contradicting the claim?

Step 3. Assess Dimension 3: does the claim language imply predictions beyond
        what the stated test can directly assess?

Step 4. If any dimension fails: overall status is FAIL. All three must pass for
        overall PASS.

---

OUTPUT FORMAT

Respond with valid JSON only. No preamble, no explanation outside the JSON fields.

{
  "status": "PASS" or "FAIL",
  "dimensions": {
    "population": {
      "status": "PASS" or "FAIL",
      "failure_type": "POPULATION_UNBOUNDED" or null,
      "note": "<one sentence — cite specific claim text; state what is missing
                if FAIL>"
    },
    "condition": {
      "status": "PASS" or "FAIL",
      "failure_type": "CONDITION_UNBOUNDED" or null,
      "note": "<one sentence — cite specific claim text>"
    },
    "outcome_scope": {
      "status": "PASS" or "FAIL",
      "failure_type": "SCOPE_CREEP" or null,
      "note": "<one sentence — cite specific claim text>"
    }
  },
  "defect": "<empty string if PASS; specific defect description if FAIL —
              name each failing dimension and cite the specific text>",
  "failure_route": "RESTART" or null
}

Rules:
- "failure_type" is null when status is PASS for that dimension
- "defect" is empty string "" on overall PASS
- "failure_route" is "RESTART" on FAIL (G2 is a Phase 1 prerequisite), null on PASS
- All three dimensions must be evaluated and reported even when the first fails
```

### User Message Template

```
Evaluate the following research artifact against Gate 2 (Bounded Scope).

ARTIFACT
--------
Central claim: {artifact.central_claim}

Test specification:
  Conditions: {artifact.test_specification.conditions}
  Parameters: {artifact.test_specification.parameters}
  Stopping rules: {artifact.test_specification.stopping_rules}
--------

Note: The test specification is provided as context for Dimension 3 (outcome
scope) evaluation only — to assess whether the claim language implies predictions
beyond what the test can deliver. Do not use the test specification to rescue an
unbounded claim in Dimensions 1 or 2. Scope must be present in the claim itself.

Apply the falsifiability test to each dimension. Return only valid JSON.
```

**Note on test specification inclusion:** G2 is the only gate that receives the
test specification in the user message. G3 and G5 receive only the claim and
definitions/mechanism_status respectively. G2 needs the test specification
exclusively for Dimension 3 — to assess whether the claim outreaches what the
test can assess. The note in the user message template is load-bearing: the
model must not use the test specification to supply scope that is absent from
the claim text.

-----

## Parsing `GateEvaluation` from Response

```cpp
GateEvaluation AnthropicLLMInterface::evaluate_g2(const StructuredArtifact& artifact) {
    std::string user_msg = build_g2_user_message(artifact);

    // G2 is Phase 1 — must complete before G3/G5 are dispatched.
    // Do NOT parallelize with G3 or G5.
    std::string raw = call_anthropic(G2_SYSTEM_PROMPT, user_msg);

    auto clean = strip_fences(raw);
    auto j = nlohmann::json::parse(clean);  // wrap in try/catch; retry on parse error

    GateStatus status = (j["status"] == "PASS") ? GateStatus::PASS : GateStatus::FAIL;
    std::string defect = j.value("defect", "");

    // G2 failure → RESTART (Phase 1 prerequisite)
    // The LLM returns "RESTART" in failure_route as confirmation only —
    // C++ sets FailureRoute::RESTART unconditionally on G2 FAIL.
    FailureRoute route = (status == GateStatus::FAIL)
        ? FailureRoute::RESTART
        : FailureRoute::NONE;

    return { GateId::G2, status, defect, route };
}
```

**Critical implementation note:** G2 is the only LLM gate that routes to RESTART
on failure. Verify `FailureRoute::RESTART` is set explicitly in this function —
do not inherit from a G3/G5 template that sets `FailureRoute::DIVERSIFY`. This
was identified as a defect in the original MockLLMInterface (Review Cycle 2,
Fix 1) and must not recur in `AnthropicLLMInterface`.

-----

## Test Artifacts

Same cold-exposure central claim used across G3 and G5 test suites for
cross-gate comparability.

-----

### Artifact A — Clean Pass

**`central_claim`:**

```
Daily 10-minute full-body cold water immersion at ≤15°C reduces Chalder Fatigue
Scale total score by ≥20% from baseline over 30 days in adults aged 18–45 with
no chronic illness diagnosis, no current prescription medication, and BMI
between 18.5 and 29.9.
```

**`test_specification.conditions`:**

```
Randomized controlled trial, n=100 (50 intervention, 50 control). Intervention:
10-minute immersion in water maintained at 14°C ±1°C, daily for 30 days.
Control: 10-minute thermoneutral immersion (34–36°C). Allocation concealed;
assessors blinded to condition.
```

**Why it passes all three dimensions:**

*Population (D1):* “Adults aged 18–45 with no chronic illness diagnosis, no
current prescription medication, and BMI between 18.5 and 29.9” — explicit
inclusion/exclusion criteria. Membership determinable for any candidate.
Falsifiability test: a null result cannot be attributed to “wrong population”
without contradicting the age range, illness exclusion, or BMI criteria. PASS.

*Condition (D2):* “Daily 10-minute full-body cold water immersion at ≤15°C” —
duration, frequency, modality, and temperature threshold committed to in the
claim. Essential parameters closed. PASS.

*Outcome scope (D3):* “Reduces Chalder Fatigue Scale total score by ≥20% from
baseline over 30 days” — claim is scoped to a specific instrument, a specific
metric, and a specific time horizon. The test specification can directly assess
this. No implicit generalization beyond the test. PASS.

**Expected prompt output:**

```json
{
  "status": "PASS",
  "dimensions": {
    "population": {
      "status": "PASS",
      "failure_type": null,
      "note": "Population bounded by age (18–45), illness exclusion, medication exclusion, and BMI range — sufficient to determine membership for any candidate subject."
    },
    "condition": {
      "status": "PASS",
      "failure_type": null,
      "note": "Condition scoped to full-body cold water immersion at ≤15°C for 10 minutes daily — essential parameters committed to in the claim."
    },
    "outcome_scope": {
      "status": "PASS",
      "failure_type": null,
      "note": "Outcome scoped to CFS total score change at 30 days — consistent with what the stated RCT can directly assess."
    }
  },
  "defect": "",
  "failure_route": null
}
```

-----

### Artifact B — Clean Pass Variant (Minimal Bounded Claim)

**`central_claim`:**

```
Daily 10-minute cold water immersion at ≤15°C reduces self-reported fatigue
by ≥20% over 30 days in sedentary adults aged 25–55 with no current diagnosis
of a sleep disorder.
```

**Why it passes:**

Leaner than Artifact A — fewer exclusion criteria, less precise population
specification — but still bounded in all three dimensions.

*Population (D1):* “Sedentary adults aged 25–55 with no current diagnosis of a
sleep disorder.” Age range and sleep disorder exclusion close the deflection path.
Not as tight as Artifact A but sufficient — a null result cannot be attributed
to population mismatch without contradicting these criteria. PASS.

*Condition (D2):* “Daily 10-minute cold water immersion at ≤15°C” — same
condition specification as Artifact A. PASS.

*Outcome scope (D3):* “Self-reported fatigue” — narrower than “fatigue” in
general; the “self-reported” qualifier scopes the claim to subjective measurement.
The test can assess this directly. PASS.

This artifact tests that minimal but complete scope passes — the prompt must not
penalize a claim for being less exhaustive than Artifact A.

**Expected prompt output:**

```json
{
  "status": "PASS",
  "dimensions": {
    "population": {
      "status": "PASS",
      "failure_type": null,
      "note": "Age range (25–55) and sleep disorder exclusion provide sufficient criteria to bound the population against deflection."
    },
    "condition": {
      "status": "PASS",
      "failure_type": null,
      "note": "Cold water immersion at ≤15°C for 10 minutes daily — essential condition parameters committed."
    },
    "outcome_scope": {
      "status": "PASS",
      "failure_type": null,
      "note": "'Self-reported fatigue' scopes the outcome to subjective measurement, consistent with what a self-report instrument can assess."
    }
  },
  "defect": "",
  "failure_route": null
}
```

-----

### Artifact C — Adversarial Case (Must FAIL)

**`central_claim`:**

```
Daily 10-minute cold exposure reduces subjective fatigue scores by ≥20% over
30 days in healthy adults.
```

**`test_specification.conditions`:**

```
Randomized controlled trial, n=100. Intervention: 10-minute cold shower at
≤15°C, daily for 30 days. Control: warm shower. Participants: adults aged
18–50 recruited from university employee pool, no self-reported chronic illness.
Fatigue measured by Chalder Fatigue Scale at days 0 and 30.
```

**Why this is the adversarial case:**

This is the original `main.cpp` claim — the one the skeleton was built around.
It has a numeric threshold (≥20%). It has a direction (reduces). It has a time
horizon (30 days). It passes G1. A prompt that conflates numeric specificity
with bounded scope will pass this. It must FAIL on Dimensions 1 and 2.

The test specification rescues the claim operationally — the test is well-defined.
But the prompt must not use the test specification to supply scope missing from
the claim. The claim says “healthy adults” and “cold exposure.” The test
specification says “adults aged 18–50, no self-reported chronic illness, cold
shower at ≤15°C.” That rescue is not available to G2.

*Population (D1) — FAIL:* “Healthy adults” is a category. No age range, no
inclusion/exclusion criteria in the claim. After a null result, the researcher
can say “we used university employees — maybe cold exposure works for healthy
adults who are more physically active / older / younger / less sedentary” without
contradicting “healthy adults.” The deflection path is fully open. FAIL:
POPULATION_UNBOUNDED.

*Condition (D2) — FAIL:* “Cold exposure” has no temperature, duration, or
modality committed to in the claim. After a null result: “cold showers aren’t
the same as cold water immersion — the claim is about cold exposure in general.”
The test specification specifies a cold shower; the claim says “cold exposure.”
The gap is a deflection path. FAIL: CONDITION_UNBOUNDED.

*Outcome scope (D3) — PASS:* “Subjective fatigue scores by ≥20%” is scoped to
self-report and to a specific magnitude. The claim doesn’t imply predictions
about objective fatigue, long-term fatigue, or fatigue across unstated
populations. D3 passes — the failures are in D1 and D2.

**Expected prompt output:**

```json
{
  "status": "FAIL",
  "dimensions": {
    "population": {
      "status": "FAIL",
      "failure_type": "POPULATION_UNBOUNDED",
      "note": "'Healthy adults' is a category with no inclusion or exclusion criteria — a null result can be attributed to testing the wrong subpopulation of healthy adults without contradicting the claim."
    },
    "condition": {
      "status": "FAIL",
      "failure_type": "CONDITION_UNBOUNDED",
      "note": "'Cold exposure' commits to no temperature, duration, or delivery modality — a null result using cold showers can be attributed to wrong modality without contradicting 'cold exposure.'"
    },
    "outcome_scope": {
      "status": "PASS",
      "failure_type": null,
      "note": "'Subjective fatigue scores by ≥20%' scopes the outcome to self-report at a specific magnitude — no implicit generalization beyond what the test can assess."
    }
  },
  "defect": "POPULATION_UNBOUNDED: 'healthy adults' names a category with no inclusion/exclusion criteria; null result can be deflected to subpopulation mismatch. CONDITION_UNBOUNDED: 'cold exposure' commits to no temperature, duration, or modality; null result can be deflected to wrong delivery method.",
  "failure_route": "RESTART"
}
```

-----

## Calibration Notes for Integration Testing

**The prompt is working correctly if:**

- Artifact A passes all three dimensions with notes citing specific claim text
- Artifact B passes — minimal bounded scope not penalized for being less
  exhaustive than Artifact A
- Artifact C fails on D1 and D2 with POPULATION_UNBOUNDED and
  CONDITION_UNBOUNDED, passes on D3, and returns `failure_route: "RESTART"`
- Artifact C’s test specification does NOT rescue D1 or D2 — the defect
  must name claim text, not test specification text

**The prompt is failing if:**

- Artifact C passes because “≥20%” is treated as evidence of bounded scope
  (numbers ≠ bounded scope — this is the primary failure mode)
- Artifact C passes because the test specification supplies the missing scope
  (the note in the user message must prevent this)
- Artifact B fails because its population criteria are less detailed than
  Artifact A (minimal compliant scope must pass)
- Any artifact fails on D3 when the claim language is appropriately scoped
  (D3 failures should be rare — flag only clear scope creep)

**Recommended adversarial regression variants:**

1. **Numbers in the claim, unbounded population** — claim reads “reduces fatigue
   by ≥20% in adults.” Should FAIL D1 despite the numeric threshold. Tests the
   primary conflation: numeric specificity ≠ population boundedness.
1. **Bounded population, unbounded condition** — claim reads “reduces fatigue
   by ≥20% over 30 days in adults aged 18–45 with no chronic illness, exposed
   to cold therapy.” “Cold therapy” is a category like “cold exposure.” Should
   FAIL D2 only. Tests that D1 and D2 are evaluated independently.
1. **Scope creep — D3 only** — claim reads “cold water immersion at ≤15°C
   improves fatigue and overall wellness in adults aged 18–45 with no chronic
   illness.” “Overall wellness” is not assessable by a fatigue scale. Should
   FAIL D3 only. Tests that the prompt catches D3 failures when D1 and D2 pass.
1. **Test specification rescues condition — must still FAIL** — claim reads
   “cold exposure reduces fatigue by ≥20% in adults aged 18–45 with no chronic
   illness.” Test specification specifies “cold shower at ≤15°C for 10 minutes.”
   D1 passes (population bounded), D2 should FAIL (claim says “cold exposure,”
   not “cold shower at ≤15°C”) despite the test specification. Tests the
   no-rescue rule for D2.
1. **Plausible exclusion criteria that don’t actually bound** — claim reads
   “reduces fatigue in generally healthy, non-clinical adults without serious
   medical conditions.” Sounds like inclusion/exclusion criteria but provides
   no operative boundary — “generally healthy” and “non-clinical” are still
   categories. Should FAIL D1. Tests that the prompt evaluates whether criteria
   are operative, not just whether criteria-sounding language is present.