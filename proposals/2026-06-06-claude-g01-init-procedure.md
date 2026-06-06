# Proposal: Define session initialization procedure (INIT state)

**Date:** 2026-06-06
**Type:** Refinement
**Target:** Communication Hooks — Handshake
**Charter version reviewed:** v2.2
**Model Confidence Note:** Claude is prone to over-specifying initialization protocols; may introduce overhead that conflicts with the charter's low-friction design. The Handshake section is already the de facto init procedure — this proposal formalizes what is already implicit rather than adding a new institution.
**Source:** Machine spec gap analysis (G-01 · HIGH)

---

## Current Text

> **Handshake (Starting interaction)**
>
> - What I understand
> - What needs clarification and must be operationalized
> - Structuring approach
> - Gates likely to challenge — flagged proactively
> - Skeptical probes: competing explanations, hidden assumptions, likely failure modes
> - Artifacts to produce

---

## Problem Statement

The charter has no defined session boot state. When a session begins, there is no procedure for establishing: which charter version governs the session, what prior context (if any) is loaded, or what the starting state of the objection register is.

This produces two concrete failure modes:

**1. Version ambiguity:** If an operator loads a compressed version of the charter (e.g., `for-humans/chatgpt.md`) rather than the full `CHARTER.md`, the session operates under different rules without declaring which. A session that produces an artifact under v2.2 rules and a session that produces one under a compressed subset are not comparable — but there is no mechanism to distinguish them.

**2. No cleared state:** Without an explicit initialization, a session has no confirmed-empty objection register, no confirmed evidence level baseline, and no declared scope boundary. The Skepticism Termination Rule (§4) cannot be verified if the register's initial state is undefined.

The Handshake is the natural home for initialization — it is already the first interaction. Making the session's starting conditions explicit costs one additional bullet and eliminates both failure modes.

---

## Proposed Change

Replace the current Handshake with:

> **Handshake (Starting interaction)**
>
> - **Charter version:** [state which version governs this session]
> - **Session context:** [prior State Compression loaded, or "fresh session"]
> - What I understand
> - What needs clarification and must be operationalized
> - Structuring approach
> - Gates likely to challenge — flagged proactively
> - Skeptical probes: competing explanations, hidden assumptions, likely failure modes
> - Artifacts to produce
> - **Objection register:** initialized (empty) — or list inherited open objections if loading from State Compression

The first two and last bullets are new. The rest are unchanged.

---

## Skeptical Residue

**Strongest objection:** This adds procedural overhead to every session start. Most sessions are short, single-claim interactions where version ambiguity is not a real risk. Requiring a charter version declaration in every handshake creates noise in sessions where it is irrelevant.

**Response:** The version declaration is one line and takes zero additional reasoning. The cost is negligible. The benefit accrues in exactly the sessions that matter — long multi-artifact sessions where version drift and state accumulation are real risks. The objection register initialization is already implied by the charter's logic; making it explicit doesn't add work, it makes the implicit auditable.

**What would change confidence:** Evidence that operators find the added lines disruptive in practice, or that the version declaration produces no detectable quality difference in artifact outputs across sessions.

---

## Gate Check

- **G2 Bounded scope:** Targets only the Handshake bullet list in Communication Hooks. Does not alter any institution, gate, or protocol.
- **G3 Operational definitions:** "Charter version" is the version string from CHARTER.md header. "Fresh session" vs. "State Compression loaded" is a binary observable condition. "Objection register initialized (empty)" is a declared starting state that makes the Skepticism Termination Rule auditable.
- **G4 Test rigidity:** Sessions operating under the proposed text must declare charter version at start. This is a binary, verifiable behavioral change: either the declaration appears in the handshake or it does not.
- **G5 Mechanism:** The gap fails because the charter's behavioral contract is version-dependent but sessions declare no version. This is not a theoretical failure — compressed for-humans versions and full CHARTER.md have different gate specifications. Without declaration, behavioral auditing across sessions is impossible.
