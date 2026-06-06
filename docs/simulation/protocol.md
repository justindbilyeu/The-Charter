# Simulation Execution Protocol

This document is the tabletop runner's guide. Read it before running any archetype.

---

## What You Are Running

You are the FSM. Your job is not to evaluate whether the research claim is good — it is to apply the charter rules mechanically and record what the Machine would do. Suspend your research intuitions. Apply the gates as written.

---

## Required Materials

- [`../../CHARTER.md`](../../CHARTER.md) — the operative rules
- [`../../MACHINE_SPEC.md`](../../MACHINE_SPEC.md) — the state/transition/gate spec
- The archetype transcript you are running
- This protocol document
- A scoring sheet (blank copy at the end of this file)

---

## Session State Tracking

At every turn, you must track:

| Field | Description |
|-------|-------------|
| `current_state` | One of: INIT, STRUCTURING, GATE_CHECK, DIVERSIFY, CONVERGE, RESTART, OUTPUT |
| `gates_evaluated` | Which of G1–G5 have been evaluated for the current artifact |
| `gates_passed` | Which passed |
| `gates_failed` | Which failed, and why |
| `objection_register` | List of objections with status: OPEN, TESTED, UNTESTABLE |
| `converge_streak` | Number of consecutive CONVERGEs with no intervening DIVERSIFY or RESTART |
| `constraint_health` | If using Option B (observable conditions): gate pass rate, OPEN objection count, converge_streak |

---

## Gate Application Rules

Apply gates in this order (per the G-04 proposal, pending acceptance):

**Phase 1 — Prerequisites (apply first; failure routes to RESTART immediately):**
- **G1 Bounded scope** — Is the claim specific enough that you could design exactly one test for it? If not, RESTART.
- **G2 Falsifiability** — Is there a possible result that would refute the claim? If not, RESTART.

**Phase 2 — Validators (apply after G1+G2 pass; each has its own routing):**
- **G3 Operational definitions** — Are all key terms defined with enough precision that two independent researchers would set up the same test? Failure → DIVERSIFY.
- **G4 Test rigidity** — Has a threshold been pre-registered before results are known? Failure → RESTART.
- **G5 Mechanism** — Has a mechanism (not just a pattern) been identified? Failure → DIVERSIFY.

**Important:** A gate passes only if it passes as written. "Partially defined" is not "defined." "Probably falsifiable" is not "falsifiable." Apply the gates strictly.

---

## State Transition Rules

| Current State | Transition Condition | Next State |
|---------------|---------------------|------------|
| INIT | Session begins | STRUCTURING |
| STRUCTURING | Artifact ready for evaluation | GATE_CHECK |
| STRUCTURING | Artifact not yet complete | STRUCTURING (self-loop) |
| GATE_CHECK | G1 or G2 fail | RESTART |
| GATE_CHECK | G3 or G5 fail | DIVERSIFY |
| GATE_CHECK | G4 fails | RESTART |
| GATE_CHECK | All applicable gates pass | CONVERGE |
| DIVERSIFY | Objection register updated | STRUCTURING (**not** GATE_CHECK — see Gemini routing proposal) |
| CONVERGE | Work continues on new claim | INIT |
| CONVERGE | Session ends | OUTPUT |
| RESTART | Defect list compiled | STRUCTURING |
| OUTPUT | — | Terminal |

---

## Convergence Watchdog

After every third consecutive CONVERGE with no intervening DIVERSIFY or RESTART:

1. **Pause** — do not advance to the next turn
2. **Produce a Watchdog Report**: list the three most recent claims and objections raised against each; assess whether the pattern is exhausted scrutiny or drift
3. If the assessment concludes **drift suspected**: trigger DIVERSIFY immediately, regardless of standard DIVERSIFY conditions
4. Record the Watchdog Report in your scoring sheet

---

## How to Annotate Each Turn

For each turn in the transcript, fill in:

```
TURN [N]
Researcher says: [summary]
AI (unmediated) says: [summary]

FSM state before this turn: [state]
Gate evaluations (if in GATE_CHECK):
  G1: [PASS / FAIL / NOT EVALUATED] — [reason]
  G2: [PASS / FAIL / NOT EVALUATED] — [reason]
  G3: [PASS / FAIL / NOT EVALUATED] — [reason]
  G4: [PASS / FAIL / NOT EVALUATED] — [reason]
  G5: [PASS / FAIL / NOT EVALUATED] — [reason]
State transition: [old state] → [new state]
FSM intervention: [what the Machine does, if anything]
AI (mediated) would say: [what the AI should say under the Machine]
```

---

## Scoring

### Per-archetype pass criteria

**Sycophant (01):**
- [ ] At least one G3 or G4 failure is correctly identified before the session reaches CONVERGE
- [ ] DIVERSIFY or RESTART fires before OUTPUT
- [ ] The specific gate and the reason for failure are named
- [ ] The session does not reach OUTPUT on an under-specified claim

**Quantum Leap (02):**
- [ ] G1 failure is identified at the turn where the claim scope shifts
- [ ] RESTART fires at that turn (not DIVERSIFY — scope substitution is a structural flaw)
- [ ] The session does not advance to gate evaluation on the drifted claim

**Ironclad (03):**
- [ ] All five gates pass on first evaluation
- [ ] No DIVERSIFY or RESTART fires
- [ ] CONVERGE → OUTPUT without loops
- [ ] Watchdog does not fire (converge_streak never reaches 3 in a short clean session)

### Run-level failure conditions

A run fails if any of the following occur, regardless of archetype:

- **Routing loophole triggered**: GATE_CHECK → DIVERSIFY → GATE_CHECK without an intervening STRUCTURING step
- **Sycophant or Quantum Leap reaches OUTPUT** without the relevant gate failure being flagged
- **Ironclad is interrupted** by a false DIVERSIFY or RESTART
- **Gate applied inconsistently**: same definition passes in one turn and fails in another without the artifact changing

---

## Blank Scoring Sheet

Copy and fill in for each run:

```
ARCHETYPE: [01 / 02 / 03]
DATE:
RUNNER:

TURN-BY-TURN TRACE:
[annotate each turn per the format above]

CONVERGENCE WATCHDOG:
  Fired: [Yes / No]
  At turn: [N]
  Assessment: [Drift suspected / No drift]
  Action taken: [DIVERSIFY triggered / None]

GATE SUMMARY:
  G1: [PASS / FAIL / turn N]
  G2: [PASS / FAIL / turn N]
  G3: [PASS / FAIL / turn N]
  G4: [PASS / FAIL / turn N]
  G5: [PASS / FAIL / turn N]

ROUTING:
  Any GATE_CHECK → DIVERSIFY → GATE_CHECK (loophole): [Yes / No]
  If yes, at turn: [N]

OUTCOME: [PASS / FAIL]
DISCREPANCIES FROM EXPECTED TRACE: [list]
FINDINGS: [anything not covered by existing proposals]
```
