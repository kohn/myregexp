#ifndef REGEXP_H
#define REGEXP_H
#include <string>
#include "Automata.h"
#include "ParseTreeNode.h"
class regexp
{
private:
    Automata* automata;
    ParseTreeNode* root;
public:
    regexp(std::string pattern);
    int accept(std::string);
    virtual ~regexp();
};
#endif
