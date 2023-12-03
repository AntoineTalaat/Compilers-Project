#ifndef NFA_GENERATOR
#define NFA_GENERATOR

#include <string>
#include "nfa.h"

class NFAGenerator {
    private:
     //   std::vector<NFA> allNFA;
        static std::string  rulesFile;
        // NFA* joinNFAs(NFA* first, NFA* second);
    public:
        NFAGenerator();

        NFAGenerator(std::string file);
        // NFA* getFullNFA();
};
#endif