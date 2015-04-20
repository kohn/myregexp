#ifndef STATE_H
#define STATE_H
#include <vector>
#include <map>
enum StateType{TYPE_START, TYPE_NORMAL, TYPE_END};
#define EPSILON 0
#define ANY 1

class State{
private:
    std::map<char, State*> ch_state_map;
    std::vector<State*> epsilon_jump_vec;
    StateType type;
    int printed;
public:
    State(StateType t){type = t; printed = 0;}
    void add_edge(char ch, State* next);
    void print(int indent);
};
#endif
