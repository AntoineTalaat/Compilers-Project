#include "nfa.h"

NFA::NFA() {
    setStartState(new State());
    setFinalState(new State());
};

NFA::NFA(State* startState, State* finalState) {
    this->startState = startState;
    this->finalState = finalState;
};

NFA::NFA(State* startState, State* finalState, std::set<State *> states) {
    this->startState = startState;
    this->finalState = finalState;
    this->states = states;
    this->statesMap = createStateMap(states);
};

State* NFA::getStartState() {
    return this->startState;
};

void NFA::setStartState(State* state) {
    this->startState = state;
    this->states.insert(state);
};

State* NFA::getFinalState() {
    return this->finalState;
};

void NFA::setFinalState(State* state) {
    this->finalState = state;
    this->states.insert(state);
};

void NFA::addState(State* state) {
    this->states.insert(state);
};

std::set<State*> NFA::getStates() {
    return this->states;
};

void NFA::setBatchStates(std::set<State*> states) {
    this->states.insert(states.begin(), states.end());
};

std::map<int, State*> NFA::getStatesMap() {
    return this->statesMap;
};

std::map<int, State*> NFA::createStateMap(std::set<State*> states) {
    std::map<int, State*> statesMap;
    for(State* state : states){
        statesMap[state->getId()] = state;
    }
    return statesMap;
};

//std::pair<int, std::map<char,std::set<int>>> getTransitionTable(){
  //  return ;
//};   // TODO 