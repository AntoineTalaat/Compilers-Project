#include "nfa_generator.h"

NFAGenerator::NFAGenerator(std::string file) {
    this->rulesFile = file;
};

NFA* NFAGenerator::getFullNFA() {
    if(this->allNFA.empty())    return nullptr;
    NFA* final = this->allNFA.front();
    for(auto it = std::next(this->allNFA.begin()); it != this->allNFA.end(); ++it) {
        final = this->joinNFAs(final, *it);
    }

    return final;
}

NFA* NFAGenerator::joinNFAs(NFA* first, NFA* second) {
    NFA* newNfa = new NFA();
    State* start = new State();
    start->addTransition('EPSILLON', first->getStartState()->getId());
    start->addTransition('EPSILLON', second->getStartState()->getId());

    newNfa->setStartState(start);
    newNfa->setBatchStates(first->getStates());
    newNfa->setBatchStates(second->getStates());

    return newNfa;
}