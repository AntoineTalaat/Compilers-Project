#include "state.h"

int State::counterGlobalId = 0;

State::State(){
    this->id = generateId();
    // std::cout<<"ASSIGNED STATE TO ID "<<this->id <<'\n';
    this->isAccepting = false;
};

State::State(bool isAccepting) {
    this->id = generateId();
    // std::cout<<"ASSIGNEDD STATE TO ID "<<this->id <<'\n';
    this->isAccepting = isAccepting;
    if(!isAccepting) this->acceptedToken=nullptr;
};

State::State(Token* t) {
    this->id = generateId();
    this->isAccepting = false;
    this->acceptedToken = t;
};



State::State(int id, bool isAccepting) {
    this->id = id;
    // std::cout<<"ASSIGNEDDD STATE TO ID "<<this->id<<'\n' ;

    this->isAccepting = isAccepting;
};

// State* State::clone(){

// }


void State::setId(int id) {
    this->id = id;
};
int State::getId() const {
    return id;
}

// Comparison operator for std::set
bool State::operator<(const State& other) const {
    return id < other.id;
}

// Equality operator for std::set
bool State::operator==(const State& other) const {
    return id == other.id;
}

// Hash function for std::unordered_set
namespace std {
    std::size_t hash<State>::operator()(const State& s) const {
        // Use a simple hash function for illustration purposes
        return hash<int>()(s.getId());
    }
}


void State::setIsAccepting(bool isAccepting) {
    this->isAccepting = isAccepting;
};
bool State::getIsAccepting() {
    return this->isAccepting;
};

void State::setAcceptedToken(Token* t) {
    setIsAccepting(true);
    this->acceptedToken = t;
};
Token* State::getAcceptedToken() {
    return this->acceptedToken;
};



std::map<char, std::set<int/*State**/>> State::getTransitions() {
    return this->transitions;
};

void State::addTransition(char letter, int state) {
    auto it = this->transitions.find(letter);
    // std::cout<<"x " <<'\n';

    if (it == this->transitions.end()) {
        // If the key doesn't exist, insert a new key-value pair

        this->transitions.emplace(letter, std::set<int>{state});
        // std::cout<<"y " <<'\n';

    } else {
        // If the key already exists, insert the state into the existing set
        it->second.insert(state);
        // std::cout<<"z " <<'\n';

    }
}


int State::generateId() {
    return State::counterGlobalId++;              
}

void State::printTransitions() {
    std::map<char, std::set<int>> transitions = this->getTransitions();
    for(auto tr : transitions) {
        std::cout << "Input: " << tr.first << " moves to States# ";
        for (auto &s : tr.second)
            std::cout << s << " ";
        std::cout << std::endl;
    }
};

std::string State::toString() {
    std::string s = "";

    s += "transitions:\n";
    for (const auto& transition : this->getTransitions()) {
        char a = transition.first;
        const auto& U = transition.second;
        s += "    " + std::string(1, a) + " -> {";
        for (const auto& u : U) {
            s += std::to_string(u) + ", ";
        }
        s += "}\n";
    }
    return s;
};

