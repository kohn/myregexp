#ifndef STATE_H
#define STATE_H
#include <map>
#include <vector>
#include <stack>
#include <iostream>

enum StateType{TYPE_START, TYPE_NORMAL, TYPE_END};
#define EPSILON 0
#define ANY 1

class State{
private:
    std::map<char, State*> ch_state_map;
    std::vector<State*> epsilon_jump_vec;
    StateType type;
    State* accept_any_char;
    int printed;
public:
    State(StateType t){type = t; printed = 0; accept_any_char=NULL;}
    void add_edge(char ch, State* next);
    void print(int indent);
    int next_state(char ch, std::stack<State*> &s);
    int next_epsilong_state(std::stack<State*> &s);
    inline void set_normal_type(){type = TYPE_NORMAL;}
    inline int is_end_state(){return type == TYPE_END;}
};
#endif
