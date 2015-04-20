#ifndef REGEXP_H
#define REGEXP_H
#include <string>
#include "Automata.h"
class regexp
{
private:
    Automata* automata;
public:
    regexp(std::string pattern);
    int accept(std::string);
    virtual ~regexp();
};
#endif
