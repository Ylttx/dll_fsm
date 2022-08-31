#ifndef FACTORY_H
#define FACTORY_H
#include "MonitorState.h"

namespace app {
class Machine;
}

namespace hsm {

class Factory {
public:
    static State* createState(app::Machine *machine, Context *context, int state) {
        if (!machine || !context) {
            return nullptr;
        }

        State *p_state = nullptr;
        
        switch (state)
        {
        case StateType::ST_STOPPED: p_state = new StoppedState(); break;
        case StateType::ST_STARTING: p_state = new StartingState(); break;
        case StateType::ST_RUNNING: p_state = new RunningState(); break;
        case StateType::ST_STOPPING: p_state = new StoppingState(); break;
        case StateType::ST_ERROR: p_state = new ErrorState(); break;
        default: break;
        }

        return context->createState(p_state, state, machine);
    }
};
} // namespace hsm

#endif // FACTORY_H