#pragma once

#include "types.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace charter {

// ---------------------------------------------------------------------------
// Charter FSM
//
// Enforces all routing rules from the charter. Illegal transitions throw.
// The FSM does not make semantic decisions — it enforces the consequences
// of decisions made by the CoherenceController and HardGates.
//
// Valid transitions (v2.3/v2.4/v2.5):
//   INIT        → STRUCTURING
//   STRUCTURING → GATE_CHECK, STRUCTURING (self-loop)
//   GATE_CHECK  → DIVERSIFY, CONVERGE, RESTART
//   DIVERSIFY   → STRUCTURING              (NOT → GATE_CHECK — v2.3 routing fix)
//   CONVERGE    → OUTPUT, INIT
//   RESTART     → STRUCTURING
//   OUTPUT      → INIT, STRUCTURING
// ---------------------------------------------------------------------------

class InvalidTransitionError : public std::logic_error {
public:
    explicit InvalidTransitionError(const std::string& msg)
        : std::logic_error(msg) {}
};

class WatchdogRequiredError : public std::logic_error {
public:
    explicit WatchdogRequiredError()
        : std::logic_error(
            "Watchdog Report required before next CONVERGE "
            "(3 consecutive CONVERGEs — §3 Convergence Watchdog)") {}
};

class ConvergePreconditionError : public std::logic_error {
public:
    explicit ConvergePreconditionError(const std::string& reason)
        : std::logic_error("CONVERGE precondition not met: " + reason) {}
};

class DiversifyIncompleteError : public std::logic_error {
public:
    explicit DiversifyIncompleteError()
        : std::logic_error(
            "DIVERSIFY exit blocked: completion criteria not met — "
            "call declare_diversify_complete() after CoherenceController::check_diversify_complete() "
            "confirms (a) new competing hypothesis, (b) new substantive objection, "
            "(c) artifact revised or justified (v2.5 DIVERSIFY exit criterion)") {}
};

class CharterFSM {
public:
    explicit CharterFSM(const std::string& charter_version = "v2.7");

    State current_state() const { return state_; }
    int consecutive_converge_count() const { return consecutive_converge_count_; }
    bool had_prior_diversify_or_restart() const { return had_prior_diversify_or_restart_; }

    // Handshake (§ Communication Hooks + v2.4 G-01)
    // Must be called before any other transition. Sets up session context.
    void handshake(bool loaded_from_compression = false);

    // Transitions — enforce charter routing rules
    void to_structuring(const std::string& reason = "");
    void to_gate_check();
    void to_diversify(const std::string& violated_condition);
    void to_converge(
        const StructuredArtifact& artifact,
        const ObjectionRegister& objections);  // validates preconditions
    void to_restart(const std::vector<std::string>& defect_list);
    void to_output();
    void to_init();

    // Convergence Watchdog (§3 v2.4)
    // Returns true if 3 consecutive CONVERGEs have occurred without a report
    bool watchdog_required() const;

    // Must be called before to_converge() when watchdog_required() is true
    // drift_suspected: if true, DIVERSIFY is mandatory regardless of standard conditions
    void submit_watchdog_report(const std::string& report, bool drift_suspected);

    // DIVERSIFY exit gate (v2.5 completion criterion)
    // Call after CoherenceController::check_diversify_complete() returns complete = true.
    // to_structuring() from DIVERSIFY state throws DiversifyIncompleteError unless this
    // has been called since the most recent to_diversify().
    void declare_diversify_complete();

    // Session history — for Watchdog and simulation review
    const std::vector<std::pair<State, std::string>>& history() const { return history_; }

private:
    State state_ = State::INIT;
    std::string charter_version_;
    bool handshake_done_ = false;

    // Watchdog state
    int consecutive_converge_count_ = 0;
    bool watchdog_report_pending_ = false;
    bool drift_suspected_ = false;

    // CONVERGE precondition: at least one prior DIVERSIFY or RESTART in session
    bool had_prior_diversify_or_restart_ = false;

    // DIVERSIFY exit gate: must be declared complete before to_structuring() from DIVERSIFY
    bool diversify_complete_declared_ = false;

    std::vector<std::pair<State, std::string>> history_;

    void validate_transition(State from, State to) const;
    void record(State s, const std::string& annotation = "");
};

}  // namespace charter
