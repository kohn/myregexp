#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "ParseTreeNode.h"
#include "State.h"
#include <string>
class Automata
{
private:
    // each automata has at least a start state and an end state
    State* start_state;
    State* end_state;
     
public:
    Automata();
    // concat two automata by linking end state of the first and start
    // state of the second
    State* s_state(){return start_state;}
    State* e_state(){return end_state;}
    // used to debug
    void print();
    int accept(std::string s);
    virtual ~Automata();
};
#endif
