#ifndef GLOBALS_H
#define GLOBALS_H

#include "state.h"
#include "nfa.h"

// Please Uncomment this for changing lexical rules
#define VS_CODE


static const char EPSILLON = 0;
class Globals{
    public:
        static std::map<std::string,NFA> regularDefinitionNFA;
        static std::set<char> alphabet;  
        static const std::string LEXICAL_RULES_FILE;
        static const std::string SYNTAX_RULES_FILE;
        static const std::string PROGRAM_INPUT_FILE;
        static const std::string TEST_INPUT_FILE;
};

#endif  //  GLOBALS_H