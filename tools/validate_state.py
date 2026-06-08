#!/usr/bin/env python3
"""
Validates for-humans/STATE.md against the expected State Compression structure.

Usage:
    python tools/validate_state.py                  # validates for-humans/STATE.md
    python tools/validate_state.py path/to/STATE.md # validates a specific file

Exits 0 on success, 1 on any validation failure.
Can be used as a pre-commit hook or CI step.
"""

import sys
from pathlib import Path

REQUIRED_HEADER_FIELDS = [
    "**Charter version:**",
    "**Last updated:**",
    "**Updated by:**",
]

REQUIRED_SECTIONS = [
    "## Gate Status — Open Artifacts",
    "## Objection Register",
    "## Constraint Health",
    "## Adversarial Anchor",
    "## Active Claims and Evidence Levels",
    "## Decisions Made This Session",
    "## Next Step",
    "## Assumptions Modified This Session",
    "## Skeptical Residue",
]

# Fields required within the Constraint Health section
CONSTRAINT_HEALTH_FIELDS = [
    "**Open objection count:**",
    "**Consecutive CONVERGE count:**",
    "**Watchdog fired this session:**",
    "**Drift assessment:**",
]

# Fields required within the Adversarial Anchor section
ADVERSARIAL_ANCHOR_FIELDS = [
    "Watchdog fired:",
    "Drift assessment:",
]


def extract_section(lines: list[str], heading: str) -> list[str]:
    """Return lines belonging to the section starting at heading, stopping at the next ## heading."""
    inside = False
    result = []
    for line in lines:
        if line.rstrip() == heading:
            inside = True
            continue
        if inside:
            if line.startswith("## "):
                break
            result.append(line)
    return result


def validate(path: Path) -> list[str]:
    if not path.exists():
        return [f"File not found: {path}"]

    text = path.read_text(encoding="utf-8")
    lines = text.splitlines()
    errors = []

    # Header fields — expected in the first ~10 lines
    header_lines = lines[:10]
    for field in REQUIRED_HEADER_FIELDS:
        if not any(field in line for line in header_lines):
            errors.append(f"Missing header field: {field}")

    # Required sections
    for section in REQUIRED_SECTIONS:
        if not any(line.rstrip() == section for line in lines):
            errors.append(f"Missing section: {section}")

    # Constraint Health — required sub-fields
    ch_lines = extract_section(lines, "## Constraint Health")
    for field in CONSTRAINT_HEALTH_FIELDS:
        if not any(field in line for line in ch_lines):
            errors.append(f"Constraint Health missing field: {field}")

    # Adversarial Anchor — required sub-fields
    aa_lines = extract_section(lines, "## Adversarial Anchor")
    for field in ADVERSARIAL_ANCHOR_FIELDS:
        if not any(field in line for line in aa_lines):
            errors.append(f"Adversarial Anchor missing field: {field}")

    # Next Step — must carry the required label (enforces the "single, specific" discipline)
    ns_lines = extract_section(lines, "## Next Step")
    if not any("**Single, specific, actionable:**" in line for line in ns_lines):
        errors.append("Next Step section missing '**Single, specific, actionable:**' label")

    # Decisions Made — must have the table header row
    dm_lines = extract_section(lines, "## Decisions Made This Session")
    has_table_header = any(
        "| Decision |" in line and "| Reasoning |" in line and "| Session |" in line
        for line in dm_lines
    )
    if not has_table_header:
        errors.append(
            "Decisions Made This Session missing table header: | Decision | Reasoning | Session |"
        )

    return errors


def main() -> None:
    if len(sys.argv) > 1:
        path = Path(sys.argv[1])
    else:
        path = Path(__file__).parent.parent / "for-humans" / "STATE.md"

    errors = validate(path)

    if errors:
        print(f"STATE.md validation FAILED — {len(errors)} error(s) in {path}:")
        for error in errors:
            print(f"  - {error}")
        sys.exit(1)
    else:
        print(f"STATE.md OK — {path}")


if __name__ == "__main__":
    main()
