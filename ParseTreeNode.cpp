#include "ParseTreeNode.h"
#include <iostream>
ParseTreeNode::ParseTreeNode(){
}
ParseTreeNode::~ParseTreeNode(){
}

StarNode::StarNode(ParseTreeNode* node){
    child = node;
    self = NULL;
}
StarNode::~StarNode(){
}

DotNode::DotNode(){
    self = NULL;
}

DotNode::~DotNode(){
    
}

CharNode::CharNode(char c){
    ch=c;
    self = NULL;
}

CharNode::~CharNode(){
    
}
UnionNode::UnionNode(ParseTreeNode* l, ParseTreeNode* r){
    left = l;
    right = r;
    self = NULL;
}

UnionNode::~UnionNode(){
    
}
ExistNode::ExistNode(ParseTreeNode* node){
    child = node;

    self = NULL;
}

ExistNode::~ExistNode(){
    
}
ConcatNode::ConcatNode(){
    self = NULL;
}

ConcatNode::~ConcatNode(){
    
}


void ConcatNode::add_node(ParseTreeNode* node){
    v.push_back(node);
}
void ConcatNode::print(int indent){
    for (int i = 0; i<indent; ++i){
        std::cout << "\t";
    }
    std::cout << "Concat Node" << std::endl;
    for(int i=v.size()-1; i>=0; i--){
        v[i]->print(indent+1);
    }
}

void DotNode::print(int indent){
    for (int i = 0; i<indent; ++i){
        std::cout << "\t";
    }

    std::cout << "Dot Node" << std::endl;
}

void StarNode::print(int indent){
    for (int i = 0; i<indent; ++i){
        std::cout << "\t";
    }

    std::cout << "StarNode" << std::endl;
    child->print(indent+1);
}

void CharNode::print(int indent){
    for (int i = 0; i<indent; ++i){
        std::cout << "\t";
    }

    std::cout << "CharNode: " << ch << std::endl;
}

void ExistNode::print(int indent){
    for (int i = 0; i<indent; ++i){
        std::cout << "\t";
    }

    std::cout << "ExistNode" << std::endl;
    child->print(indent+1);
}

void UnionNode::print(int indent){
    for (int i = 0; i<indent; ++i){
        std::cout << "\t";
    }

    std::cout << "UnionNode" << std::endl;
    left->print(indent+1);
    right->print(indent+1);
}


Automata* ConcatNode::gen_automata(){
    if(self != NULL)
        return self;
       
    for(int i=v.size()-1; i>=0; i--){
        if(self == NULL)
            self = v[i]->gen_automata();
        else
            self->concat(v[i]->gen_automata());
    }
    return self;
}

Automata* StarNode::gen_automata(){
    if(self != NULL)
        return self;
    
    Automata* child_automata = child->gen_automata();
    self = new Automata();
    self->s_state()->add_edge(EPSILON, child_automata->s_state());
    self->s_state()->add_edge(EPSILON, self->e_state());
    child_automata->e_state()->add_edge(EPSILON, child_automata->s_state());
    child_automata->e_state()->add_edge(EPSILON, self->e_state());
    child_automata->e_state()->set_normal_type();
    return self;
}

Automata* DotNode::gen_automata(){
    if(self != NULL)
        return self;
    
    self = new Automata();
    self->s_state()->add_edge(ANY, self->e_state());
    return self;
}

Automata* CharNode::gen_automata(){
    if(self != NULL)
        return self;
    
    self = new Automata();
    self->s_state()->add_edge(ch, self->e_state());
    return self;
}

Automata* UnionNode::gen_automata(){
    if(self != NULL)
        return self;
    
    self = new Automata();
    self->s_state()->add_edge(EPSILON, left->gen_automata()->s_state());
    self->s_state()->add_edge(EPSILON, right->gen_automata()->s_state());

    State* le = left->gen_automata()->e_state();
    State* re = right->gen_automata()->e_state();
    le->add_edge(EPSILON, self->e_state());
    re->add_edge(EPSILON, self->e_state());

    // set end state of left child and right child to normal state
    le->set_normal_type();
    re->set_normal_type();
    
    return self;
}

Automata* ExistNode::gen_automata(){
    if(self != NULL)
        return self;
    
    self = new Automata();
    State* s = self->s_state();
    State* e = self->e_state();
    s->add_edge(EPSILON, e);

    Automata* child_automata = child->gen_automata();
    s->add_edge(EPSILON, child_automata->s_state());
    child_automata->e_state()->add_edge(EPSILON, e);
    child_automata->e_state()->set_normal_type();
    return self;
}
