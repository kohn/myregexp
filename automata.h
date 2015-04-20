#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "ParseTreeNode.h"
#include "State.h"
#include <string>
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
    int accept(std::string s);
    virtual ~Automata();
};
#endif
