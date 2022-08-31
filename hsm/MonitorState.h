#include "State.h"

namespace hsm {

enum StateType {
    ST_STOPPED,     // 停机
    ST_STARTING,    // 启动中
    ST_RUNNING,     // 运行
    ST_STOPPING,    // 停机中
    ST_ERROR,       // 故障
    ST_END
};

class StoppedState : public State {
public:
    StoppedState();
 
    void enter(void) override;
    void exit(void) override;
    void update(void) override;

private:
    int handleInput(const Input &input);
};

class StartingState : public State {
public:
    void enter(void) override;
    void exit(void) override;
    void update(void) override;
};

class RunningState : public State {
public:
    RunningState();
 
    void enter(void) override;
    void exit(void) override;
    void update(void) override;

private:
    int handleInput(const Input &input);
};

class StoppingState : public State {
public:
    void enter(void) override;
    void exit(void) override;
    void update(void) override;
};

class ErrorState : public State {
public:
    void enter(void) override;
    void exit(void) override;
    void update(void) override;
};

} // namespace hsm