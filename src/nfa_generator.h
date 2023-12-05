#ifndef NFA_GENERATOR
#define NFA_GENERATOR

#include <string>
#include "nfa.h"
#include "state.h"

class NFAGenerator {
    private:
       
    public:
        NFAGenerator();
        NFAGenerator(std::string file);
        static NFA getFullNFA(std::vector<NFA>);
        static NFA generateNFAFromPostfix(std::vector<std::string> postfix);
        static NFA generateNFAFromString(std::string s);
};
#endif  // NFA_GENERATOR