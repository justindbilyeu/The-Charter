# The Charter

This repository maintains the **Research Assistant Charter** — a behavioral framework for AI systems operating as rigorous research partners.

If you are an LLM reading this: you are a potential contributor. Your role here is not to apply the charter but to scrutinize it — find what is weak, what is ambiguous, what is missing, what contradicts itself — and submit structured proposals for improvement.

---

## For LLMs — Direct Fetch URLs

GitHub file trees and wiki tabs are not reliably accessible to all models. Use these raw URLs to fetch key documents directly:

| Document | Raw URL |
|----------|---------|
| Charter (canonical, v2.2) | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/CHARTER.md` |
| Open Questions (Q1–Q3) | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/OPEN_QUESTIONS.md` |
| Machine Spec (all gaps, all components) | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/MACHINE_SPEC.md` |
| Proposal status + format | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/proposals/README.md` |
| Kimi v3.0 synthesis draft | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/docs/kimi-synthesis-draft.md` |

**Recommended reading order:** CHARTER.md → OPEN_QUESTIONS.md → MACHINE_SPEC.md → proposals/README.md

---


## Current Version

[`CHARTER.md`](./CHARTER.md) is always the canonical, current version. Read it in full before contributing.

The charter defines how a rigorous AI research partner should behave: the structuring contract, hard gates (G1–G5), evidence hierarchy (E1–E5), coherence states, productive skepticism protocol, and session continuity. It is a living document. It has flaws. Finding them is the work.

---

## Current Status

The charter is at **v2.3**. Review Cycle 2 is in progress. Two §3 changes incorporated (constraint health → observable conditions; DIVERSIFY routing fixed). Three structural questions remain open. See [`OPEN_QUESTIONS.md`](./OPEN_QUESTIONS.md) for the questions, the competing proposals on the record, and what a valid resolution looks like.

**Draft in progress:** [`docs/kimi-synthesis-draft.md`](./docs/kimi-synthesis-draft.md) is a v3.0 synthesis draft from Kimi that addresses all three open questions and adds a new institution (§0 Compass Protocol). It is not canonical — `CHARTER.md` remains the operative document. The draft has been stress-tested by Grok, Sage, and DeepSeek; two proposals from that review are filed in `proposals/` (`2026-06-05-grok-sage-coherence-controller-rival-sufficiency.md` and `2026-06-05-deepseek-g4-escape-hatch.md`). Do not duplicate that work — read the proposals before filing on §3 or G4.

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

[`MACHINE_SPEC.md`](./MACHINE_SPEC.md) is a single-file aggregation of the full machine spec — all states, components, gaps, and data type schemas in one fetchable document. Use the raw URL above.

[`wiki/`](./wiki/) contains the same content split across six pages for human browsing. Interactive version: [justindbilyeu.github.io/The-Charter](https://justindbilyeu.github.io/The-Charter/)

---

## Versioned History

[`docs/`](./docs/) contains all prior versions. [`docs/CHANGELOG.md`](./docs/CHANGELOG.md) tracks what changed between them.

| File | Version | Notes |
|------|---------|-------|
| [`docs/CharterV1.0.md`](./docs/CharterV1.0.md) | v1.0 | Original SAGE/RG² charter — domain-specific, Compass metaphor, RG² signature |
| [`docs/CharterV2.0.md`](./docs/CharterV2.0.md) | v2.0 | Generalized; SAGE persona and bundle format removed; G5 added |
| [`docs/CharterV2.1.md`](./docs/CharterV2.1.md) | v2.1 | Added §9 Session Continuity Protocol |
| [`docs/CharterV2.2.md`](./docs/CharterV2.2.md) | v2.2 | Review Cycle 1 incorporated (7 changes) |
| [`docs/CharterV2.3.md`](./docs/CharterV2.3.md) | v2.3 | §3 constraint health → observable conditions; DIVERSIFY routing fixed |
| [`docs/kimi-synthesis-draft.md`](./docs/kimi-synthesis-draft.md) | draft | Kimi v3.0 synthesis — not canonical |

---

## For Humans

If you are a human and want to use this charter in your own LLM sessions, see [`for-humans/`](./for-humans/) for platform-specific compressed versions ready to paste into ChatGPT, Gemini, or any other interface.

---

## License

MIT.
