#ifndef PARSETREENODE_H
#define PARSETREENODE_H
#include "Automata.h"
#include <vector>
#include <stack>

class Automata;
// base class
class ParseTreeNode
{
 
public:
    ParseTreeNode();
    virtual Automata* gen_automata()=0;
    virtual void print(int indent) = 0;
    virtual ~ParseTreeNode()=0;
};

// *
class StarNode:public ParseTreeNode
{
private:
    ParseTreeNode* child;
    Automata* self;

public:
    StarNode(ParseTreeNode* node);
    Automata* gen_automata();
    void print(int indent);
    ~StarNode();
};

// .
class DotNode:public ParseTreeNode
{
private:
    Automata* self;

public:
    DotNode();
    Automata* gen_automata();
    void print(int indent);
    ~DotNode();
};
// character
class CharNode:public ParseTreeNode
{
private:
    char ch;
    Automata* self;

public:
    CharNode(char ch);
    Automata* gen_automata();
    void print(int indent);
    ~CharNode();
};

// |
class UnionNode:public ParseTreeNode
{
private:
    ParseTreeNode* left;
    ParseTreeNode* right;
    Automata* self;
public:
    UnionNode(ParseTreeNode* l, ParseTreeNode* r);
    Automata* gen_automata();
    void print(int indent);
    ~UnionNode();
};
// ?
class ExistNode:public ParseTreeNode
{
private:
    ParseTreeNode* child;
    Automata* self;
public:
    ExistNode(ParseTreeNode* node);
    Automata* gen_automata();
    void print(int indent);
    ~ExistNode();
};

// concat
class ConcatNode:public ParseTreeNode
{
private:
    std::vector<ParseTreeNode*> v;
    Automata* self;
public:
    ConcatNode();
    Automata* gen_automata();
    void add_node(ParseTreeNode* node);
    void print(int indent);
    ~ConcatNode();
};
#endif
