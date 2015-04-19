#ifndef PARSETREENODE_H
#define PARSETREENODE_H
#include "automata.h"
#include <vector>
// base class
#include <stack>
class ParseTreeNode
{
public:
    ParseTreeNode();
    virtual Automata* gen_automata()=0;
    virtual void print(int indent)=0;
    virtual ~ParseTreeNode()=0;
};

// *
class StarNode:public ParseTreeNode
{
private:
    ParseTreeNode* child;
public:
    StarNode(ParseTreeNode* node);
    Automata* gen_automata(){return 0;}
    void print(int indent);
    ~StarNode();
};

// .
class DotNode:public ParseTreeNode
{
public:
    DotNode();
    Automata* gen_automata(){return 0;}
    void print(int indent);
    ~DotNode();
};
// character
class CharNode:public ParseTreeNode
{
private:
    char ch;
public:
    CharNode(char ch);
    Automata* gen_automata(){return 0;}
    void print(int indent);
    ~CharNode();
};

// |
class UnionNode:public ParseTreeNode
{
private:
    ParseTreeNode* left;
    ParseTreeNode* right;
public:
    UnionNode(ParseTreeNode* l, ParseTreeNode* r);
    Automata* gen_automata(){return 0;}
    void print(int indent);
    ~UnionNode();
};
// ?
class ExistNode:public ParseTreeNode
{
private:
    ParseTreeNode* child;
public:
    ExistNode(ParseTreeNode* node);
    Automata* gen_automata(){return 0;}
    void print(int indent);
    ~ExistNode();
};

// concat
class ConcatNode:public ParseTreeNode
{
private:
    std::vector<ParseTreeNode*> v;

public:
    ConcatNode();
    Automata* gen_automata(){return 0;}
    void add_node(ParseTreeNode* node);
    void print(int indent);
    ~ConcatNode();
};
#endif
