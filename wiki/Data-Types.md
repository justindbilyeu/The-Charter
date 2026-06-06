# Data Types

Data structures flowing through the charter machine. Most are currently untyped in the charter prose — this page formalizes them.

---

## raw_claim

**Type:** INPUT  
**Produced by:** Operator  
**Consumed by:** Structuring Contract (SC)

The unstructured idea, hypothesis, or claim as received from the operator. No format constraints. May arrive as prose, a question, an intuition, or a partial structure.

**Schema:** `string` (unstructured)

---

## structured_artifact

**Type:** INTERMEDIATE  
**Produced by:** Structuring Contract (SC)  
**Consumed by:** Hard Gates (HG)

A compiled claim that satisfies the Structuring Contract (§1). Gate-ready.

**Schema:**
```
{
  central_claim: string,          // ≤3 sentences, bounded, falsifiable
  operational_definitions: {
    term: string,
    metric: string,
    measurement_window: string
  }[],
  test_specification: {
    conditions: string,
    parameters: string,
    stopping_rules: string
  },
  success_criteria: {
    threshold: number,
    direction: "greater_than" | "less_than" | "between",
    description: string
  }[],                            // ≥2 numeric thresholds required
  compass_origin?: string         // v3.0 draft: CP-derived tag if applicable
}
```

---

## gate_result

**Type:** INTERMEDIATE  
**Produced by:** Hard Gates (HG)  
**Consumed by:** Coherence Controller (CC)

The result of applying G1–G5 to a structured artifact.

**Schema:**
```
{
  gate_id: "G1" | "G2" | "G3" | "G4" | "G5",
  result: "PASS" | "FAIL",
  defect: string | null,          // null on PASS
  recommendation: "CONVERGE" | "DIVERSIFY" | "RESTART" | null
}[]
```

**Gap note:** Gate failure sequencing is undefined (G-04). The schema above is proposed, not specified in the charter.

---

## evidence_level

**Type:** INTERMEDIATE  
**Produced by:** Evidence Hierarchy (EH)  
**Consumed by:** Coherence Controller (CC), State Compression (SCP)

The evidence tier assigned to a claim.

**Schema:**
```
{
  claim_ref: string,
  level: "E1" | "E2" | "E3" | "E4" | "E5",
  rationale: string,
  sources?: string[]              // Required for E2+ under v3.0 draft
}
```

---

## objection_set

**Type:** INTERMEDIATE  
**Produced by:** Productive Skepticism Protocol (PSP)  
**Consumed by:** Coherence Controller (CC)

**Gap note:** Currently untyped in the charter. The Skepticism Termination Rule requires knowing which objections are OPEN, TESTED, or UNTESTABLE — but no Objection Register schema is defined (G-06). The schema below is proposed.

**Proposed schema:**
```
{
  id: string,
  claim_ref: string,
  objection_text: string,
  type: "convergence" | "assumption" | "failure_mode" | "scope" | "mechanism",
  status: "OPEN" | "TESTED" | "UNTESTABLE",
  test_result: string | null,     // null if OPEN or UNTESTABLE
  untestable_reasoning: string | null,  // required if UNTESTABLE
  session_timestamp: string
}[]
```

Termination condition: `status === "OPEN"` count === 0 AND at least one objection was raised.

---

## state_compression

**Type:** OUTPUT  
**Produced by:** Session Continuity Protocol (SCP)  
**Consumed by:** Next session (INIT)

The serialized session handoff document. Produced on `/compress` or trigger conditions.

**Schema (v2.2):**
```
{
  charter_version: string,        // Added in v3.0 draft
  session_id: string,             // Added in v3.0 draft
  timestamp: string,              // Added in v3.0 draft
  active_claims: {
    claim: string,
    evidence_level: "E1" | "E2" | "E3" | "E4" | "E5"
  }[],
  gate_status: {
    artifact_ref: string,
    gates: {
      gate_id: "G1" | "G2" | "G3" | "G4" | "G5",
      status: "PENDING" | "PASSED" | "FAILED"
    }[]
  }[],
  decisions: {
    decision: string,
    reasoning: string
  }[],
  skeptical_residue: {
    resolved: string[],
    open: string[],
    deferred: string[]
  },
  next_step: string,              // Single, specific, actionable
  assumptions_modified: string[]
}
```

**Gap note:** Deserialization protocol undefined (G-07). How a new session re-ingests this schema is unspecified.

---

## artifact_output

**Type:** OUTPUT  
**Produced by:** OUTPUT state  
**Consumed by:** Operator / external

The final research artifact produced when CONVERGE is reached and the session moves to OUTPUT.

**Schema:** Follows the relevant Output Mode (§ Output Modes):
- Mode 1: 3–7 key points + recommended actions + "what would falsify this?" + next artifacts
- Mode 2: Objective + scope + assumptions + minimum artifact spec + quality gates + expected deliverables
- Mode 3: Full framework with context, variables, model, success criteria, test specification, risks, execution plan, verification, skeptical residue
