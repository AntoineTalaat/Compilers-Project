#ifndef GLOBALS_H
#define GLOBALS_H

#include "state.h"
#include "nfa.h"

// include all globals here

static const char EPSILLON = 0;
class Globals{
    public:
        static std::map<std::string,NFA> regularDefinitionNFA;
        static std::set<char> alphabet;
};

#endif  //  GLOBALS_H