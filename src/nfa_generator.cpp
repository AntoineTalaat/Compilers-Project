#include "nfa_generator.h"
#include "globals.h"
#include "operations_handler.h"

NFAGenerator::NFAGenerator() {
    this->rulesFile = "";
};

NFAGenerator::NFAGenerator(std::string file) {
    NFAGenerator::rulesFile = file;
};

 NFA* NFAGenerator::getFullNFA() {
     if(this->allNFA.empty())    return nullptr;
     NFA* final = this->allNFA.front();
     for(auto it = std::next(this->allNFA.begin()); it != this->allNFA.end(); ++it) {
         final = OperationsHandler::joinNFAs(final, *it);
     }

     return final;
 };
