#include "Context.h"
#include "State.h"
#include <assert.h>

namespace hsm {
 
Context::~Context() {
    if (m_cur_ns.m_state) {
        m_cur_ns.m_state->exit();
    }

    for (auto item : m_states) {
        if (item.second.m_state) {
            delete item.second.m_state;
            item.second.m_state = nullptr;
        }
    }

    m_states.clear();
}

State *Context::createState(State *p_state, int state, app::Machine *machine) {
    if (!p_state || !machine) {
        return nullptr;
    }

    p_state->setContext(this);
    p_state->setMachine(machine);

    NodeState ns(p_state);
    m_states[state] = ns;
 
    return p_state;
}

void Context::start(int state) {
    auto it = m_states.find(state);
    assert(it != m_states.end() && it->second.m_state != nullptr);
    m_cur_state = state;
    m_cur_ns = it->second;
    m_cur_ns.m_state->enter();
}

void Context::update(void) {
    m_cur_ns.m_state->update();
}

void Context::transferState(int state) {
    auto it = m_states.find(state);
 
    if (it != m_states.end()) {
        m_cur_ns.m_state->exit();
        m_cur_ns = it->second;
        m_cur_ns.m_state->enter();
    }
}

void Context::sendSyncInput(const Input &input) {
    m_cur_ns.m_state->sendSyncInput(input);
}

int Context::getCurrentState(void) {
    return m_cur_state;
}

} // namespace hsm