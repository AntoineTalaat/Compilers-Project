
#include "globals.h"
std::map<std::string,NFA> Globals::regularDefinitionNFA=*(new std::map<std::string,NFA>());
std::set<char> Globals::alphabet = *(new std::set<char>());