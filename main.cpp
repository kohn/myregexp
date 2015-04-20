#include <iostream>
#include <string>
#include "Parser.h"
#include "regexp.h"
using namespace std;

void test(string pattern, string case_str){
    regexp reg(pattern);
    if(reg.accept(case_str))
        cout << "Accept" << endl;
    else
        cout << "Reject" << endl;
}

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


    test("abc", "abc");
    test("a(b|c)", "ab");
    test("ab*", "abbbb");
    test("a?b*", "");
    test("a?b*", "a");
    test("a?b*", "bbb");
    test("a?b*", "abbbb");
    test("a?b*", "c");

    test(".",  "a");
    test(".", "aa");
    test(".*", "asdsads");

    test("ab((cd)|e)fg", "abcdfg");
    test("ab((cd)|e)fg", "abefg");
    test("ab((cd)|e)fg", "abcfg");

    test("ab((cd)|e)*fg", "abcdcdcdfg");
    test("ab((cd)|e)*fg", "abcdcdefg");
    test("ab((cd)|e)*fg", "abcdcdcefg");
    
    
    return 0;
}
