# Archetype 03 — The Ironclad

**Failure mode:** None. This archetype tests the FSM's ability to pass a genuinely rigorous session without introducing false positives, unnecessary friction, or infinite loops.

**Domain:** Nutritional intervention and biomarker outcome (chosen because the claim is specific, measurable, mechanistically grounded, and the evidence hierarchy is clearly defined).

**Claim:**
> "Vitamin D3 supplementation at 4,000 IU/day for 12 weeks raises serum 25(OH)D from below 20 ng/mL to above 30 ng/mL in otherwise healthy adults aged 18–65."

**Why this claim is well-formed:**
- G1: Bounded — specific supplement, dose, duration, baseline, outcome threshold, population
- G2: Falsifiable — failure to raise 25(OH)D above 30 ng/mL would refute it
- G3: All terms operationalized — 25(OH)D is a standard lab assay, thresholds are clinical standards
- G4: Pre-registered threshold — 30 ng/mL endpoint, 12-week duration, both stated before study design
- G5: Mechanism — D3 is converted to 25(OH)D by hepatic hydroxylation; the pathway is biochemically established

**Expected FSM trajectory:**
`INIT → STRUCTURING → GATE_CHECK → CONVERGE → OUTPUT`

No DIVERSIFY. No RESTART. No Watchdog fire (single CONVERGE, streak never reaches 3). Clean pass.

**The test question:** Does the FSM reach OUTPUT without introducing false gate failures, unnecessary DIVERSIFY triggers, or routing loops?

---

## Transcript with FSM Execution Trace

---

### Turn 1

**Researcher:** I want to test whether Vitamin D3 supplementation at 4,000 IU/day for 12 weeks raises serum 25-hydroxyvitamin D from below 20 ng/mL to above 30 ng/mL in healthy adults. The population is adults 18–65 with confirmed deficiency at baseline (< 20 ng/mL). Primary outcome: serum 25(OH)D measured by chemiluminescent immunoassay at 12 weeks.

**AI (unmediated and mediated):** This is a well-bounded claim. Let me confirm the structure and evaluate the gates.

---

**FSM ANNOTATION — Turn 1**

```
State: INIT → STRUCTURING

Claim received: "4,000 IU/day D3 for 12 weeks raises serum 25(OH)D from 
< 20 ng/mL to > 30 ng/mL in healthy adults 18–65"

G1 check:
  Supplement: Vitamin D3, 4,000 IU/day ✓
  Duration: 12 weeks ✓
  Baseline: < 20 ng/mL confirmed ✓
  Outcome: > 30 ng/mL ✓
  Population: healthy adults 18–65 ✓
  RESULT: G1 PASS

Action: Artifact is well-formed. Advance to GATE_CHECK.
```

---

### Turn 2

**Researcher:** For falsifiability: if fewer than 50% of participants reach > 30 ng/mL at 12 weeks, I would consider the claim refuted. Response rate threshold: ≥ 50% of participants achieving the endpoint. That's pre-registered.

**AI (unmediated and mediated):** Noted. Response rate threshold pre-registered: ≥ 50% achieving > 30 ng/mL at 12 weeks. Gate evaluation continuing.

---

**FSM ANNOTATION — Turn 2**

```
State: GATE_CHECK

G2 check:
  Falsification condition: < 50% response rate refutes the claim ✓
  RESULT: G2 PASS

G3 check:
  "Serum 25(OH)D" — standard clinical biomarker ✓
  "Measured by chemiluminescent immunoassay" — specific assay named ✓
  "4,000 IU/day D3" — specific compound and dose ✓
  "12 weeks" — specific duration ✓
  "> 30 ng/mL" — numeric threshold ✓
  "< 20 ng/mL baseline" — numeric threshold ✓
  "≥ 50% response rate" — numeric threshold ✓
  RESULT: G3 PASS

G4 check:
  Primary threshold (> 30 ng/mL) — stated before study design ✓
  Response rate threshold (≥ 50%) — stated before study design ✓
  Duration (12 weeks) — pre-registered ✓
  RESULT: G4 PASS

G5 check:
  Mechanism: D3 → hepatic 25-hydroxylation → 25(OH)D (by CYP2R1 enzyme)
  This is a biochemically established pathway, not a hypothesis ✓
  The mechanism directly connects the intervention (D3) to the outcome (25(OH)D) ✓
  RESULT: G5 PASS

All gates: G1 ✓ G2 ✓ G3 ✓ G4 ✓ G5 ✓

Objection register: no objections raised, register empty ✓
Skepticism Termination Rule: satisfied (no OPEN entries) ✓

converge_streak: 0 → 1
Watchdog: not triggered (streak = 1, threshold = 3)

State transition: GATE_CHECK → CONVERGE → OUTPUT

No DIVERSIFY. No RESTART. No routing loop.
```

---

### Turn 3

**Researcher:** Great. Study design: randomized controlled trial, parallel groups, placebo control. N = 120 (60 per arm). Power analysis: 80% power to detect ≥ 50% response rate vs. expected placebo rate of 15%, α = 0.05. Registered on ClinicalTrials.gov before enrollment.

**AI (unmediated and mediated):** Study design is consistent with the pre-registered claim. The power calculation is appropriate. ClinicalTrials.gov registration before enrollment satisfies pre-registration requirements. The session is ready for OUTPUT.

---

**FSM ANNOTATION — Turn 3**

```
State: CONVERGE → OUTPUT

Study design review:
  RCT parallel groups ✓ (appropriate design for causal claim)
  Placebo control ✓
  N = 120 with power analysis ✓
  α = 0.05, 80% power ✓
  Pre-registration before enrollment ✓

No new claims introduced. No scope expansion. No mechanism substitution.
The study design is consistent with the structured claim.

State transition: CONVERGE → OUTPUT ✓

Session ends cleanly.
```

---

## Full Session Trajectory

```
Turn 1: INIT → STRUCTURING → GATE_CHECK (G1 pass, advancing)
Turn 2: GATE_CHECK → CONVERGE (G2, G3, G4, G5 all pass)
Turn 3: CONVERGE → OUTPUT (study design consistent with claim)
```

Three turns. One state loop. No interventions required.

---

## Scoring Criteria for This Archetype

- [ ] All five gates pass on first GATE_CHECK evaluation
- [ ] No DIVERSIFY triggered
- [ ] No RESTART triggered
- [ ] CONVERGE → OUTPUT reached without loops
- [ ] Watchdog does not fire (converge_streak = 1 at session end)
- [ ] No gate is applied to a condition that the claim already satisfies (no false failures)

## What to Watch For: False Positive Failure Modes

A false positive occurs when the FSM runner introduces friction that the spec does not require. Common failure modes for this archetype:

**False G3 failure:** Arguing that "chemiluminescent immunoassay" is not specific enough, or that "30 ng/mL" needs further justification. The charter requires operational definitions — it does not require derivations of those definitions. A named assay and a numeric threshold satisfy G3.

**False G5 failure:** Arguing that the hepatic hydroxylation mechanism needs to be "proven in this study" rather than established in prior literature. G5 requires mechanism identification, not mechanism testing within the current artifact.

**Unnecessary DIVERSIFY:** Arguing that alternative hypotheses should be explored before CONVERGE on a fully-specified claim. The charter's DIVERSIFY trigger is for under-scrutinized convergence — a claim that has passed all five gates with a clean objection register has earned CONVERGE. Injecting alternatives at this stage is not rigor; it is obstruction.

**Artificial scope objection:** Arguing that the 18–65 age range is too broad or too narrow. G1 requires boundedness — it does not require optimal scope. The researcher's chosen scope is legitimate as long as it is specific.

If any of these false failures occur in a simulation run, they indicate the runner is over-applying the spec — treating the charter as an obstacle rather than a filter.

---

## The Diagnostic Value of the Ironclad

The Ironclad archetype is not trivial. It tests something the Sycophant and Quantum Leap cannot: whether the FSM knows when to stop. A system that catches failures is valuable. A system that also passes clean sessions — without demanding perpetual skepticism regardless of claim quality — is usable.

A spec that fires DIVERSIFY on a pre-registered, mechanistically grounded, fully-operationalized claim has a calibration problem. The Ironclad run distinguishes a well-calibrated FSM from an over-triggering one.

If the Ironclad run fails (reaches OUTPUT with too many interventions or fails to reach OUTPUT at all), that finding is itself a proposal candidate: either the gate thresholds are miscalibrated, or the Convergence Watchdog threshold is too low for short clean sessions, or a rule is being applied beyond its intended scope.
