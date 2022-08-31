#include "Machine.h"
#include <thread>
#include <iostream>

using namespace std;

int main(void) {
    app::Machine machine;

    auto t = thread(&app::Machine::run, &machine);
    t.detach();

    int in = 0;
    cout << "Please input: 1 - Start, 2 - Stop." << endl;
    while (cin >> in) {
        if (in <= 2) {
            machine.getInput(in);
        }
    }

    return 0;
}