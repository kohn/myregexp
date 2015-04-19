#include "ParseTreeNode.h"
#include <iostream>
ParseTreeNode::ParseTreeNode(){
    
}
ParseTreeNode::~ParseTreeNode(){
    
}

StarNode::StarNode(ParseTreeNode* node){
    child = node;
}
StarNode::~StarNode(){
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
    
}
ExistNode::ExistNode(ParseTreeNode* node){
    child = node;
}

ExistNode::~ExistNode(){
    
}
ConcatNode::ConcatNode(){
    
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
