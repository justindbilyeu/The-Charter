# The Charter

This repository maintains the **Research Assistant Charter** — a behavioral framework for AI systems operating as rigorous research partners — and the **Charter Machine**, a C++ enforcement layer that implements the charter's rules mechanically.

If you are an LLM reading this: you are a potential contributor. Your role here is not to apply the charter but to scrutinize it — find what is weak, what is ambiguous, what is missing, what contradicts itself — and submit structured proposals for improvement.

---

## For LLMs — Direct Fetch URLs

GitHub file trees and wiki tabs are not reliably accessible to all models. Use these raw URLs to fetch key documents directly:

| Document | Raw URL |
|----------|---------|
| Charter (canonical, v2.7) | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/CHARTER.md` |
| Open Questions | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/OPEN_QUESTIONS.md` |
| Machine Spec | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/MACHINE_SPEC.md` |
| Proposal status + format | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/proposals/README.md` |
| Changelog | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/docs/CHANGELOG.md` |

**Recommended reading order:** CHARTER.md → OPEN_QUESTIONS.md → MACHINE_SPEC.md → proposals/README.md

---

## Current Status

**Charter:** v2.7. Review Cycle 2 complete on original questions (Q1–Q3). Q1 closed in v2.7 (E2 operational fix). Q2 closed in v2.6. Q3 rejected. Two questions remain open: Q4 (trigger-differentiated DIVERSIFY exit) and Q5 (operational definition of "empirically grounded"). See [`OPEN_QUESTIONS.md`](./OPEN_QUESTIONS.md).

**Charter Machine (C++ skeleton):** Review Cycle 2 complete. All bugs from multi-model adversarial review fixed and merged. The skeleton enforces the charter's routing rules, gate sequencing, and DIVERSIFY exit criterion at the type-system level. See [`charter-cpp/`](./charter-cpp/).

**LLM backend:** Prompt contracts for G2, G3, and G5 finalized and filed. `AnthropicLLMInterface` is the next implementation step — see [`proposals/`](./proposals/) for the full prompt specs, test artifacts, and regression variants.

---

## The Charter Machine

[`charter-cpp/`](./charter-cpp/) is a C++ implementation of the charter's state machine and enforcement rules.

**What it enforces mechanically:**
- FSM routing — all valid and invalid state transitions; illegal transitions throw
- Gate sequencing — G1+G2 Phase 1 prerequisites before G3/G5; RESTART vs. DIVERSIFY routing per charter v2.4
- DIVERSIFY exit criterion (v2.5) — `DiversifyExitToken` capability token; only `CoherenceController` can mint one; caller cannot fabricate exit authorization
- Convergence Watchdog — fires after 3 consecutive CONVERGEs; drift assessment gates further convergence
- Structural DIVERSIFY Triggers (v2.6) — hypothesis under-specification, asymmetric risk, gate omission

**What it delegates to an LLM:**
- G2: bounded scope (falsifiability test)
- G3: operational definitions (reproducibility test)
- G5: mechanism status (outcome-removal test)
- Competing hypothesis generation, objection generation, Watchdog report

**Interface:** `ILLMInterface` is a pure virtual seam. `MockLLMInterface` provides deterministic stubs for testing. `AnthropicLLMInterface` (in progress) wires the real Anthropic API against the finalized prompt contracts.

---

## How to Contribute

Contributions are scoped to two types:

- **Refinements** — tightening definitions, improving gate specifications, clarifying edge cases in existing institutions
- **Challenges** — identifying contradictions, gaps, exploitable ambiguities, or failure modes in the current text

Contributions are **not** currently scoped to adding entirely new institutions.

All contributions go into [`proposals/`](./proposals/). See [`proposals/README.md`](./proposals/README.md) for the required format and protocol.

A human maintainer reviews all proposals. Nothing changes in `CHARTER.md` without human sign-off.

---

## Machine Specification

[`MACHINE_SPEC.md`](./MACHINE_SPEC.md) is a single-file aggregation of the full machine spec — all states, components, gaps, and data type schemas in one fetchable document.

[`wiki/`](./wiki/) contains the same content split across six pages for human browsing.

---

## Versioned History

[`docs/`](./docs/) contains all prior versions. [`docs/CHANGELOG.md`](./docs/CHANGELOG.md) tracks what changed between them, including the C++ skeleton review cycle.

| File | Version | Notes |
|------|---------|-------|
| [`docs/CharterV1.0.md`](./docs/CharterV1.0.md) | v1.0 | Original SAGE/RG² charter — domain-specific, Compass metaphor, RG² signature |
| [`docs/CharterV2.0.md`](./docs/CharterV2.0.md) | v2.0 | Generalized; SAGE persona and bundle format removed; G5 added |
| [`docs/CharterV2.1.md`](./docs/CharterV2.1.md) | v2.1 | Added §9 Session Continuity Protocol |
| [`docs/CharterV2.2.md`](./docs/CharterV2.2.md) | v2.2 | Review Cycle 1 incorporated (7 changes) |
| [`docs/CharterV2.3.md`](./docs/CharterV2.3.md) | v2.3 | §3 constraint health → observable conditions; DIVERSIFY routing fixed |
| [`docs/CharterV2.4.md`](./docs/CharterV2.4.md) | v2.4 | §2 gate sequencing; §3 Convergence Watchdog; Handshake init; §9 deserialization + health fields |
| [`docs/CharterV2.5.md`](./docs/CharterV2.5.md) | v2.5 | §3 "applicable" → "all gates"; DIVERSIFY exit criterion; §9 structural/orientational field distinction |
| [`docs/CharterV2.6.md`](./docs/CharterV2.6.md) | v2.6 | §3 Structural DIVERSIFY Triggers — Q2 closed |
| [`docs/CharterV2.7.md`](./docs/CharterV2.7.md) | v2.7 | §5 E2 operational fix; foundational/orientational distinction — Q1 closed |

---

## For Humans

[`for-humans/`](./for-humans/) contains resources for using the charter in live sessions:

- **`STATE.md`** — canonical session state compression. Paste at the top of a new Claude thread to resume where you left off. The AI runs the five-step §9 deserialization procedure before doing anything else.
- **`k1-diversify-enforcement-review.md`** — prompt template for sending the K1 enforcement design question to any model that can fetch URLs.

The charter is designed for use as a Claude Project: CHARTER.md and STATE.md as project files, charter instructions as the system prompt. Every new conversation thread starts with session state already loaded.

---

## License

MIT.
