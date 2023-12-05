#ifndef GLOBALS_H
#define GLOBALS_H

#include "state.h"
#include "nfa.h"

// include all globals here

static const char EPSILLON = '@';
class Globals{
    public:
        static std::map<std::string,NFA> regularDefinitionNFA;
};

#endif  //  GLOBALS_H