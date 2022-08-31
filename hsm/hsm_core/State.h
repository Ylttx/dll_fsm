#ifndef STATE_H
#define STATE_H
#include "Input.h"
#include "Context.h"
#include <functional>
#include <chrono>

namespace app {
class Machine;
}

namespace hsm {

class State {
    friend class Context;
    using FuncType = std::function<int(const Input &)>;
public:
    State();
    virtual ~State() {}

    virtual void enter(void);
    virtual void exit(void) {}
    virtual void update(void) {}

protected:
    void setContext(Context *context);
    void setMachine(app::Machine *machine);
    void setInputHandle(FuncType func);
 
    int sendSyncInput(const Input &input);
    void transfer(int state);

    bool isTimeOut(int64_t timeout);

    app::Machine *m_machine;
 
private:
    FuncType m_func;
    Context *m_context;
    std::chrono::steady_clock::time_point m_start;
};

} // namespace hsm

#endif