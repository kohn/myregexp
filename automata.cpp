#include "Automata.h"
#include "State.h"
#include <string>
#include <stack>

Automata::Automata(){
    start_state = new State(TYPE_START);
    end_state = new State(TYPE_END);
}

Automata::~Automata(){
    delete start_state;
    delete end_state;
}

void Automata::print(){
    start_state->print(0);
}


int Automata::accept(std::string s){
    std::stack<State*> s1;
    std::stack<State*> s2;

    std::stack<State*> *sta1 = &s1;
    std::stack<State*> *sta2 = &s2;

    sta1->push(start_state);
    start_state->next_epsilong_state(*sta1);

    int len = s.length();
    for(int i=0; i<len; i++){
        while(!sta1->empty()){
            State* top_state = sta1->top();
            sta1->pop();
            top_state->next_state(EPSILON, *sta2);
            top_state->next_state(s[i], *sta2);
        }
        std::stack<State*> *tmp = sta1;
        sta1 = sta2;
        sta2 = tmp;
    }

    while(!sta1->empty()){
        State* top = sta1->top();
        sta1->pop();
        if(top->is_end_state())
            return 1;
    }
    return 0;
}
