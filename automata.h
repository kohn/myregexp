#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "ParseTreeNode.h"
#include "State.h"
class Automata
{
private:
    State* start_state;
    State* end_state;
     
public:
    Automata();
    void concat(Automata* next);
    void add_state(State* last, char ch, State* next);
    State* s_state(){return start_state;}
    State* e_state(){return end_state;}
    void print();
    virtual ~Automata();
};
#endif
