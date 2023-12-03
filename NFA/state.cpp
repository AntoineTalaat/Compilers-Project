#include "state.h"

int State::counterGlobalId = 0;

State::State(){
   // this->id = generateId();
   // this->isAccepting = false;
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

void State::setAcceptedToken(Token t) {
    setIsAccepting(true);
    this->acceptedToken = t;
};
Token State::getAcceptedToken() {
    return this->acceptedToken;
};



std::map<char, std::set<int/*State**/>> State::getTransitions() {
    return this->transitions;
};

void State::addTransition(char letter, int state) {
    auto it = this->transitions.find(letter);

    if (it == this->transitions.end()) {
        // If the key doesn't exist, insert a new key-value pair
        this->transitions.emplace(letter, std::set<int>{state});
    } else {
        // If the key already exists, insert the state into the existing set
        it->second.insert(state);
    }
}


int State::generateId() {
    return State::counterGlobalId++;              
}