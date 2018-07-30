#include <iostream>
#include "cellular_automaton.h"

int main() {
    CellularAutomaton ca (95, 65);

    ca.min_birth = 3;
    ca.max_birth = 3;
    ca.min_survival= 2;
    ca.max_survival= 3;
    ca.randomize_state(7);
    ca.print_array();

    for (int i = 0; i < 1000; i++) {
        std::cout << std::endl;
        ca.update();
        ca.print_array();
    }

    return 0;
}
