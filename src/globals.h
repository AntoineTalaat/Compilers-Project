#ifndef GLOBALS_H
#define GLOBALS_H

#include "state.h"
#include "nfa.h"

// include all globals here

static const char EPSILLON = '@';
static std::map<std::string,NFA*> regularDefinitionNFA;


#endif  //  GLOBALS_H