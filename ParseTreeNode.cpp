#include "ParseTreeNode.h"
#include <iostream>
ParseTreeNode::ParseTreeNode(){
    self = NULL;
}

ParseTreeNode::~ParseTreeNode(){
    if(self != NULL)
        delete self;
}

StarNode::StarNode(ParseTreeNode* node){
    child = node;
}
StarNode::~StarNode(){
    if(child != NULL)
        delete child;
}

DotNode::DotNode(){
}

DotNode::~DotNode(){
    
}

CharNode::CharNode(char c){
    ch=c;
}

CharNode::~CharNode(){
    
}
UnionNode::UnionNode(ParseTreeNode* l, ParseTreeNode* r){
    left = l;
    right = r;
}

UnionNode::~UnionNode(){
    if(left != NULL)
        delete left;
    if(right != NULL)
        delete right;
}
ExistNode::ExistNode(ParseTreeNode* node){
    child = node;
}

ExistNode::~ExistNode(){
    if(child != NULL)
        delete child;
    
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

void CatNode::print(int indent){
    for (int i = 0; i<indent; ++i){
        std::cout << "\t";
    }

    std::cout << "CatNode" << std::endl;
    left->print(indent+1);
    right->print(indent+1);
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


CatNode::~CatNode(){
    
}
Automata* CatNode::gen_automata(){
    if(self != NULL)
        return self;

    Automata* l = left->gen_automata();
    Automata* r = right->gen_automata();
    
    self = new Automata();
    self->s_state()->add_edge(EPSILON, l->s_state());
    l->e_state()->add_edge(EPSILON, r->s_state());
    r->e_state()->add_edge(EPSILON, self->e_state());
    return self;
}

