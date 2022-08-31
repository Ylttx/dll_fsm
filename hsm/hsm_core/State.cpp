#include "State.h"

namespace hsm {

State::State() : m_func(nullptr), m_context(nullptr) {}

void State::enter(void) {
    m_start = std::chrono::steady_clock::now();
}

void State::setContext(Context *context)  {
    m_context = context;
}

void State::setMachine(app::Machine *machine) {
    m_machine = machine;
}

void State::setInputHandle(FuncType func) {
    m_func = func;
}

int State::sendSyncInput(const Input &input) {
    if (m_func) {
        return m_func(input);
    }

    return 0;
}

void State::transfer(int state) {
    if (m_context) {
        m_context->transferState(state);
    }
}

bool State::isTimeOut(int64_t timeout) {
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - m_start);
    return seconds.count() >= timeout;
}

} // namespace hsm