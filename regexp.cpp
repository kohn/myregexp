#include "regexp.h"
#include <string>
#include "Parser.h"
#include "Automata.h"

regexp::regexp(std::string pattern){
    Parser p;
    automata = p.parse(pattern)->gen_automata();
    //automata->print();
}

regexp::~regexp(){
    
}


int regexp::accept(std::string s){
    return automata->accept(s);
}
