#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "ParseTreeNode.h"
#include <stack>

class Parser
{
private:
    ParseTreeNode* get_remaining_node(std::stack<ParseTreeNode*> &sta);
    int next_node(std::string s, int start_index, ParseTreeNode* &node);

public:
    Parser(){}
    ParseTreeNode* parse(std::string s);
    ~Parser(){}
};
#endif
