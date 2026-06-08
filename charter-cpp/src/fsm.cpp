#include "charter/fsm.h"
#include <sstream>

namespace charter {

CharterFSM::CharterFSM(const std::string& charter_version)
    : charter_version_(charter_version) {}

void CharterFSM::handshake(bool loaded_from_compression) {
    if (state_ != State::INIT)
        throw InvalidTransitionError("Handshake must be called from INIT state");
    handshake_done_ = true;
    record(State::INIT,
        "Handshake — charter: " + charter_version_ +
        ", session: " + (loaded_from_compression ? "loaded from compression" : "fresh"));
}

void CharterFSM::to_structuring(const std::string& reason) {
    validate_transition(state_, State::STRUCTURING);
    record(State::STRUCTURING, reason);
    state_ = State::STRUCTURING;
}

void CharterFSM::to_gate_check() {
    validate_transition(state_, State::GATE_CHECK);
    record(State::GATE_CHECK);
    state_ = State::GATE_CHECK;
}

void CharterFSM::to_diversify(const std::string& violated_condition) {
    validate_transition(state_, State::DIVERSIFY);
    had_prior_diversify_or_restart_ = true;
    consecutive_converge_count_ = 0;
    drift_suspected_ = false;  // DIVERSIFY satisfies the mandatory post-drift requirement
    record(State::DIVERSIFY, violated_condition);
    state_ = State::DIVERSIFY;
}

void CharterFSM::to_converge(
    const StructuredArtifact& artifact,
    const ObjectionRegister& objections)
{
    validate_transition(state_, State::CONVERGE);

    // Watchdog must fire before CONVERGE if 3 consecutive CONVERGEs occurred
    if (watchdog_report_pending_)
        throw WatchdogRequiredError();

    // CONVERGE preconditions (v2.5: "all gates" — no applicable exemption)
    if (!artifact.all_gates_pass())
        throw ConvergePreconditionError("not all gates have passed");
    if (has_open_objections(objections))
        throw ConvergePreconditionError("open objections remain unresolved");
    if (!had_prior_diversify_or_restart_)
        throw ConvergePreconditionError(
            "session trajectory must include at least one prior DIVERSIFY or RESTART");

    // If drift was suspected in the Watchdog report, DIVERSIFY is mandatory
    if (drift_suspected_)
        throw ConvergePreconditionError(
            "Watchdog assessed drift suspected — DIVERSIFY is mandatory (§3 Convergence Watchdog)");

    ++consecutive_converge_count_;
    if (consecutive_converge_count_ >= 3)
        watchdog_report_pending_ = true;

    record(State::CONVERGE);
    state_ = State::CONVERGE;
}

void CharterFSM::to_restart(const std::vector<std::string>& defect_list) {
    validate_transition(state_, State::RESTART);
    had_prior_diversify_or_restart_ = true;
    consecutive_converge_count_ = 0;
    std::string annotation = "Defects:";
    for (const auto& d : defect_list) annotation += " [" + d + "]";
    record(State::RESTART, annotation);
    state_ = State::RESTART;
}

void CharterFSM::to_output() {
    validate_transition(state_, State::OUTPUT);
    if (watchdog_report_pending_)
        throw WatchdogRequiredError();
    if (drift_suspected_)
        throw ConvergePreconditionError(
            "Watchdog drift assessment — DIVERSIFY required before OUTPUT (§3 Convergence Watchdog)");
    record(State::OUTPUT);
    state_ = State::OUTPUT;
}

void CharterFSM::to_init() {
    validate_transition(state_, State::INIT);
    if (drift_suspected_)
        throw ConvergePreconditionError(
            "Watchdog drift assessment — DIVERSIFY required before starting new claim (§3 Convergence Watchdog)");
    record(State::INIT, "new claim");
    state_ = State::INIT;
    handshake_done_ = false;
    consecutive_converge_count_ = 0;
    had_prior_diversify_or_restart_ = false;
    watchdog_report_pending_ = false;
    drift_suspected_ = false;
}

bool CharterFSM::watchdog_required() const {
    return watchdog_report_pending_;
}

void CharterFSM::submit_watchdog_report(const std::string& /*report*/, bool drift_suspected) {
    if (!watchdog_report_pending_)
        return;  // no-op if watchdog hasn't fired
    watchdog_report_pending_ = false;
    drift_suspected_ = drift_suspected;
    record(State::CONVERGE,
        "Watchdog Report submitted — drift assessment: " +
        std::string(drift_suspected ? "DRIFT SUSPECTED" : "exhausted scrutiny"));
}

void CharterFSM::validate_transition(State from, State to) const {
    if (!handshake_done_ && from != State::INIT)
        throw InvalidTransitionError("Handshake not completed");

    // Routing table — illegal transitions throw
    bool valid = false;
    switch (from) {
        case State::INIT:
            valid = (to == State::STRUCTURING);
            break;
        case State::STRUCTURING:
            valid = (to == State::GATE_CHECK || to == State::STRUCTURING);
            break;
        case State::GATE_CHECK:
            valid = (to == State::DIVERSIFY || to == State::CONVERGE || to == State::RESTART);
            break;
        case State::DIVERSIFY:
            // v2.3: DIVERSIFY → STRUCTURING only; GATE_CHECK shortcut removed
            valid = (to == State::STRUCTURING);
            break;
        case State::CONVERGE:
            valid = (to == State::OUTPUT || to == State::INIT);
            break;
        case State::RESTART:
            valid = (to == State::STRUCTURING);
            break;
        case State::OUTPUT:
            valid = (to == State::INIT || to == State::STRUCTURING);
            break;
    }

    if (!valid) {
        std::ostringstream oss;
        oss << "Invalid transition: " << to_string(from) << " → " << to_string(to);
        if (from == State::DIVERSIFY && to == State::GATE_CHECK)
            oss << " (DIVERSIFY → GATE_CHECK shortcut removed in v2.3; must return to STRUCTURING)";
        throw InvalidTransitionError(oss.str());
    }
}

void CharterFSM::record(State s, const std::string& annotation) {
    history_.emplace_back(s, annotation);
}

}  // namespace charter
