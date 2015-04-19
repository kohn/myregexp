#include <iostream>
#include <string>
#include "parser.h"
using namespace std;

int main(int argc, char *argv[])
{
    Parser p;
    p.parse("(ab|c).*bc?")->print(0);

    cout << "==========="<< endl;

    p.parse("abc(a|b|c)d")->print(0);
    cout << "===========" << endl;

    p.parse("(abc)")->print(0);
    
    return 0;
}
