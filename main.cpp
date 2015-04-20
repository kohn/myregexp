#include <iostream>
#include <string>
#include "Parser.h"
using namespace std;

int main(int argc, char *argv[])
{
    Parser p;
    p.parse("a(b|c).a*bc?")->print(0);

    cout << "==========="<< endl;

    p.parse("abc(a|b|c)d")->print(0);
    cout << "===========" << endl;

    p.parse("(abc)")->print(0);
    cout << "===========" << endl;

    
    ParseTreeNode* root = p.parse("abc");
    root->print(0);
    Automata* root_automata = root->gen_automata();
    root_automata->print();

    root = p.parse("a?b*");
    root->print(0);
    root_automata = root->gen_automata();
    root_automata->print();

    root = p.parse("c(a|b)d");
    root->print(0);
    root_automata = root->gen_automata();
    root_automata->print();
    
    return 0;
}
