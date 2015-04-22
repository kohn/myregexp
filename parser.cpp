#include "Parser.h"
#include "ParseTreeNode.h"
#include <stack>
#include <string>
#include <assert.h>
#include <list>


ParseTreeNode* Parser::parse(std::string s){
    int len = s.length();
    return parse_whole_tree(s, 0, len, len);
}

ParseTreeNode* Parser::parse_whole_tree(std::string s, int start, int end, int &new_pos){
    int pos = end;
    ParseTreeNode* last_node = NULL;
    last_node = parse_one_node(s, start, pos, pos);
    while(pos>start){
        switch (get_next_op(s, pos)) {
            case CAT: {
                last_node = new CatNode(parse_one_node(s, start, pos, pos), last_node);
                break;
            }
            case UNION: {
                last_node = new UnionNode(parse_whole_tree(s, start, pos, pos), last_node);
                break;
            }
        }
    }
    new_pos = start;
    return last_node;
}
            
ParseTreeNode* Parser::parse_one_node(std::string s, int start, int end, int &new_pos){
    int pos = end;

    if(pos <= start)
        return NULL;
    
    switch (s[pos-1]) {
    case '*': {
        ParseTreeNode* new_node = new StarNode(parse_one_node(s, start, pos-1, pos));
        new_pos = pos;
        return new_node;
    }
    case '?': {
        ParseTreeNode* new_node = new ExistNode(parse_one_node(s, start, pos-1, pos));
        new_pos = pos;
        return new_node;
    }
    case '.': {
        ParseTreeNode* new_node = new DotNode();
        new_pos = pos-1;
        return new_node;
    }
    case '+': { // a+ => aa*
        ParseTreeNode* next_node = parse_one_node(s, start, pos-1, pos);
        ParseTreeNode* star_node = new StarNode(next_node);
        ParseTreeNode* cat_node = new CatNode(next_node, star_node);
        new_pos = pos;
        return cat_node;
    }
    case ')': {
        // find corresponding(the outmost) '('
        int i;
        for(i=start; i<end; i++){
            if(s[i] == '(')
                break;
        }

        // parenthesis mismatch
        if(i == end)
            return NULL;
        
        new_pos = i;
        return parse_whole_tree(s, i+1, end-1, pos);
    }
    case '(': {
        // parenthesis mismatch
        return NULL;
    }
    case ']': {
        int i;
        // find the outmost '['
        for(i=start; i<end; i++){
            if(s[i] == '[')
                break;
        }

        if(i == end)
            return NULL;

        new_pos = i;
        return parse_bracket_node(s, i+1, end-1);
    }
    case '[': {
        // bracket mismatch
        return NULL;
    }
    default:{
        // characters cases
        new_pos = pos - 1;
        return new CharNode(s[pos-1]);
    }
    }
}

ParseTreeNode* Parser::parse_bracket_node(std::string s, int start, int end){
    if(start >= end)
        return NULL;
    
    ParseTreeNode* root = new CharNode(s[end-1]);
    for(int i=end-2; i>=start; i--){
        ParseTreeNode* char_node = new CharNode(s[i]);
        root = new UnionNode(char_node, root);
    }
    return root;
}


OP Parser::get_next_op(std::string s, int &pos){
    if(s[pos-1] == '|'){
        pos = pos-1;
        return UNION;
    }
    else
        return CAT;
}
