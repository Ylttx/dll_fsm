#include "Machine.h"
#include "Factory.h"
#include <unistd.h>

namespace app {

Machine::Machine() {
    using namespace hsm;

    m_state = 0;
    m_error = false;
 
    m_context = new Context();
    Factory::createState(this, m_context, StateType::ST_STOPPED);
    Factory::createState(this, m_context, StateType::ST_STARTING);
    Factory::createState(this, m_context, StateType::ST_RUNNING);
    Factory::createState(this, m_context, StateType::ST_STOPPING);
    Factory::createState(this, m_context, StateType::ST_ERROR);

    m_context->start(StateType::ST_STOPPED);
}

Machine::~Machine() {
    if (m_context) {
        delete m_context;
        m_context = nullptr;
    }
}

void Machine::run(void) {
    static int error = 0;

    while (true) {
        m_context->update();

        if (!m_inputs.empty()) {
            hsm::Input input(m_inputs.front());
            m_inputs.pop();
            m_context->sendSyncInput(input);
        }

        if (++error % 10 == 0) {
            error = 0;
            setError(true);
        } else {
            setError(false);
        }

        sleep(1);
    }
}

} // namespace app