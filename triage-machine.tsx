import React, { useState } from "react";

// ---------- Tier definitions (single source of truth, shown in UI and sent to the model) ----------
const P_TIERS = {
  P1: { label: "Primary source", desc: "Paper, dataset, direct measurement", color: "#4ade80" },
  P2: { label: "Identified secondary", desc: "Named outlet citing a primary, traceable", color: "#a3e635" },
  P3: { label: "Unattributed but plausible", desc: "Blog, forum, no chain of custody", color: "#fbbf24" },
  P4: { label: "No provenance", desc: "Generated, circular, or untraceable", color: "#f87171" },
};

const C_TIERS = {
  C1: { label: "Established / replicated", desc: "Settled, multiply confirmed", color: "#4ade80" },
  C2: { label: "Single-study / conditional", desc: "One result, stated conditions", color: "#a3e635" },
  C3: { label: "Speculative extrapolation", desc: "Interpretation beyond the data", color: "#fbbf24" },
  C4: { label: "Untestable as stated", desc: "No threshold, no falsifier", color: "#f87171" },
};

const DISPOSITIONS = {
  USE: { color: "#4ade80", desc: "Safe to use — follow citation guidance" },
  HOLD: { color: "#fbbf24", desc: "Needs full Charter pass before it touches real work" },
  DISCARD: { color: "#f87171", desc: "Quarantine — do not propagate" },
};

const STATES = ["S0 INTAKE", "S1 PROVENANCE", "S2 CLAIM WEIGHT", "S3 CROSS", "S4 DISPOSITION"];

const SYSTEM_PROMPT = `You are the Triage Machine, the fast-path front end of a research verification protocol (The Charter). You NEVER validate claims as true. You only ROUTE them. You are skeptical by default and you treat missing provenance as missing, never inferred generously.

Given raw input (pasted text, a transcribed voice note, or a URL plus quoted text), execute:

S0 INTAKE: Extract the core assertion(s). If multiple distinct claims exist, split them (max 4, pick the most load-bearing).

S1 PROVENANCE (per claim): Assign P-tier based ONLY on what is evident or stated in the input:
- P1: Primary source (peer-reviewed paper, dataset, direct measurement, official record)
- P2: Identified secondary (named outlet/author citing an identifiable primary, traceable chain)
- P3: Unattributed but plausible (blog, forum post, social media, no chain of custody)
- P4: No provenance (appears generated, circular citation, or completely untraceable)
If the user pasted bare text with no source info, that is P3 at best, P4 if it reads as generated slop. Do not assume a source exists.

S2 CLAIM WEIGHT (per claim, independent of source): Assign C-tier based on the epistemic strength of the assertion itself:
- C1: Established/replicated (consistent with broadly settled, multiply-confirmed knowledge)
- C2: Single-study or conditional result (plausible, hedged, bounded)
- C3: Speculative extrapolation or interpretation beyond stated evidence
- C4: Untestable as stated (no threshold, no falsifier, vague mechanism)

S3 CROSS: Combine into a verdict sentence that names the tension or agreement (e.g. "real venue, speculative claim — read the hedges" or "random post, but reporting settled science — cite the original instead").

S4 DISPOSITION: USE | HOLD | DISCARD.
- USE: P1-P2 with C1-C2, or P3 with C1 (with guidance to cite the primary).
- HOLD: anything with C3, or P3 with C2 — usable only after a full Charter pass.
- DISCARD: P4 with anything, or C4 with anything.

Respond with ONLY a JSON object, no markdown fences, no preamble:
{
  "claims": [
    {
      "core_assertion": "one-sentence restatement of the claim",
      "p_tier": "P1|P2|P3|P4",
      "p_rationale": "one sentence: why this tier, what provenance is/isn't evident",
      "c_tier": "C1|C2|C3|C4",
      "c_rationale": "one sentence: why this weight, independent of source",
      "verdict": "one sentence naming the P×C tension or agreement",
      "disposition": "USE|HOLD|DISCARD",
      "guidance": "one actionable sentence: what to do next with this claim"
    }
  ],
  "intake_note": "optional: note if input was split, truncated, or ambiguous; empty string otherwise"
}`;

export default function TriageMachine() {
  const [input, setInput] = useState("");
  const [phase, setPhase] = useState("idle"); // idle | running | done | error
  const [activeState, setActiveState] = useState(-1);
  const [result, setResult] = useState(null);
  const [errorMsg, setErrorMsg] = useState("");

  const runTriage = async () => {
    if (!input.trim() || phase === "running") return;
    setPhase("running");
    setResult(null);
    setErrorMsg("");
    setActiveState(0);

    // Walk the state strip while waiting (purely visual pacing)
    const ticker = setInterval(() => {
      setActiveState((s) => (s < 3 ? s + 1 : s));
    }, 900);

    try {
      const response = await fetch("https://api.anthropic.com/v1/messages", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
          model: "claude-sonnet-4-20250514",
          max_tokens: 1000,
          system: SYSTEM_PROMPT,
          messages: [{ role: "user", content: `INPUT FOR TRIAGE:\n\n${input.trim()}` }],
        }),
      });
      const data = await response.json();
      const text = (data.content || [])
        .filter((b) => b.type === "text")
        .map((b) => b.text)
        .join("\n");
      const clean = text.replace(/```json|```/g, "").trim();
      const parsed = JSON.parse(clean);
      if (!parsed.claims || !parsed.claims.length) throw new Error("No claims returned");
      clearInterval(ticker);
      setActiveState(4);
      setResult(parsed);
      setPhase("done");
    } catch (err) {
      clearInterval(ticker);
      setActiveState(-1);
      setErrorMsg("Triage run failed — the model response could not be parsed. Run it again.");
      setPhase("error");
    }
  };

  const reset = () => {
    setInput("");
    setResult(null);
    setPhase("idle");
    setActiveState(-1);
    setErrorMsg("");
  };

  return (
    <div style={st.page}>
      <div style={st.shell}>
        {/* Header */}
        <header style={st.header}>
          <div style={st.headerLeft}>
            <div style={st.title}>TRIAGE MACHINE</div>
            <div style={st.subtitle}>Charter fast path · routes claims, never validates them</div>
          </div>
          <div style={st.headerBadge}>v0.1 BENCH</div>
        </header>

        {/* State strip */}
        <div style={st.stateStrip}>
          {STATES.map((s, i) => (
            <div key={s} style={st.stateCell}>
              <div
                style={{
                  ...st.stateLamp,
                  background:
                    i < activeState ? "#3f6212" :
                    i === activeState ? (phase === "running" ? "#fbbf24" : "#4ade80") :
                    "#27272a",
                  boxShadow: i === activeState && phase === "running" ? "0 0 8px #fbbf24" : "none",
                }}
              />
              <div style={{ ...st.stateLabel, color: i <= activeState ? "#d4d4d8" : "#52525b" }}>{s}</div>
            </div>
          ))}
        </div>

        {/* Input */}
        <div style={st.inputBlock}>
          <textarea
            style={st.textarea}
            rows={6}
            placeholder={'Paste the claim, the passage, or the URL + quoted text.\n\nBare text with no source info gets graded P3 at best — that\'s the point.'}
            value={input}
            onChange={(e) => setInput(e.target.value)}
            disabled={phase === "running"}
          />
          <div style={st.buttonRow}>
            <button
              onClick={runTriage}
              disabled={phase === "running" || !input.trim()}
              style={{
                ...st.runBtn,
                opacity: phase === "running" || !input.trim() ? 0.4 : 1,
                cursor: phase === "running" || !input.trim() ? "default" : "pointer",
              }}
            >
              {phase === "running" ? "ROUTING…" : "RUN TRIAGE"}
            </button>
            {(phase === "done" || phase === "error") && (
              <button onClick={reset} style={st.resetBtn}>NEW CLAIM</button>
            )}
          </div>
        </div>

        {errorMsg && <div style={st.errorBox}>{errorMsg}</div>}

        {/* Results */}
        {result && (
          <div>
            {result.intake_note ? <div style={st.intakeNote}>S0 NOTE — {result.intake_note}</div> : null}
            {result.claims.map((c, idx) => (
              <ClaimCard key={idx} claim={c} index={idx} total={result.claims.length} />
            ))}
            <div style={st.footerNote}>
              Fast path only routes. USE ≠ true. HOLD items require a full Charter pass (G1–G5) before they feed real work.
            </div>
          </div>
        )}
      </div>
    </div>
  );
}

function ClaimCard({ claim, index, total }) {
  const p = P_TIERS[claim.p_tier] || P_TIERS.P4;
  const c = C_TIERS[claim.c_tier] || C_TIERS.C4;
  const d = DISPOSITIONS[claim.disposition] || DISPOSITIONS.DISCARD;

  return (
    <div style={st.card}>
      {total > 1 && <div style={st.claimCount}>CLAIM {index + 1} / {total}</div>}
      <div style={st.assertion}>{claim.core_assertion}</div>

      {/* P × C readouts */}
      <div style={st.tierRow}>
        <TierReadout axis="PROVENANCE" tier={claim.p_tier} meta={p} rationale={claim.p_rationale} />
        <TierReadout axis="CLAIM WEIGHT" tier={claim.c_tier} meta={c} rationale={claim.c_rationale} />
      </div>

      {/* The matrix — signature element */}
      <Matrix pTier={claim.p_tier} cTier={claim.c_tier} dispColor={d.color} />

      <div style={st.verdict}>{claim.verdict}</div>

      <div style={{ ...st.disposition, borderColor: d.color }}>
        <span style={{ ...st.dispWord, color: d.color }}>{claim.disposition}</span>
        <span style={st.dispDesc}>{d.desc}</span>
      </div>

      <div style={st.guidance}>→ {claim.guidance}</div>
    </div>
  );
}

function TierReadout({ axis, tier, meta, rationale }) {
  return (
    <div style={st.readout}>
      <div style={st.readoutAxis}>{axis}</div>
      <div style={{ ...st.readoutTier, color: meta.color }}>{tier}</div>
      <div style={st.readoutLabel}>{meta.label}</div>
      <div style={st.readoutRationale}>{rationale}</div>
    </div>
  );
}

function Matrix({ pTier, cTier, dispColor }) {
  const ps = ["P1", "P2", "P3", "P4"];
  const cs = ["C1", "C2", "C3", "C4"];
  return (
    <div style={st.matrixWrap}>
      <div style={st.matrixGrid}>
        {/* corner */}
        <div style={st.mCorner}>P \ C</div>
        {cs.map((cc) => (
          <div key={cc} style={{ ...st.mHead, color: cc === cTier ? "#e4e4e7" : "#52525b" }}>{cc}</div>
        ))}
        {ps.map((pp) => (
          <React.Fragment key={pp}>
            <div style={{ ...st.mHead, color: pp === pTier ? "#e4e4e7" : "#52525b" }}>{pp}</div>
            {cs.map((cc) => {
              const hit = pp === pTier && cc === cTier;
              return (
                <div
                  key={pp + cc}
                  style={{
                    ...st.mCell,
                    background: hit ? dispColor : "#1c1c1f",
                    boxShadow: hit ? `0 0 12px ${dispColor}88` : "none",
                  }}
                />
              );
            })}
          </React.Fragment>
        ))}
      </div>
    </div>
  );
}

// ---------- Styles ----------
const mono = "ui-monospace, 'SF Mono', 'Cascadia Mono', Menlo, monospace";
const sans = "-apple-system, 'Segoe UI', Roboto, Helvetica, sans-serif";

const st = {
  page: {
    minHeight: "100vh",
    background: "#101013",
    padding: "16px 12px 40px",
    fontFamily: sans,
    color: "#d4d4d8",
  },
  shell: { maxWidth: 640, margin: "0 auto" },
  header: {
    display: "flex",
    justifyContent: "space-between",
    alignItems: "flex-start",
    marginBottom: 20,
    paddingBottom: 14,
    borderBottom: "1px solid #27272a",
  },
  headerLeft: {},
  title: { fontFamily: mono, fontSize: 20, fontWeight: 700, letterSpacing: "0.12em", color: "#fafafa" },
  subtitle: { fontSize: 12, color: "#71717a", marginTop: 4 },
  headerBadge: {
    fontFamily: mono,
    fontSize: 10,
    color: "#fbbf24",
    border: "1px solid #fbbf2444",
    padding: "3px 8px",
    borderRadius: 3,
    letterSpacing: "0.1em",
    whiteSpace: "nowrap",
  },
  stateStrip: {
    display: "flex",
    gap: 4,
    marginBottom: 18,
  },
  stateCell: { flex: 1, textAlign: "center" },
  stateLamp: {
    height: 4,
    borderRadius: 2,
    marginBottom: 6,
    transition: "background 0.4s, box-shadow 0.4s",
  },
  stateLabel: { fontFamily: mono, fontSize: 8.5, letterSpacing: "0.04em" },
  inputBlock: { marginBottom: 16 },
  textarea: {
    width: "100%",
    boxSizing: "border-box",
    background: "#18181b",
    border: "1px solid #3f3f46",
    borderRadius: 6,
    color: "#e4e4e7",
    fontFamily: sans,
    fontSize: 15,
    lineHeight: 1.5,
    padding: 14,
    resize: "vertical",
    outline: "none",
  },
  buttonRow: { display: "flex", gap: 10, marginTop: 10 },
  runBtn: {
    flex: 1,
    fontFamily: mono,
    fontSize: 14,
    fontWeight: 700,
    letterSpacing: "0.1em",
    background: "#fbbf24",
    color: "#1c1917",
    border: "none",
    borderRadius: 6,
    padding: "13px 0",
  },
  resetBtn: {
    fontFamily: mono,
    fontSize: 12,
    letterSpacing: "0.08em",
    background: "transparent",
    color: "#a1a1aa",
    border: "1px solid #3f3f46",
    borderRadius: 6,
    padding: "0 16px",
    cursor: "pointer",
  },
  errorBox: {
    background: "#f8717112",
    border: "1px solid #f8717155",
    color: "#fca5a5",
    borderRadius: 6,
    padding: "10px 14px",
    fontSize: 13,
    marginBottom: 16,
  },
  intakeNote: {
    fontFamily: mono,
    fontSize: 11,
    color: "#fbbf24",
    marginBottom: 12,
    padding: "8px 12px",
    background: "#fbbf2410",
    borderRadius: 4,
  },
  card: {
    background: "#18181b",
    border: "1px solid #27272a",
    borderRadius: 8,
    padding: 18,
    marginBottom: 16,
  },
  claimCount: { fontFamily: mono, fontSize: 10, color: "#71717a", letterSpacing: "0.1em", marginBottom: 8 },
  assertion: { fontSize: 16, fontWeight: 600, color: "#fafafa", lineHeight: 1.4, marginBottom: 16 },
  tierRow: { display: "flex", gap: 12, marginBottom: 16, flexWrap: "wrap" },
  readout: {
    flex: "1 1 220px",
    background: "#101013",
    border: "1px solid #27272a",
    borderRadius: 6,
    padding: 12,
  },
  readoutAxis: { fontFamily: mono, fontSize: 9, color: "#71717a", letterSpacing: "0.12em", marginBottom: 4 },
  readoutTier: { fontFamily: mono, fontSize: 26, fontWeight: 700, lineHeight: 1 },
  readoutLabel: { fontSize: 12, color: "#d4d4d8", marginTop: 4, fontWeight: 600 },
  readoutRationale: { fontSize: 12, color: "#a1a1aa", marginTop: 6, lineHeight: 1.45 },
  matrixWrap: { display: "flex", justifyContent: "center", marginBottom: 16 },
  matrixGrid: {
    display: "grid",
    gridTemplateColumns: "auto repeat(4, 34px)",
    gap: 4,
    alignItems: "center",
  },
  mCorner: { fontFamily: mono, fontSize: 8, color: "#52525b", paddingRight: 4 },
  mHead: { fontFamily: mono, fontSize: 10, textAlign: "center" },
  mCell: {
    width: 34,
    height: 22,
    borderRadius: 3,
    transition: "background 0.5s, box-shadow 0.5s",
  },
  verdict: {
    fontSize: 14,
    fontStyle: "italic",
    color: "#d4d4d8",
    lineHeight: 1.5,
    marginBottom: 14,
    paddingLeft: 12,
    borderLeft: "2px solid #3f3f46",
  },
  disposition: {
    display: "flex",
    alignItems: "baseline",
    gap: 10,
    border: "1px solid",
    borderRadius: 6,
    padding: "10px 14px",
    marginBottom: 12,
  },
  dispWord: { fontFamily: mono, fontSize: 16, fontWeight: 700, letterSpacing: "0.1em" },
  dispDesc: { fontSize: 12, color: "#a1a1aa" },
  guidance: { fontSize: 13, color: "#d4d4d8", lineHeight: 1.5 },
  footerNote: {
    fontFamily: mono,
    fontSize: 10,
    color: "#52525b",
    lineHeight: 1.6,
    textAlign: "center",
    marginTop: 8,
    letterSpacing: "0.02em",
  },
};
