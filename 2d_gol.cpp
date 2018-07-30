/*
 * Prints a series of states from a 1D cellular automaton simulation.
 */


#include <stdio.h>
#include <iostream>
#include <vector>
// for rand()
#include <cstdlib>
// for writing to files
#include <fstream>

using namespace std;

#define ARRAY_SIZE 95
#define FILENAME "/home/void/stuff/godot/C++ Terrain reader/tfiles/sierpinski"

// initialize arrays - we need 2 to store the future state as well as the current one
bool current_states[ARRAY_SIZE][ARRAY_SIZE];
bool new_states[ARRAY_SIZE][ARRAY_SIZE];

// for checking whether neighboring cells are alive
const int offsets[8][2] = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };
// rules for the CA
const int min_birth = 3;
const int max_birth = 3;
const int min_survival = 2;
const int max_survival = 3;

// output file
ofstream OUTFILE;

// Prototypes
void update_array();
int get_neighbor_count(int y, int x);
void print_array();
void setup_array();
void print_item_at(int y, int x);
void write_array_to_file(int frame_num);

int main()
{
    // open file and state array size
    OUTFILE.open(FILENAME);
    // OUTFILE << ARRAY_SIZE << '\n';

    // set initial state
    setup_array();

    // write first frame to file
    write_array_to_file(0);

    for (int i = 1; i < ARRAY_SIZE; i++) {
        update_array();
        write_array_to_file(i);
    }

    OUTFILE.close();
    return 0;
}

void setup_array() {
    // fill center cell and nothing else
    // current_states[ARRAY_SIZE / 2][ARRAY_SIZE / 2] = 1;

    // random fill
    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            current_states[y][x] = rand() % 2;
        }
    }

    // random fill 7x7 at center
    // int size = 7;
    // int corner = ARRAY_SIZE / 2 - size / 2;
    // int ny, nx;

    // for (int y = 0; y < size; y++) {
        // for (int x = 0; x < size; x++) {
            // ny = y + corner;
            // nx = x + corner;
            // current_states[ny][nx] = rand() % 2;
        // }
    // }
}

void update_array() {
    int neighbor_count;
    bool current_state;

    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            neighbor_count = get_neighbor_count(y, x);
            current_state = current_states[y][x];

            // check for survival
            if (current_state) {
                if (neighbor_count >= min_survival && neighbor_count <= max_survival) {
                    new_states[y][x] = true;
                }
                else {
                    new_states[y][x] = false;
                }
            }

            // check for birth
            else {
                if (neighbor_count >= min_birth && neighbor_count <= max_birth) {
                    new_states[y][x] = true;
                }
                else {
                    new_states[y][x] = false;
                }
            }
        }
    }

    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            current_states[y][x] = new_states[y][x];
        }
    }
}

int get_neighbor_count(int y, int x) {
    int total = 0;

    for (int i = 0; i < 8; i++) {
        // Calculate position to check neighbor for
        int new_y = offsets[i][0] + y;
        int new_x = offsets[i][1] + x;

        // Make sure it's not out-of-bounds
        if (new_y >= 0 && new_y < ARRAY_SIZE && new_x >= 0 && new_x < ARRAY_SIZE) {
            if (current_states[new_y][new_x]) {
                total++;
            }
        }
    }

    return total;
}

void print_array() {
    // Prints current_states nicely.

    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            print_item_at(y, x);
        }
        printf("\n");
    }
    printf("\n");
}

void write_array_to_file(int frame_num) {
    // Writes current_states to file in a way readable to my godot program:
    // 1's and 0's, and a number preceded by an f to show frame number.

    OUTFILE << 'f' << frame_num << '\n';

    for (int y = 0; y < ARRAY_SIZE; y++) {
        for (int x = 0; x < ARRAY_SIZE; x++) {
            OUTFILE << (int) current_states[y][x];

            // put dots inbetween cells for easier parsing, but not at end.
            // if (x != ARRAY_SIZE - 1) {
                // OUTFILE << '.';
            // }
        }
        OUTFILE << '\n';
    }
}

void print_item_at(int y, int x) {
    printf("%c", current_states[y][x]? '#' : '.');
}
