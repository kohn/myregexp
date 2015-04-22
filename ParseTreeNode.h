#ifndef PARSETREENODE_H
#define PARSETREENODE_H
#include "Automata.h"
#include <vector>
#include <stack>

class Automata;
// base class
class ParseTreeNode
{
protected:
    Automata* self;
   
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
public:
    ExistNode(ParseTreeNode* node);
    Automata* gen_automata();
    void print(int indent);
    ~ExistNode();
};

class CatNode:public ParseTreeNode
{
private:
    ParseTreeNode* left;
    ParseTreeNode* right;
public:
    CatNode(ParseTreeNode *l, ParseTreeNode *r){left = l; right=r;}
    Automata* gen_automata();
    void print(int indent);
    virtual ~CatNode();
};

#endif
