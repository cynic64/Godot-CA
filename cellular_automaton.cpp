#include <iostream>
#include <cstdlib>
#include "cellular_automaton.h"

CellularAutomaton::CellularAutomaton(int width, int height) {
    // creates 2d vector of correct size and fills it with false.
    array_size_y = height;
    array_size_x = width;

    fill_array();
    generate_offsets();
}

void CellularAutomaton::update() {
    // updates the simulation
    int neighbors;
    bool current_state;

    for (int y = 0; y < array_size_y; y++) {
        for (int x = 0; x < array_size_x; x++) {
            current_state = current_states[y][x];
            neighbors = check_neighbors(x, y);
            next_states[y][x] = get_new_state(current_state, neighbors);
        }
    }

    next_to_current();
}

int CellularAutomaton::check_neighbors(int x, int y) {
    // checks how may neighbors the cell at (x, y) has.

    int total = 0;
    int new_x, new_y;
    for (int i = 0; i < offsets.size(); i++) {
        // get new coordinates
        new_x = x + offsets[i][0];
        new_y = y + offsets[i][1];

        // make sure they aren't out-of-bounds
        if (new_x >= 0 && new_x < array_size_x && new_y >= 0 && new_y < array_size_y) {
            if (current_states[new_y][new_x]) {
                total += 1;
            }
        }
    }

    return total;
}

bool CellularAutomaton::get_new_state(bool current, int neighbor_count) {
    // returns what state a cell should be in next.
    if (current) {
        // if it's currently alive
        if (neighbor_count >= min_survival && neighbor_count <= max_survival) {
            // it gets to live
            return true;
        }
        else {
            // DIE
            return false;
        }
    }
    else {
        // it's currently dead
        if (neighbor_count >= min_birth && neighbor_count <= max_birth) {
            // it lives!
            return true;
        }
        else {
            // stay dead
            return false;
        }
    }
}

void CellularAutomaton::next_to_current() {
    // copies next_states to current_states
    current_states = next_states;
}

void CellularAutomaton::generate_offsets() {
    // generates coordinate offsets to check for neighbors.
    // currently set to generate Moore neighborhoods.
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) {
                // 0, 0 isn't a valid offset
                continue;
            }
            else {
                offsets.push_back( { x, y } );
            }
        }
    }
}

void CellularAutomaton::fill_array() {
    // fills arrays with false, and resizes them.

    vector < bool > line = { };

    for (int i = 0; i < array_size_x; i++) {
        line.push_back(false);
    }

    for (int i = 0; i < array_size_y; i++) {
        current_states.push_back(line);
        next_states.push_back(line);
    }
}

void CellularAutomaton::randomize_state(int size) {
    // randomizes a centered square of tiles (side length size)
    int x_corner = array_size_x / 2 - size / 2;
    int y_corner = array_size_y / 2 - size / 2;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            current_states[y+y_corner][x+x_corner] = (bool) (rand() % 2);
        }
    }
}

void CellularAutomaton::set_cell(int x, int y, bool state) {
    current_states[y][x] = state;
}

void CellularAutomaton::print_array() {
    // prints array nicely
    bool cell;

    for (int y = 0; y < array_size_y; y++) {
        for (int x = 0; x < array_size_x; x++) {
            cell = current_states[y][x];
            if (cell) {
                std::cout << "# ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
