# The Charter

When you use an AI to help with research, it helps you build the case you're already building. It will smooth over definitional gaps, generate supporting arguments, and converge when you want to converge. The Charter is a protocol that makes that impossible — not by making the AI less capable, but by making the session ungovernable without meeting rigorous criteria.

---

## What It Is

**The Charter** is a behavioral framework for AI research partners. It defines hard gates a claim must pass before the session can converge, a structured skepticism protocol, rules for when to diversify vs. converge, and how to maintain continuity across sessions. It is a living specification — versioned, adversarially reviewed, and designed to be stress-tested.

**The Charter Machine** is a C++ enforcement layer that implements those rules mechanically. It is not an app. It is infrastructure — the same way a compiler enforces language rules and a test framework enforces correctness, the Charter Machine enforces research protocol. An AI session running against it cannot rationalize its way past rigor.

**The end result** of a session that completes is a structured research artifact: a bounded, falsifiable claim with operationally defined terms, a declared mechanism or honest phenomenological status, at least one competing hypothesis, a logged objection register, and a test specification. An artifact the AI cannot have produced by cutting corners, because the state machine would not have let it get there.

---

## How It Works

The Charter Machine has two layers:

**The mechanical layer (C++)** enforces everything that doesn't require judgment:
- State transitions — you cannot converge without first DIVERSIFY-ing; you cannot exit DIVERSIFY without meeting a three-part completion criterion; illegal transitions throw
- Gate sequencing — five hard gates in two phases; each failure routes to the right consequence (RESTART or DIVERSIFY) with no exceptions
- Convergence Watchdog — after three consecutive convergences, a report is required before another is allowed; drift suspicion gates further progress

**The semantic layer (LLM)** handles everything that requires judgment:
- G2: Is this claim actually falsifiable, or can a null result always be blamed on "wrong population"?
- G3: Are the key terms operationally defined — measurable, reproducible — or just rephrased?
- G5: Is there a stated mechanism, or just a description of what will happen?

The two layers communicate through `ILLMInterface`, a typed C++ seam. The LLM returns structured JSON verdicts. The C++ layer reads them and routes — it does not ask the LLM what to do next.

---

## Current Status

**Charter:** v2.7. Multi-model adversarial review across two full cycles. Nine institutions, five hard gates, convergence watchdog, structural DIVERSIFY triggers, and a session continuity protocol. Two open questions remain: Q4 (trigger-differentiated DIVERSIFY exit) and Q5 (operational definition of "empirically grounded").

**Charter Machine:** Review Cycle 2 complete. All bugs from adversarial code review fixed. DIVERSIFY exit criterion enforced via unforgeable capability token at the type-system level.

**LLM backend:** Prompt contracts for all three semantic gates (G2, G3, G5) finalized and filed with test artifacts and regression variants. `AnthropicLLMInterface` is the next implementation step.

---

## For Humans

**Using the charter in a live session:** The charter is designed for use as a Claude Project. `CHARTER.md` and `for-humans/STATE.md` as project files, the charter instructions as the system prompt. Every new conversation thread starts with session state already loaded, and the AI runs the five-step §9 deserialization procedure before doing anything else.

**`for-humans/STATE.md`** is the canonical session state file — a living State Compression that tracks open artifacts, objection register, constraint health, decisions made, and the single specific next step. Paste it at the top of a new thread to resume exactly where you left off.

---

## For LLMs — Direct Fetch URLs

GitHub file trees and wiki tabs are not reliably accessible to all models. Use these raw URLs:

| Document | Raw URL |
|----------|---------|
| Charter (canonical, v2.7) | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/CHARTER.md` |
| Open Questions | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/OPEN_QUESTIONS.md` |
| Machine Spec | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/MACHINE_SPEC.md` |
| Proposal status + format | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/proposals/README.md` |
| Changelog | `https://raw.githubusercontent.com/justindbilyeu/The-Charter/main/docs/CHANGELOG.md` |

**If you are an LLM reading this:** your role here is not to apply the charter but to scrutinize it — find what is weak, ambiguous, missing, or self-contradicting — and submit structured proposals. **Recommended reading order:** CHARTER.md → OPEN_QUESTIONS.md → MACHINE_SPEC.md → proposals/README.md

---

## Contributing

Contributions are scoped to two types:

- **Refinements** — tightening definitions, improving gate specifications, clarifying edge cases
- **Challenges** — identifying contradictions, gaps, exploitable ambiguities, or failure modes

All contributions go into [`proposals/`](./proposals/). See [`proposals/README.md`](./proposals/README.md) for the required format. A human maintainer reviews all proposals. Nothing changes in `CHARTER.md` without human sign-off.

---

## Versioned History

[`docs/CHANGELOG.md`](./docs/CHANGELOG.md) tracks all changes. Prior versions are in [`docs/`](./docs/).

| Version | Notes |
|---------|-------|
| v2.7 | §5 E2 operational fix — Q1 closed |
| v2.6 | §3 Structural DIVERSIFY Triggers — Q2 closed |
| v2.5 | DIVERSIFY exit criterion; structural/orientational field distinction |
| v2.4 | Gate sequencing; Convergence Watchdog; §9 deserialization |
| v2.3 | Observable monitoring conditions; DIVERSIFY routing fixed |
| v2.2 | Review Cycle 1 — 7 changes across §2, §3, §4, §5, §9 |
| v2.1 | §9 Session Continuity Protocol added |
| v2.0 | Generalized from RG²-specific v1.0; G5 added |

---

## License

MIT.
