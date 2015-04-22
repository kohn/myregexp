#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "ParseTreeNode.h"
#include <stack>

enum OP {CAT, UNION};
class Parser
{
private:
    ParseTreeNode* parse_whole_tree(std::string s, int start, int end, int &new_pos);
    ParseTreeNode* parse_one_node(std::string s, int start, int end, int &new_pos);
    OP get_next_op(std::string s, int &pos);
    
public:
    Parser(){}
    ParseTreeNode* parse(std::string s);
    ~Parser(){}
};
#endif
