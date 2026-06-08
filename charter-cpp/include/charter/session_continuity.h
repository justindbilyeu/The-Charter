#pragma once

#include "types.h"
#include <string>
#include <vector>

namespace charter {

// ---------------------------------------------------------------------------
// Session Continuity Protocol (§9)
//
// Manages State Compression: serialization, deserialization (five-step
// procedure, v2.4), trigger detection, and the structural/orientational
// field validation (v2.5).
// ---------------------------------------------------------------------------

class SessionContinuity {
public:
    // Serialize session state to a portable string (JSON in production;
    // simple key-value format in this skeleton).
    // TODO: replace with nlohmann/json in production build.
    std::string compress(
        const StructuredArtifact& artifact,
        const ObjectionRegister& objections,
        const ConstraintHealth& health,
        const AdversarialAnchor& anchor,
        const std::string& next_step,
        const std::vector<std::string>& assumptions_modified,
        const std::string& charter_version = "v2.7") const;

    // ---------------------------------------------------------------------------
    // Five-step deserialization procedure (v2.4 / v2.5)
    //
    // Before any new work when loading a State Compression:
    //   Step 1. Declare loaded charter version; note diff if differs from current.
    //   Step 2. Confirm gate status for each open artifact.
    //   Step 3. Load open objections into register.
    //   Step 4. State the single next step.
    //   Step 5. Load Constraint Health and Adversarial Anchor status.
    //
    // v2.5: if structural fields are missing, this is an INVALID HANDOFF.
    //   Operator must: supply missing fields | grant explicit waiver | treat as fresh session.
    // ---------------------------------------------------------------------------

    enum class HandoffAction {
        SUPPLY_MISSING_FIELDS,
        GRANT_EXPLICIT_WAIVER,
        TREAT_AS_FRESH_SESSION
    };

    struct DeserializationResult {
        bool valid;                                     // all structural fields present
        std::vector<std::string> missing_structural;    // empty if valid
        std::string charter_version_delta;              // non-empty if version differs
        StateCompression compression;
        std::string deserialization_log;               // human-readable five-step trace
    };

    DeserializationResult deserialize(
        const std::string& serialized,
        const std::string& current_charter_version = "v2.7") const;

    // Produce a fresh empty StateCompression for new sessions
    static StateCompression fresh_session(const std::string& charter_version = "v2.7");

    // ---------------------------------------------------------------------------
    // Trigger condition detection (§9)
    // ---------------------------------------------------------------------------

    // Topic shift: primary claim/artifact/objective changed to a different one
    // (exploring a new aspect of the same claim does NOT qualify)
    bool is_topic_shift(
        const StructuredArtifact& prev,
        const StructuredArtifact& current) const;

    // Milestone: gate status changed, artifact completed, or test spec finalized
    bool is_milestone(
        const StructuredArtifact& before,
        const StructuredArtifact& after) const;

    // Elevated complexity: >= 2 active artifacts/claims/objections tracked
    // simultaneously without a State Compression since the earliest was opened
    bool is_elevated_complexity(
        const std::vector<StructuredArtifact>& active_artifacts,
        const ObjectionRegister& objections,
        std::chrono::system_clock::time_point last_compression_time) const;

private:
    // Number of concurrent items that constitutes "elevated complexity" (§9)
    static constexpr int COMPLEXITY_THRESHOLD = 2;
};

}  // namespace charter
