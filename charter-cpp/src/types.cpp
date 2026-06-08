#include "charter/types.h"
#include <algorithm>

namespace charter {

const char* to_string(State s) {
    switch (s) {
        case State::INIT:        return "INIT";
        case State::STRUCTURING: return "STRUCTURING";
        case State::GATE_CHECK:  return "GATE_CHECK";
        case State::DIVERSIFY:   return "DIVERSIFY";
        case State::CONVERGE:    return "CONVERGE";
        case State::RESTART:     return "RESTART";
        case State::OUTPUT:      return "OUTPUT";
    }
    return "UNKNOWN";
}

bool StructuredArtifact::all_gates_pass() const {
    for (auto g : { GateId::G1, GateId::G2, GateId::G3, GateId::G4, GateId::G5 }) {
        auto it = gate_status.find(g);
        if (it == gate_status.end() || it->second != GateStatus::PASS) return false;
    }
    return true;
}

bool StructuredArtifact::any_gate_pending() const {
    for (auto g : { GateId::G1, GateId::G2, GateId::G3, GateId::G4, GateId::G5 }) {
        auto it = gate_status.find(g);
        if (it == gate_status.end() || it->second == GateStatus::PENDING) return true;
    }
    return false;
}

bool has_open_objections(const ObjectionRegister& reg) {
    return std::any_of(reg.begin(), reg.end(),
        [](const Objection& o) { return o.status == ObjectionStatus::OPEN; });
}

int open_objection_count(const ObjectionRegister& reg) {
    return static_cast<int>(std::count_if(reg.begin(), reg.end(),
        [](const Objection& o) { return o.status == ObjectionStatus::OPEN; }));
}

bool StateCompression::is_valid() const {
    return missing_structural_fields().empty();
}

std::vector<std::string> StateCompression::missing_structural_fields() const {
    std::vector<std::string> missing;
    if (gate_status.empty())
        missing.push_back("gate_status");
    // objection_register may legitimately be empty for fresh artifacts;
    // we check that it was explicitly set by checking charter_version is populated
    // (a compression that was properly produced will always have charter_version)
    if (charter_version.empty())
        missing.push_back("charter_version (proxy for structural completeness)");
    // constraint_health: zero-valued struct is ambiguous — production should use optional
    // adversarial_anchor: watchdog_fired=false is a valid state, so we can't detect absence
    // TODO: wrap structural fields in std::optional in production to allow proper validation
    return missing;
}

}  // namespace charter
