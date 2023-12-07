#ifndef SubsetConstruction_H
#define SubsetConstruction_H

#include "nfa.h"
#include "globals.h"
#include <set>

class SubsetConstruction {

    private:
        NFA nfa;
        std::set <char> alphabet;

        int startStateID ;
        int deadStateID ;

        std::set<int> startStateEpsClosure;
        std::set <int> epsClosure(int state);
        std::set <int> getEpsClosure(std::set <int> states);
        std::set <int> move(std::set <int> states, char letter);
        std::map<std::pair<std::set<int>, char>, std::set<int>> convertNFAToDFA();

        void printMap(std::map<int, State> statesMap);
        void printSet(std::set<int> states);
        void printmarkedMap(std::map<std::set<int>, bool> marked);
        void printDFATransitionhs(std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran);
        std::string setToString(std::set<int> s);


    public:


        SubsetConstruction(NFA nfa);
        void setStartStateID(int startState);
        void setDeadStateID(int deadState);
        int getStartStateID();
        int getDeadStateID();
        void setAlphabet(std::set <char> alphabet);
        std::map< int , State> getDFA();
        std::map<int, State> minimizeDFA(std::map<int, State> &DFA);
};
#endif  // SubsetConstruction_H
