#include "nfa.h"

NFA::NFA() {
    setStartState(new State());
    // TODO initialize transition map  IMPORTANT
};

// NFA::NFA(State* startState, State* finalState) {
//     this.startState = startState;
// };

NFA::NFA(State* start, std::map<int,State*> states){
    this->startState = startState;
    this->setBatchStates(states);
}

NFA::NFA(State* startState, std::set<State*> states) {
    this->startState = startState;
    this->statesMap = createStateMap(states);
};

State* NFA::getStartState() {
    return this->startState;
};

void NFA::setStartState(State* state) {
    this->startState = state;
    addState(state);
};



void NFA::addState(State* state) {
    this->statesMap[state->getId()]=state;
};


void NFA::setBatchStates(std::map<int,State*> states) {
    // this->states.insert(states.begin(), states.end());
    for (const auto& pair : states) {
        this->statesMap[pair.first] = pair.second;
    }
};

std::map<int, State*> NFA::getStatesMap() {
    return this->statesMap;
};

std::map<int, State*> NFA::createStateMap(std::set<State*> states) {
    std::map<int, State*> statesMap;  // TODO check if stack or heap
    for(State* state : states){
        statesMap[state->getId()] = state;
    }
    return statesMap;
};

//std::pair<int, std::map<char,std::set<int>>> getTransitionTable(){
  //  return ;
//};   // TODO 