//
// Created by veror on 12/3/2023.
//

#include "nfa.h"
#include "subset_construction.h"
#include <iostream>

bool debug = false;

SubsetConstruction::SubsetConstruction(NFA nfa) {
    this->nfa = nfa;
//    this->printMap(this->nfa.getStatesMap());
 //   std::cout << "-------------------------------------------------";
}



void SubsetConstruction::setAlphabet(std::set <char> alphabet) {

    alphabet.erase(EPSILLON);
    this->alphabet = std::move(alphabet);

}



std::set<int> SubsetConstruction::move(std::set<int> states, char letter) {
    std::set<int> move;
    for(int state : states) {
        State* currentState = this->nfa.getStatesMap().at(state);
        std::map<char, std::set<int>> transitions = currentState->getTransitions();
        if(transitions.find(letter) != transitions.end()) {
            std::set<int> letterTransitions = transitions.at(letter);
            move.insert(letterTransitions.begin(), letterTransitions.end());
        }
    }
    return move;
}

std::set<int> SubsetConstruction::epsClosure(int state) {
    std::set<int> epsClosure;
    std::set<int> visited;
    std::stack<int> stack;
    stack.push(state);

    while(!stack.empty()) {
        int currentStateID = stack.top();
        State* currentState = this->nfa.getStatesMap().at(currentStateID);
        stack.pop();

        if(visited.find(currentStateID) != visited.end())
            continue;
        visited.insert(currentStateID);
        epsClosure.insert(currentStateID);

        std::map<char, std::set<int>> transitions = currentState->getTransitions();

        if(transitions.find(EPSILLON) != transitions.end()) {
            std::set<int> epsTransitions = transitions.at(EPSILLON);
            for(int epsTransition : epsTransitions)
                stack.push(epsTransition);
        }
    }
    return epsClosure;
}

std::set <int> SubsetConstruction::getEpsClosure(const std::set <int> states){
    std::set<int> epsClosure;

    for (int state : states) {
        std::set<int> stateEpsClosure = this->epsClosure(state);
        epsClosure.insert(stateEpsClosure.begin(), stateEpsClosure.end());
    }

    return epsClosure;
}


void SubsetConstruction::printSet(std::set<int> s) {
    std::cout << "{";
    for (int state : s) {
        std::cout << state << " ";
    }
    std::cout << "}";
}

std::string SubsetConstruction::setToString(std::set<int> s) {

    std::string result = "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += std::to_string(*it);
        if (std::next(it) != s.end()) {
            result += ", ";
        }
    }
    result += "}";
    return result;
}

void SubsetConstruction::printMap(std::map<int, State*> statesMap){
    std::cout << "States:\n";
    for (const auto& state : statesMap) {
        std::cout << state.first << ": ";
        std::cout << state.second->toString()<< std::endl;
    }
}

void SubsetConstruction::printmarkedMap(std::map<std::set<int>, bool> marked){
    std::cout << "marked Map:\n";
    for (const auto& state : marked) {
        this->printSet(state.first);
        std::cout << state.second << std::endl;
    }
}


void SubsetConstruction::printDFATransitionhs(std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran){
    std::cout << "Dtran:\n";
    for (const auto& transition : Dtran) {
        const auto& T = transition.first.first;
        char a = transition.first.second;
        const auto& U = transition.second;
        std::cout << "Dtran[{" << this->setToString(T)<< "}, " << a << "] = {" << this->setToString(U)<< "}\n";
    }
}


std::map< std::pair<std::set<int>, char> , std::set<int> > SubsetConstruction::convertNFAToDFA()  {
    if(debug)   printMap(this->nfa.getStatesMap());
    if(debug)   std::cout << "-------------------------------------------------";

    std::queue<std::set<int>> DstatesQueue;
    std::set<std::set<int>> Dstates;
    std::map<std::set<int>, bool> marked;
    std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran;

    // Step 1: Initialize with epsilon closure of the start state
    int startStateID = this->nfa.getStartState()->getId();
    if(debug) std::cout << "start state id: " << startStateID << std::endl;

    std::set<int> startEpsClosure = epsClosure(startStateID);
    if(debug) std::cout << "start eps closure: ";
    if(debug) this->printSet(startEpsClosure);
    if(debug) std::cout << "-------------------------------------------------\n";


    DstatesQueue.push(startEpsClosure);
    Dstates.insert(startEpsClosure);

    while (!DstatesQueue.empty()) {
        std::set<int> T = DstatesQueue.front();
        DstatesQueue.pop();

        // Mark T
        marked[T] = true;

        // Step 2: Process each input symbol
        for (char a: this->alphabet) {
            // Step 3: Calculate U = epsClosure(move(T, a))
            if(debug) std::cout << "current input " << a << std::endl;
            if(debug) std::cout << "input : ";
            if(debug) this->printSet(T);

            std::set<int> goTo = move(T, a);
            std::set<int> U = getEpsClosure(goTo);

            if(debug)std::cout << "go to states : ";
            if(debug) this->printSet(U);

            // Step 4: Check if U is not in Dstates
            if (Dstates.find(U) == Dstates.end()) {
                if(debug) std::cout << "U is not in Dstates" << std::endl;
                // Add U as an unmarked state to Dstates
                DstatesQueue.push(U);
                Dstates.insert(U);
            }

            if(debug) std::cout << "-------------------------------------------------\n";
            // Step 5: Set Dtran[T, a] = U
            Dtran[std::make_pair(T, a)] = U;
        }
    }

    this->printDFATransitionhs(Dtran);

    return Dtran;
}






