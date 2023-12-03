#ifndef SubsetConstruction_H
#define SubsetConstruction_H

#include "../NFA/nfa.h"
#include "../NFA/state.h"
#include <set>

class SubsetConstruction {

    private:
        NFA nfa;
        std::set <char> alphabet;
        std::map<int , State* > stateMap;

        std::set <int> epsClosure(int state);
        std::set <int> getEpsClosure(std::set <int> states);
        std::set <int> move(std::set <int> states, char letter);

    public:

        SubsetConstruction(NFA nfa);
        std::map<std::pair<std::set<int>, char>, std::set<int>> convertNFAToDFA();
        void setStatesMap(std::map<int , State* > stateMap);
        void setAlphabet(std::set <char> alphabet);
};
#endif  // SubsetConstruction_H
