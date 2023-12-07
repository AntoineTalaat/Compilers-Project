#ifndef SubsetConstruction_H
#define SubsetConstruction_H

#include "nfa.h"
#include "globals.h"
#include <set>
#include "utils.h"

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



    public:


        SubsetConstruction(NFA nfa);
        void setStartStateID(int startState);
        void setDeadStateID(int deadState);
        int getStartStateID();
        int getDeadStateID();
        void setAlphabet(std::set <char> alphabet);
        std::set<char> getAlphabet();
        std::map< int , State> getDFA();
};
#endif  // SubsetConstruction_H
