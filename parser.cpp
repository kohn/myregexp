#include "parser.h"
#include "ParseTreeNode.h"
#include <stack>
#include <string>
#include <assert.h>
#include <list>


ParseTreeNode* Parser::parse(std::string s){
    int len = s.length();
    ParseTreeNode* root = NULL;
    std::stack<ParseTreeNode*> node_stack;

    int i = 0;
    while(i<len){
        ParseTreeNode* new_node;
        i = next_node(s, i, new_node);
        node_stack.push(new_node);
    }
    return get_remaining_node(node_stack);
}

int Parser::next_node(std::string s, int start_index, ParseTreeNode* &node){
    int len = s.length();
    int node_flag = 0;
    int left_brace_flag = 0;
    std::stack<ParseTreeNode*> local_node_stack;

    for(int i=start_index; i<len; i++){
        switch (s[i]) {
        case '.': {
            if(node_flag != 0 && left_brace_flag == 0){
                node = local_node_stack.top();
                local_node_stack.pop();
                return i;
            }
            ParseTreeNode* new_node = new DotNode();
            local_node_stack.push(new_node);
            node_flag++;
            break;
        }
        case '?': {
            ParseTreeNode* new_node = new ExistNode(local_node_stack.top());
            local_node_stack.pop();
            local_node_stack.push(new_node);
            node_flag++;
            break;
        }
        case '*': {
            ParseTreeNode* new_node = new StarNode(local_node_stack.top());
            local_node_stack.pop();
            local_node_stack.push(new_node);
            node_flag ++;
            break;
        }
        case '(': {
            if(node_flag!=0 && left_brace_flag==0){
                node = local_node_stack.top();
                local_node_stack.pop();
                assert(local_node_stack.empty());
                return i;
            }
            left_brace_flag ++;
            break;
        }
        case ')': {
            if(left_brace_flag == 0){
                node = local_node_stack.top();
                local_node_stack.pop();
                assert(local_node_stack.empty());
                return i-1;
            }
            left_brace_flag --;
            ParseTreeNode* new_node = get_remaining_node(local_node_stack);
            local_node_stack.push(new_node);
            node_flag++;
            break;
        }
        case '|':{
            ParseTreeNode* left= local_node_stack.top();
            local_node_stack.pop();
            ParseTreeNode* right;
            i = next_node(s, i+1, right);
            ParseTreeNode* new_node = new UnionNode(left, right);
            local_node_stack.push(new_node);
            node_flag++;
            break;
        }
        default:{
            if(node_flag !=0 && left_brace_flag == 0){
                node = local_node_stack.top();
                local_node_stack.pop();
                assert(local_node_stack.empty());
                return i;
            }
            ParseTreeNode* new_node = new CharNode(s[i]);
            local_node_stack.push(new_node);
            node_flag++;
            break;
        }
        }
    }
    node = get_remaining_node(local_node_stack);
    return len;
}

ParseTreeNode* Parser::get_remaining_node(std::stack<ParseTreeNode*> &sta){
    if(sta.empty())
        return NULL;
    if(sta.size() == 1){
        ParseTreeNode* top_node = sta.top();
        sta.pop();
        return top_node;
    }
    else{
        ConcatNode* new_node = new ConcatNode();
        while(!sta.empty()){
            new_node->add_node(sta.top());
            sta.pop();
        }
        return new_node;
    }
}
