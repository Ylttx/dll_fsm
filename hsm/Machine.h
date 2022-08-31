#ifndef MACHINE_H
#define MACHINE_H
#include <queue>

namespace hsm {
class Context;
}

namespace app {

class Machine
{
public:
    Machine();
    virtual ~Machine();

    bool isError(void) { return m_error; }
    bool isRunning(void) { return m_state == 1; }

    void start(void) { m_state = 1; }
    void stop(void) { m_state = 0; }

    void setError(bool err) { m_error = err; }
    void getInput(int in) { m_inputs.push(in); }

    void run(void);

private:
    hsm::Context *m_context;

    int m_state; // 0:关机 1:运行
    bool m_error; // 故障

    std::queue<int> m_inputs;
};

} // namespace app

#endif // MACHINE_H