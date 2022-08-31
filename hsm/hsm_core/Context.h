#ifndef CONTEXT_H
#define CONTEXT_H
#include <unordered_map>
#include "Input.h"

namespace app {
class Machine;
}

namespace hsm {

class State;

struct NodeState {
    NodeState(State *state = nullptr) : m_state(state) {}
 
    NodeState &operator=(const NodeState &rhs) {
        m_state = rhs.m_state;
        return *this;
    }

    State *m_state;
};

class Context {
 
public:
    Context() {}
    ~Context();

    State *createState(State *p_state, int state, app::Machine *machine);

    void start(int state);

    void update(void);

    void transferState(int state);
 
    void sendSyncInput(const Input &input);

    int getCurrentState(void);

private:
    std::unordered_map<int, NodeState> m_states;
    NodeState m_cur_ns;
    int m_cur_state;
};

} // namespace hsm

#endif