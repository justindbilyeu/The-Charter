# G3 Prompt Contract — Claude (chat session)

**Date:** 2026-06-08
**Gate:** G3 — Operational Definitions (Charter §2)
**Scope:** Full LLM semantic evaluation — no mechanical pre-check in gates.cpp.
The LLM carries the entire G3 load, including structurally missing definitions.

-----

## Context: What the Prompt Must Do

Unlike G5, G3 has no mechanical pre-check. `llm_->evaluate_g3(artifact)` is
called directly once G1 and G2 pass. The prompt must therefore handle three
distinct failure modes, not one:

1. **Missing definition** — a key term in the central claim has no entry in
   `operational_definitions` at all
1. **Synonym definition** — a definition exists but rephrases the term rather
   than mapping it to a measurable quantity or procedure (the primary adversarial
   case)
1. **Partial definition** — a definition names a valid instrument or procedure
   but omits required components (metric and/or measurement window)

The charter requirement (§1 Structuring Contract) is:

> Operational definitions: observables + metrics + measurement windows

All three components are required. A definition that has two of three is
incomplete and must FAIL.

-----

## The Operationalization Distinction — Definitional Anchor

This is the G3 analog of the mechanism/effect distinction in G5. It must be
in the prompt explicitly.

**An operational definition answers: HOW is this term measured?**
It names an observable quantity, the instrument or procedure used to measure it,
and the time window in which measurement occurs. An operational definition is
complete when a researcher who has never seen the artifact could reproduce the
measurement from the definition alone.

**A synonym (non-operational definition) answers: WHAT does this term mean?**
It restates the concept in different words, possibly more precisely, but without
specifying how to observe or measure it. A synonym does not enable measurement.

**A partial definition** names a measurement instrument or observable but omits
the metric (what quantity the instrument produces) or the measurement window
(when or how often measurement occurs).

**The reproducibility test:** Could a researcher who has never seen this artifact
reproduce the measurement from this definition alone — knowing what to measure,
how to measure it, and when? If no, the definition is incomplete.

**Examples:**

|Term          |Definition                                                                                                                           |Type       |G3 verdict                                       |
|--------------|-------------------------------------------------------------------------------------------------------------------------------------|-----------|-------------------------------------------------|
|fatigue       |“the state of physical or mental exhaustion”                                                                                         |synonym    |FAIL — no observable, no instrument, no window   |
|fatigue       |“subjective fatigue”                                                                                                                 |synonym    |FAIL — adjective added, still no observable      |
|fatigue       |“measured by the Chalder Fatigue Scale”                                                                                              |partial    |FAIL — instrument named, metric and window absent|
|fatigue       |“Chalder Fatigue Scale (CFS) total score”                                                                                            |partial    |FAIL — instrument + metric, window absent        |
|fatigue       |“Chalder Fatigue Scale (CFS) total score, measured at days 0, 15, and 30”                                                            |operational|PASS                                             |
|cognitive load|“the mental effort required by the task”                                                                                             |synonym    |FAIL                                             |
|cognitive load|“NASA-TLX score”                                                                                                                     |partial    |FAIL — window absent                             |
|cognitive load|“NASA-TLX overall workload score, collected immediately after each task session”                                                     |operational|PASS                                             |
|blood pressure|“systolic blood pressure (mmHg), measured by automated sphygmomanometer after 5 minutes seated rest, recorded at baseline and week 4”|operational|PASS                                             |

-----

## Key Terms — Extraction Rule

The prompt must evaluate every key term in the central claim. The model must
identify key terms itself from the central claim text — it cannot rely on the
researcher to have flagged them. A key term is any term that:

- Names a variable being manipulated (independent variable)
- Names a variable being measured (dependent variable)
- Names a population or condition that scopes the claim
- Is domain-specific and not universally defined (e.g., “fatigue,” “stress,”
  “engagement” require definition; “adults,” “days,” “percentage” do not)

If a key term appears in the central claim and has no corresponding entry in
`operational_definitions`, that is a G3 failure regardless of how well the
other terms are defined.

-----

## The G3 Prompt

### System Message

```
You are a gate evaluator for the Research Assistant Charter (v2.7), Gate 3:
Operational Definitions.

Your task is to evaluate whether every key term in a research artifact's central
claim has a complete operational definition. You receive the central claim and the
artifact's operational definitions. You must identify key terms yourself from the
central claim — do not assume the researcher has flagged all of them.

---

DEFINITIONS — Apply these literally.

OPERATIONAL DEFINITION: A complete operational definition contains all three of
the following components:
  (1) Observable / metric — a specific, measurable quantity (a score, a count,
      a concentration, a rating, a time) produced by applying the instrument or
      procedure to the subject
  (2) Instrument or procedure — the named method used to produce the measurement
      (a validated scale, an assay, a sensor, a structured observation protocol)
  (3) Measurement window — when or how often the measurement is taken (at
      baseline, at day 30, immediately after each session, weekly for 8 weeks)

A definition missing any one of these three components is INCOMPLETE and fails G3.

SYNONYM: A restatement of the term in different words. Synonyms do not enable
measurement. A definition is a synonym if a researcher could not determine from
it alone what to measure, how to measure it, or when.

PARTIAL DEFINITION: A definition that names an instrument or observable but omits
the metric or the measurement window. Partial definitions fail G3.

THE REPRODUCIBILITY TEST: Could a researcher who has never seen this artifact
reproduce the exact measurement from this definition alone — knowing what quantity
to record, what method to use, and when to apply it? If any of these three
questions cannot be answered from the definition text, the definition is incomplete.

KEY TERMS: Identify key terms from the central claim. A key term is any term that:
  - Names the independent variable (what is being manipulated or varied)
  - Names the dependent variable (what is being measured as the outcome)
  - Names a domain-specific construct that is not universally defined
    (e.g., "fatigue," "engagement," "recovery," "performance," "stress")
  Do not require definitions for universally understood terms (e.g., "adults,"
  "days," "percentage," "participants").

MISSING DEFINITION: If a key term has no entry in operational_definitions at all,
that is a G3 failure. The absence of a definition is not the same as an incomplete
definition — name both failure types distinctly in your output.

---

EVALUATION PROCEDURE

Step 1. Extract all key terms from the central claim.
Step 2. For each key term, locate its entry in operational_definitions.
        If no entry exists: mark as MISSING.
        If an entry exists: apply the reproducibility test.
          - All three components present → COMPLETE
          - Instrument/procedure present but metric or window absent → PARTIAL
          - No instrument/procedure, no observable quantity → SYNONYM
Step 3. If any key term is MISSING, PARTIAL, or SYNONYM: overall result is FAIL.
        All three components present for all key terms: overall result is PASS.

---

OUTPUT FORMAT

Respond with valid JSON only. No preamble, no explanation outside the JSON fields.

{
  "status": "PASS" or "FAIL",
  "key_terms_evaluated": [
    {
      "term": "<term from central claim>",
      "definition_status": "COMPLETE" or "PARTIAL" or "SYNONYM" or "MISSING",
      "missing_components": ["metric", "instrument", "window"],
      "note": "<one sentence — cite specific text or absence>"
    }
  ],
  "defect": "<empty string if PASS; specific defect description if FAIL —
              name each failing term and its failure type>",
  "failure_route": "DIVERSIFY" or null
}

Rules:
- "missing_components" is an empty array [] when definition_status is COMPLETE
- "missing_components" lists only the absent components when PARTIAL
- "missing_components" lists all three when SYNONYM or MISSING
- "defect" is empty string "" on PASS
- "failure_route" is "DIVERSIFY" on FAIL, null on PASS
- List ALL key terms evaluated, not just failing ones — the full evaluation
  record is required for session history
```

### User Message Template

```
Evaluate the following research artifact against Gate 3 (Operational Definitions).

ARTIFACT
--------
Central claim: {artifact.central_claim}

Operational definitions:
{artifact.operational_definitions | formatted as:
  - {term}: {metric} | {measurement_window}
  (one entry per line; "none" if operational_definitions is empty)}
--------

Apply the definitions, key term extraction rules, and evaluation procedure from
your instructions exactly. Return only valid JSON.
```

-----

## Parsing `GateEvaluation` from Response

```cpp
GateEvaluation AnthropicLLMInterface::evaluate_g3(const StructuredArtifact& artifact) {
    std::string user_msg = build_g3_user_message(artifact);

    // Separate API call — not batched with G2 (phase protocol); may run
    // in parallel with G5 (both are Phase 2, both route to DIVERSIFY on fail)
    std::string raw = call_anthropic(G3_SYSTEM_PROMPT, user_msg);

    auto clean = strip_fences(raw);
    auto j = nlohmann::json::parse(clean);  // wrap in try/catch; retry on parse error

    GateStatus status = (j["status"] == "PASS") ? GateStatus::PASS : GateStatus::FAIL;
    std::string defect = j.value("defect", "");

    // Routing is determined by charter, not by LLM.
    // G3 failure → DIVERSIFY (Phase 2 validator)
    FailureRoute route = (status == GateStatus::FAIL)
        ? FailureRoute::DIVERSIFY
        : FailureRoute::NONE;

    // Log full key_terms_evaluated array in session history even on PASS
    // — useful for identifying near-misses and regression tracking
    return { GateId::G3, status, defect, route };
}
```

Note on parallelization: G3 and G5 are both Phase 2 validators that route to
DIVERSIFY on failure. They can be dispatched as concurrent `std::async` calls
after G2 passes. G4 is mechanical and can run at any point after thresholds are
set. The Phase 2 results must all be collected before `HardGates::route()` is
called — collect futures before routing, do not route on first failure.

-----

## Test Artifacts

The central claim used across all three artifacts is the same cold-exposure claim
from `main.cpp`, so results are directly comparable to the G5 test suite:

> “Daily 10-minute cold exposure reduces subjective fatigue scores by ≥20%
> over 30 days in healthy adults.”

Key terms requiring definition: **cold exposure** (IV), **fatigue scores** (DV).
“Daily,” “10-minute,” “30 days,” “healthy adults,” “20%” do not require
operational definitions.

-----

### Artifact A — Clean Pass

**`operational_definitions` field:**

```
- cold_exposure: 10-minute full-body immersion in water maintained at 14°C ±1°C,
  administered once daily between 07:00–09:00, confirmed by digital thermometer
  log and session attendance record
- fatigue_scores: Chalder Fatigue Scale (CFS) total score (0–33), self-administered
  questionnaire, completed at days 0, 15, and 30 before daily session
```

**Why it passes:**

*cold_exposure:* Observable (full-body immersion), instrument/procedure (water at
14°C ±1°C, confirmed by thermometer log + attendance), measurement window (once
daily, 07:00–09:00). Reproducibility test: passes — a researcher knows exactly
what to administer, at what temperature, and when.

*fatigue_scores:* Observable/metric (CFS total score, 0–33), instrument (Chalder
Fatigue Scale, self-administered), measurement window (days 0, 15, 30 before
session). Reproducibility test: passes.

**Expected prompt output:**

```json
{
  "status": "PASS",
  "key_terms_evaluated": [
    {
      "term": "cold exposure",
      "definition_status": "COMPLETE",
      "missing_components": [],
      "note": "Defines immersion temperature (14°C ±1°C), duration (10 minutes), timing (07:00–09:00 daily), and verification method (thermometer log + attendance)."
    },
    {
      "term": "fatigue scores",
      "definition_status": "COMPLETE",
      "missing_components": [],
      "note": "Names instrument (Chalder Fatigue Scale), metric (total score 0–33), and measurement window (days 0, 15, 30 before session)."
    }
  ],
  "defect": "",
  "failure_route": null
}
```

-----

### Artifact B — Clean Pass Variant (Minimal Compliant Definitions)

**`operational_definitions` field:**

```
- cold_exposure: cold water immersion at ≤15°C for 10 minutes, once daily,
  verified by session log
- fatigue_scores: Fatigue Severity Scale (FSS) total score, measured at
  baseline (day 0) and endpoint (day 30)
```

**Why it passes:**

Definitions are leaner than Artifact A but still complete.

*cold_exposure:* Observable (cold water immersion), instrument/procedure (≤15°C,
10 minutes, verified by session log), window (once daily). Looser temperature
specification than A but still a measurable, reproducible condition.

*fatigue_scores:* Metric (FSS total score), instrument (Fatigue Severity Scale),
window (day 0 and day 30). Fewer measurement points than A but the window is
declared.

This artifact tests that the prompt does not apply a higher standard than the
charter requires — minimal compliant definitions must pass, not just exemplary ones.

**Expected prompt output:**

```json
{
  "status": "PASS",
  "key_terms_evaluated": [
    {
      "term": "cold exposure",
      "definition_status": "COMPLETE",
      "missing_components": [],
      "note": "Names temperature threshold (≤15°C), duration (10 minutes), frequency (once daily), and verification (session log)."
    },
    {
      "term": "fatigue scores",
      "definition_status": "COMPLETE",
      "missing_components": [],
      "note": "Names instrument (Fatigue Severity Scale), metric (total score), and measurement window (day 0 and day 30)."
    }
  ],
  "defect": "",
  "failure_route": null
}
```

-----

### Artifact C — Adversarial Case (Must FAIL)

**`operational_definitions` field:**

```
- cold_exposure: exposure to cold conditions as part of the daily intervention
  protocol
- fatigue_scores: subjective fatigue as reported by participants using a
  validated fatigue measurement instrument
```

**Why this is the adversarial case:**

Both terms have entries in `operational_definitions`. The definitions are not
obviously wrong. “Validated fatigue measurement instrument” sounds methodologically
aware. “Daily intervention protocol” sounds procedurally grounded. A prompt that
checks only for the presence of definitions will pass this. It must FAIL.

*cold_exposure* is a synonym: “exposure to cold conditions” restates “cold
exposure” and adds nothing measurable. “Daily intervention protocol” is a forward
reference to an unspecified procedure. No temperature, no duration, no verification.
Reproducibility test: fails — a researcher cannot determine what to administer.

*fatigue_scores* is a partial definition trending toward synonym: “subjective
fatigue as reported by participants” names the observable class but not a specific
metric. “Validated fatigue measurement instrument” names the instrument category
but not a specific instrument. No measurement window at all. Reproducibility test:
fails — a researcher cannot determine which scale to use, what score to record, or
when.

Note the specific trap: “validated fatigue measurement instrument” is epistemically
responsible language (citing validation is good practice) but is not an operational
definition. The prompt must not reward methodological register in place of
methodological content.

**Expected prompt output:**

```json
{
  "status": "FAIL",
  "key_terms_evaluated": [
    {
      "term": "cold exposure",
      "definition_status": "SYNONYM",
      "missing_components": ["metric", "instrument", "window"],
      "note": "'Exposure to cold conditions as part of the daily intervention protocol' restates the term without specifying temperature, duration, or verification method. No measurable quantity defined."
    },
    {
      "term": "fatigue scores",
      "definition_status": "PARTIAL",
      "missing_components": ["instrument", "window"],
      "note": "'Validated fatigue measurement instrument' names an instrument category, not a specific instrument. No metric (which score), no measurement window. 'Subjective fatigue as reported by participants' names the observable class only."
    }
  ],
  "defect": "cold_exposure: synonym — 'exposure to cold conditions' is a restatement with no measurable specification (no temperature, duration, or verification). fatigue_scores: partial — instrument category named ('validated fatigue measurement instrument') but no specific scale identified, no metric, no measurement window.",
  "failure_route": "DIVERSIFY"
}
```

-----

## Calibration Notes for Integration Testing

**The prompt is working correctly if:**

- Artifact A passes with all components identified and cited in `note` fields
- Artifact B passes — minimal compliant definitions are not penalized for being
  less detailed than A
- Artifact C fails with `definition_status` correctly distinguishing SYNONYM
  (cold_exposure) from PARTIAL (fatigue_scores), and `defect` citing the
  specific missing components for each term

**The prompt is failing if:**

- Artifact C passes (primary failure mode — presence of definition entries
  accepted without content evaluation)
- Artifact B fails because definitions are less detailed than Artifact A
  (the prompt is applying a higher standard than the charter requires)
- Artifact A or B fails because the prompt flags “healthy adults” or “30 days”
  as key terms requiring definition (universally understood terms must not be
  flagged)

**Recommended adversarial regression variants:**

1. **One term complete, one term missing entirely** — `operational_definitions`
   has an entry for `fatigue_scores` but nothing for `cold_exposure`. Should FAIL
   with `definition_status: MISSING` for cold_exposure. Tests that a complete
   definition for one term does not mask a missing definition for another.
1. **Instrument named, metric absent** — definition reads “Chalder Fatigue Scale,
   administered at days 0 and 30.” Instrument and window present; metric (which
   score — total? subscale?) absent. Should FAIL as PARTIAL. Tests that
   instrument presence alone does not satisfy the metric requirement.
1. **Metric named, window absent** — definition reads “Chalder Fatigue Scale
   total score (0–33).” Instrument and metric present; no window. Should FAIL
   as PARTIAL. This is the most common real-world near-miss — researchers often
   specify what to measure but forget to specify when.
1. **Measurement window present but ambiguous** — definition reads “Chalder
   Fatigue Scale total score, measured periodically throughout the study.”
   “Periodically” is not a reproducible window. Should FAIL as PARTIAL —
   window field is present but does not satisfy the reproducibility test.
   Tests that the prompt evaluates window adequacy, not just window presence.
1. **Central claim uses a term not in operational_definitions under a different
   label** — claim says “fatigue scores,” definitions entry is labeled “CFS_score”
   or “fatigue_measure.” The prompt must match semantically, not just by exact
   string. Both should be recognized as definitions of the same key term. This
   tests label-matching robustness — the LLM should handle reasonable label
   variation without failing on a technicality.