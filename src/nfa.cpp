#include "nfa.h"
#include <utility>

NFA::NFA() {
};

NFA::NFA(State  startState) {
     this->setStartState(startState);
 };

NFA::NFA(State startState, State  finalState) {
     this->setStartState(startState);
     this->setFinalState(finalState);
};

NFA::NFA(State  start, std::map<int,State > states){
    this->setStartState(start);
    this->setBatchStates(std::move(states));
}

NFA::NFA(State  startState, std::set<State > states) {
    this->setStartState(startState);
    this->statesMap = createStateMap(std::move(states));
};

State  NFA::getStartState() {
    return this->statesMap[this->startStateID];
};

void NFA::setStartState(State  state) {
    this->startStateID = state.getId();
    addState(state);
};

State  NFA::getFinalState() {
    return this->statesMap[this->finalStateID];
};

// NFA  NFA::clone() {
//     NFA  newNFA= new NFA();

//     return newNFA;
// };

void NFA::setFinalState(State  state) {
    this->finalStateID = state.getId();
    //this->finalState.setIsAccepting(true);
    addState(state);
};

void NFA::addState(State  state) {
    this->statesMap[state.getId()]=state;
};

void NFA::setBatchStates(const std::map<int,State >& states) {
    // this->states.insert(states.begin(), states.end());
    for (const auto& pair : states) {
        this->statesMap[pair.first] = pair.second;
    }
};

std::map<int, State > NFA::getStatesMap() {
    return this->statesMap;
};

std::map<int, State > NFA::createStateMap(std::set<State > states) {
    std::map<int, State > statesMap;
    for(State  state : states){
        statesMap[state.getId()] = state;
    }
    return statesMap;
};
