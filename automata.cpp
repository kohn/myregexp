#include "Automata.h"
#include "State.h"
Automata::Automata(){
    start_state = new State(TYPE_START);
    end_state = new State(TYPE_END);
}

Automata::~Automata(){
    delete start_state;
    delete end_state;
}

void Automata::concat(Automata* next){
    end_state->add_edge(0, next->start_state);
    end_state = next->end_state;
}


void Automata::add_state(State* last, char ch, State* next){
    last->add_edge(ch, next);
}

void Automata::print(){
    start_state->print(0);
}
