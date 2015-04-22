#include <iostream>
#include <string>
#include "Parser.h"
#include "regexp.h"
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char *argv[])
{
    Parser p;
    p.parse("abc")->print(0);
    cout << "==========="<< endl;
    
    p.parse("a(b|c).a*bc?")->print(0);

    cout << "==========="<< endl;

    p.parse("abc(a|b|c)d")->print(0);
    cout << "===========" << endl;

    p.parse("(abc)")->print(0);
    cout << "===========" << endl;

    
    ParseTreeNode* root = p.parse("cd");
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

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
