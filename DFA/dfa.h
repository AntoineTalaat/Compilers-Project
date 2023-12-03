#ifndef DFA_H
#define DFA_H

#include <string>
#include <set>
#include "State.h"
#include <bits/stdc++.h>
class DFA {
    private:
        State* startState;
        std::map<int, State*> statesMap;
        std::map<int, State*> createStateMap(std::set<State*> states);
    public:
        DFA();

};

#endif // DFA_H
