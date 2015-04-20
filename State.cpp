#include "State.h"
#include <iostream>
#include <map>
#include <vector>
#include <stack>
void State::add_edge(char ch, State* next){
    if(ch == EPSILON)
        epsilon_jump_vec.push_back(next);
    else if(ch == ANY)
        accept_any_char = next;
    else
        ch_state_map[ch] = next;
}

void State::print(int indent){
    
    for (int i = 0; i<indent; ++i){
        std::cout << " ";
    }
    std::cout << (void*)this << std::endl;
    if(printed == 1)
        return;
    printed = 1;
    

    for(std::map<char, State*>::iterator it=ch_state_map.begin(); it!=ch_state_map.end(); it++){
        for (int i = 0; i<indent+2; ++i){
            std::cout << " ";
        }
        if(it->first == ANY)
            std::cout << ".";
        else
            std::cout << it->first;

        std::cout << std::endl;
        it->second->print(indent+2);
    }

    for(std::vector<State*>::iterator iter=epsilon_jump_vec.begin();
        iter != epsilon_jump_vec.end();
        iter++) {
        for (int i = 0; i<indent+2; ++i){
            std::cout << " ";
        }
        
        std::cout << "E" << std::endl;
        (*iter)->print(indent+2);
    }
}



int State::next_state(char ch, std::stack<State*> &s){
    if(accept_any_char != NULL){
        s.push(accept_any_char);
        accept_any_char->next_epsilong_state(s);
        return 0;
    }
    std::map<char, State*>::iterator it = ch_state_map.find(ch);
    if(it == ch_state_map.end()){
        return -1;
    }
    s.push(it->second);
    it->second->next_epsilong_state(s);
    return 0;
}


int State::next_epsilong_state(std::stack<State*> &s){
    for(std::vector<State*>::iterator it = epsilon_jump_vec.begin();
            it != epsilon_jump_vec.end();
            it++) {
            s.push(*it);
            (*it)->next_epsilong_state(s);
    }
    return 0;
}
