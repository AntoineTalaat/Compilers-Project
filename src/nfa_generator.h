#ifndef NFA_GENERATOR
#define NFA_GENERATOR

#include <string>
#include "nfa.h"

class NFAGenerator {
    private:
        std::vector<NFA*> allNFA;
        std::string  rulesFile;
        
    public:
        NFAGenerator();
        NFAGenerator(std::string file);
        NFA* getFullNFA();
};
#endif  // NFA_GENERATOR