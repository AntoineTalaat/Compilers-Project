#ifndef NFA_H
#define NFA_H

#include "State.h"
#include <bits/stdc++.h>

class NFA {
    private:
        int startStateID;
        int finalStateID;
        std::map<int, State> statesMap;
        std::map<int, State> createStateMap(std::set<State> states);

    public:
        NFA();
        NFA(State start);
        NFA(State start, State final);
        NFA(State start, std::map<int,State> states);
        NFA(State start, std::set<State> states);
      
        static NFA deepCopy(NFA nfa);
        State& getStartState();
        void   setStartState(State state);
        State& getFinalState();
        void   setFinalState(State state);
        void   addState(State state);
        void   setBatchStates(const std::map<int,State>& states);
        std::map<int, State> getStatesMap();
        
};
#endif  // NFA_H