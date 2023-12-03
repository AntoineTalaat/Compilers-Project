#include "state.h"
#include <map>
State::State() {
    this->id = generateId();
    this->isAccepting = false;
};

State::State(bool isAccepting) {
    this->id = generateId();
    this->isAccepting = isAccepting;
};

State::State(int id, bool isAccepting) {
    this->id = id;
    this->isAccepting = isAccepting;
};

void State::setId(int id) {
    this->id = id;
};

int State::getId() {
    return this->id;
};

void State::setIsAccepting(bool isAccepting) {
    this->isAccepting = isAccepting;
};

bool State::getIsAccepting() {
    return this->isAccepting;
};

std::map<char, std::set<int/*State**/>> State::getTransitions() {
    return this->transitions;
};

void State::addTransition(char letter, int state) {
    if(this->transitions.find(letter) == this->transitions.end())
        this->transitions.insert_or_assign(letter, std::set<int>({state}));
    else    this->transitions.at(letter).insert(state);
};

int State::generateId() {
    return 0;              // TODO
}