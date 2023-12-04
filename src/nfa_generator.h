#ifndef NFA_GENERATOR
#define NFA_GENERATOR

#include <string>
#include "nfa.h"
#include "state.h"

class NFAGenerator {
    private:
        std::vector<NFA*> allNFA;
        // std::string  rulesFile;
        // State* start;
        // State* end;
        
        
    public:
        NFAGenerator();
        NFAGenerator(std::string file);
        NFA* getFullNFA();
        static NFA* generateNFAFromPostfix(std::vector<std::string> postfix);
        static NFA* generateNFAFromString(std::string s);

    
};
#endif  // NFA_GENERATOR