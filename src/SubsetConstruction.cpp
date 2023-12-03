//
// Created by veror on 12/3/2023.
//

#include "nfa.h"
#include "subset_construction.h"


SubsetConstruction::SubsetConstruction(NFA nfa) {
    this->nfa = nfa;
    this->stateMap = nfa.getStatesMap();
}

void SubsetConstruction::setStatesMap(std::map<int , State* > stateMap) {
    this->stateMap = stateMap;
}

void SubsetConstruction::setAlphabet(std::set <char> alphabet) {
    this->alphabet = alphabet;
}



std::set<int> SubsetConstruction::move(std::set<int> states, char letter) {
    std::set<int> move;
    for(int state : states) {
        State* currentState = this->stateMap.at(state);
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
        State* currentState = this->stateMap.at(currentStateID);
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


std::map<std::pair<std::set<int>, char>, std::set<int>> SubsetConstruction::convertNFAToDFA()  {
    std::queue<std::set<int>> DstatesQueue;
    std::set<std::set<int>> Dstates;
    std::map<std::set<int>, bool> marked;
    std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran;

    // Step 1: Initialize with epsilon closure of the start state
    int startStateID = this->nfa.getStartState()->getId();
    std::set<int> startEpsClosure = epsClosure(startStateID);

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
            std::set<int> goTo = move(T, a);
            std::set<int> U = getEpsClosure(goTo);

            // Step 4: Check if U is not in Dstates
            if (Dstates.find(U) == Dstates.end()) {
                // Add U as an unmarked state to Dstates
                DstatesQueue.push(U);
                Dstates.insert(U);
            }

            // Step 5: Set Dtran[T, a] = U
            Dtran[std::make_pair(T, a)] = U;
        }
    }

    return Dtran;
}


/*
 *   // Output the resulting DFA
    std::cout << "DFA States:\n";
    for (const auto& stateSet : Dstates) {
        std::cout << "{";
        for (int state : stateSet) {
            std::cout << state << " ";
        }
        std::cout << "}\n";
    }

    std::cout << "DFA Transitions:\n";
    for (const auto& transition : Dtran) {
        const auto& T = transition.first.first;
        char a = transition.first.second;
        const auto& U = transition.second;
        std::cout << "Dtran[{" << *T.begin() << "}, " << a << "] = {" << *U.begin() << "}\n";
    }
 */




