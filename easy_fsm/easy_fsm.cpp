#include <iostream>
#include <thread>
using namespace std;

enum StateType {
    ST_STOPPED,     // 停机
    ST_STARTING,    // 启动中
    ST_RUNNING,     // 运行
    ST_STOPPING,    // 停机中
    ST_ERROR,       // 故障
    ST_END
};

class EasyFSM {
public:
    EasyFSM() : m_state(ST_STOPPED) {
        m_state = false;
    }

    void run(void) {
        while (true) {
            switch (m_state)
            {
            case ST_STOPPED:
                cout << "I am stopped" << endl;
                if (m_input == 1)
                    m_state = ST_STARTING;
                else if (m_input == 7)
                    m_state = ST_ERROR;
                break;
            case ST_STARTING:
                cout << "I am starting" << endl;
                if (m_input == 2)
                    m_state = ST_RUNNING;
                else if (m_input == 3)
                    m_state = ST_STOPPING;
                break;
            case ST_RUNNING:
                cout << "I am running" << endl;
                if (m_input == 4)
                    m_state = ST_STOPPING;
                break;
            case ST_STOPPING:
                cout << "I am stopping" << endl;
                if (m_input == 5)
                    m_state = ST_STOPPED;
                else if (m_input == 6)
                    m_state = ST_ERROR;
                break;
            case ST_ERROR:
                cout << "I am error" << endl;
                if (m_input == 8)
                    m_state = ST_STOPPED;
                break;
            default:
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }

    void set_input(int in) { m_input = in; }

private:
    int m_state;
    int m_input;
};


int main(void) {
    EasyFSM fsm;

    auto t = std::thread(&EasyFSM::run, &fsm);

    int in = 0;
    while (cin >> in) {
        fsm.set_input(in);
    }

    return 0;
}