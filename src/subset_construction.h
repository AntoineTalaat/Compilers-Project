#ifndef SubsetConstruction_H
#define SubsetConstruction_H

#include "nfa.h"
#include "globals.h"
#include <set>

class SubsetConstruction {

    private:
        NFA nfa;
        std::set <char> alphabet;


        std::set <int> epsClosure(int state);
        std::set <int> getEpsClosure(std::set <int> states);
        std::set <int> move(std::set <int> states, char letter);

    public:

        SubsetConstruction(NFA nfa);
        std::map<std::pair<std::set<int>, char>, std::set<int>> convertNFAToDFA();
        void setAlphabet(std::set <char> alphabet);
        void printMap(std::map<int, State*> statesMap);
        void printSet(std::set<int> states);

        void printmarkedMap(std::map<std::set<int>, bool> marked);
        void printDFATransitionhs(std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran);

    std::string setToString(std::set<int> s);
};
#endif  // SubsetConstruction_H
