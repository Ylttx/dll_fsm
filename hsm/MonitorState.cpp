#include "MonitorState.h"
#include "Machine.h"
#include <iostream>
using namespace std;

namespace hsm {
 
enum InputType {
    IT_START = 1,
    IT_STOP,
    IT_END
};

StoppedState::StoppedState() {
    auto func = std::bind(&StoppedState::handleInput, this, std::placeholders::_1);
    setInputHandle(func);
}

void StoppedState::enter(void) {
    State::enter();
    cout << "enter stopped state" << endl;
}

void StoppedState::exit(void) {
    State::exit();
    cout << "exit stopped state" << endl;
}

void StoppedState::update(void) {
    State::update();
    if (m_machine->isError()) {
        cout << "T7: check error" << endl;
        transfer(StateType::ST_ERROR);
    }
}

int StoppedState::handleInput(const Input &input) {
    if (input.getType() == InputType::IT_START) {
        cout << "T1: recieve start input." << endl;
        transfer(StateType::ST_STARTING);
    }
    return 0;
}

void StartingState::enter(void) {
    State::enter();
    cout << "enter starting state" << endl;
    m_machine->start();
}

void StartingState::exit(void) {
    State::exit();
    cout << "exit starting state" << endl;
}

void StartingState::update(void) {
    State::update();
    if (m_machine->isRunning()) {
        cout << "T2: check running" << endl;
        transfer(StateType::ST_RUNNING);
    } else if (isTimeOut(3)) {
        cout << "T3: start failed 3s!" << endl;
        transfer(StateType::ST_STOPPING);
    }
}

RunningState::RunningState() {
    auto func = std::bind(&RunningState::handleInput, this, std::placeholders::_1);
    setInputHandle(func);
}

void RunningState::enter(void) {
    State::enter();
    cout << "enter running state" << endl;
    m_machine->start();
}

void RunningState::exit(void) {
    State::exit();
    cout << "exit running state" << endl;
}

void RunningState::update(void) {
    State::update();
    if (m_machine->isError()) {
        cout << "T4: check error" << endl;
        transfer(StateType::ST_STOPPING);
    }
}

int RunningState::handleInput(const Input &input) {
    if (input.getType() == InputType::IT_STOP) {
        cout << "T4: stop command" << endl;
        transfer(StateType::ST_STOPPING);
    }

    return 0;
}

void StoppingState::enter(void) {
    State::enter();
    cout << "enter stopping state" << endl;
    m_machine->stop();
}

void StoppingState::exit(void) {
    State::exit();
    cout << "exit stopping state" << endl;
}

void StoppingState::update(void) {
    State::update();
    if (!m_machine->isRunning()) {
        if (m_machine->isError()) {
            cout << "T6: check error" << endl;
            transfer(StateType::ST_ERROR);
        } else {
            cout << "T5: stop done" << endl;
            transfer(StateType::ST_STOPPED);
        }
    }
}

void ErrorState::enter(void) {
    State::enter();
    cout << "enter error state" << endl;
    m_machine->start();
}

void ErrorState::exit(void) {
    State::exit();
    cout << "exit error state" << endl;
}

void ErrorState::update(void) {
    State::update();
    if (!m_machine->isError()) {
        cout << "T8: check no error" << endl;
        transfer(StateType::ST_STOPPED);
    }
}

} // namespace hsm