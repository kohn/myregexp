#include "regexp.h"
#include <string>
#include "Parser.h"
#include "Automata.h"

regexp::regexp(std::string pattern){
    Parser p;
    root = p.parse(pattern);
    automata = root->gen_automata();
    //automata->print();
}

regexp::~regexp(){
    delete root;
}


int regexp::accept(std::string s){
    return automata->accept(s);
}
