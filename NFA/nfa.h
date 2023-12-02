#ifndef NFA_H
#define NFA_H

#include <string>
#include <set>
#include "State.h"
#include <bits/stdc++.h>

class NFA {
    private:
        State* startState;
        State* finalState;
        std::set<State *> states;

    public:
        NFA();
        NFA(State* start, State* final);
        NFA(State* start, State* final, std::set<State *> states);
        
        State* getStartState();
        void   setStartState(State* state);
        State* getFinalState();
        void   setFinalState(State* state);
        void   addState(State* state);
        std::set<State*> getStates();
        void   setBatchStates(std::set<State*> states);
        std::pair<int, std::map<char,std::set<int>>> getTransitionTable();   // TODO check whether states r gonna be represented using their id/pointer?
};
#endif  // NFA_H