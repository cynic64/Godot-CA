#ifndef cellular_automaton_h_INCLUDED
#define cellular_automaton_h_INCLUDED

#include <vector>
using namespace std;

class CellularAutomaton
{
    public:
        CellularAutomaton(int width, int height);
        void update();
        void fill_array();
        void print_array();
        void set_cell(int x, int y, bool state);
        void randomize_state(int size);
        int check_neighbors(int x, int y);
        // rules (move this to a struct later?)
        int min_survival;
        int max_survival;
        int min_birth;
        int max_birth;

    private:
        void generate_offsets();
        void next_to_current();
        bool get_new_state(bool current, int neighbor_count);
        // struct for this?
        int array_size_x;
        int array_size_y;
        vector < vector < bool > > current_states;
        vector < vector < bool > > next_states;
        vector < vector < int> > offsets;
};

#endif // cellular_automaton_h_INCLUDED

