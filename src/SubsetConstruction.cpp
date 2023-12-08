//
// Created by veror on 12/3/2023.
//

#include "nfa.h"
#include "subset_construction.h"
#include <iostream>


// Utils utils;
bool debug = false;
bool first = true;



SubsetConstruction::SubsetConstruction(NFA nfa) {
    this->nfa = nfa;
}


void SubsetConstruction::setAlphabet(std::set <char> alphabet) {
    this->alphabet = std::move(alphabet);
}

std::set<char> SubsetConstruction::getAlphabet() {
    return this->alphabet;
}

void SubsetConstruction::setStartStateID(int startState){
    this->startStateID = startState;
}
void SubsetConstruction::setDeadStateID(int deadState){
    this->deadStateID = deadState;
}
int SubsetConstruction::getStartStateID(){
    return this->startStateID;
}
int SubsetConstruction::getDeadStateID() {
    return this->deadStateID;
}



std::set<int> SubsetConstruction::move(std::set<int> states, char letter) {
    std::set<int> move;
    for(int state : states) {
        State currentState = this->nfa.getStatesMap().at(state);
        std::map<char, std::set<int>> transitions = currentState.getTransitions();
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
        State currentState = this->nfa.getStatesMap().at(currentStateID);
        stack.pop();

        if(visited.find(currentStateID) != visited.end())
            continue;
        visited.insert(currentStateID);
        epsClosure.insert(currentStateID);

        std::map<char, std::set<int>> transitions = currentState.getTransitions();

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







std::map <int , State> SubsetConstruction::getDFA(){
    State dead = new State();
    this->alphabet.erase(EPSILLON);

    for(char c : this->alphabet){
        dead.addTransition(c, dead.getId());
    }
    dead.setIsAccepting(false);

    std::map<int , State> DFA;
    DFA[dead.getId()] = dead;

    this->setDeadStateID(dead.getId());

    std::map<std::pair<std::set<int>, char> , std::set<int> > Dtran = this->convertNFAToDFA();
    std::map<std::set<int>, int> visitedStates;

    // for(auto& transition : Dtran){
    //     if(transition.first.first!=this->startStateEpsClosure){
    //         continue;
    //     }

    // }


    for(auto& transition : Dtran){
        const auto& inputSetOfStates = transition.first.first;
        char a = transition.first.second;
        const auto& OutputSetOfStates = transition.second;

        int fromStateID ;
        State fromState;
        int toStateID ;
        State toState;


        if(visitedStates.find(inputSetOfStates) != visitedStates.end()) {
            if(debug)  std::cout << "We worked in this input state before\n";
            fromStateID = visitedStates.at(inputSetOfStates);
        }else{
            if(debug) std::cout << "We didn't work in this input state before\n";
            Token* t = new Token("", "", INT16_MAX);
            fromState = new State() ;
            fromState.setAcceptedToken(t);

            fromStateID = fromState.getId();
            fromState.setIsAccepting(false);

            if(debug) std::cout << "fromstateID " << fromStateID << std::endl;

            // check if the inputSetOfStates contains an accepting state and set the new state is accepting if the inputSetOfStates contains an accepting state
            for (int state: inputSetOfStates) {
                if(debug) std::cout << "state " << state << " in input \n";
                if (this->nfa.getStatesMap().at(state).getIsAccepting() ) {
                    if(debug){
                        std::cout << "state " <<state << std::endl;
                        std::cout << "token "<< this->nfa.getStatesMap().at(state).getAcceptedToken()->type << " " <<
                                  this->nfa.getStatesMap().at(state).getAcceptedToken()->priority << std::endl;
                    }


                    fromState.setIsAccepting(true);

                    if(this->nfa.getStatesMap().at(state).getAcceptedToken()->priority < fromState.getAcceptedToken()->priority){
                        fromState.setAcceptedToken(this->nfa.getStatesMap().at(state).getAcceptedToken());
                    }
                }
            }

            if(this->startStateEpsClosure == inputSetOfStates && first){
                if(debug) std::cout << "first state " << fromStateID << std::endl;

                this->setStartStateID(fromStateID);
                first = false;
            }
            visitedStates[inputSetOfStates] = fromStateID;
            DFA[fromStateID] = fromState;

        }

        if(visitedStates.find(OutputSetOfStates) != visitedStates.end()) {
            if(debug)   std::cout << "We worked in this output state before\n";
            toStateID = visitedStates.at(OutputSetOfStates);
        }else{
            if(OutputSetOfStates.size() == 0){
                if(debug)   std::cout << "go to dead state\n";
                toStateID = dead.getId();

            }else{
                if(debug)  std::cout << "We didn't work in this output state before\n";
                Token* t = new Token("", "", INT16_MAX);
                toState = new State() ;
                toState.setAcceptedToken(t);
                toStateID = toState.getId();
                toState.setIsAccepting(false);

                // check if the output contains an accepting state and set the new state is accepting if the inputSetOfStates contains an accepting state
                for (int state: OutputSetOfStates) {
                    if (this->nfa.getStatesMap().at(state).getIsAccepting()) {
                        toState.setIsAccepting(true);
                        if(this->nfa.getStatesMap().at(state).getAcceptedToken()->priority < toState.getAcceptedToken()->priority){
                            toState.setAcceptedToken(this->nfa.getStatesMap().at(state).getAcceptedToken());
                        }
                    }
                }
                visitedStates[OutputSetOfStates] = toStateID;
                DFA[toStateID] = toState;
            }
        }

        //   std::cout << "from state id " << fromStateID << std::endl;
        DFA[fromStateID].addTransition(a, toStateID);
    }

    return DFA;
}



std::map< std::pair<std::set<int>, char> , std::set<int> > SubsetConstruction::convertNFAToDFA()  {
    std::queue<std::set<int>> DstatesQueue;
    std::set<std::set<int>> Dstates;
    std::map<std::set<int>, bool> marked;
    std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran;

    // Step 1: Initialize with epsilon closure of the start state and push it to queue
    int startStateID = this->nfa.getStartState().getId();
    std::set<int> startEpsClosure = epsClosure(startStateID);
    this->startStateEpsClosure = startEpsClosure;
    DstatesQueue.push(startEpsClosure);
    Dstates.insert(startEpsClosure);

    

    if(debug){
        std::cout << "start state id: " << startStateID << std::endl;
        std::cout << "start state is accepting : " << this->nfa.getStartState().getIsAccepting() << std::endl;

        if(this->nfa.getStartState().getIsAccepting()){
            std::cout << "start state token type : " << this->nfa.getStartState().getAcceptedToken()->type << std::endl;
            std::cout << "start state token priority : " << this->nfa.getStartState().getAcceptedToken()->priority << std::endl;
        }

    }


    while (!DstatesQueue.empty()) {
        std::set<int> T = DstatesQueue.front();
        DstatesQueue.pop();

        marked[T] = true;                   // Mark T

        // Step 2: Process each input symbol
        for (char a: this->alphabet) {
            // Get the set of states reachable from T on input symbol a
            std::set<int> goTo = move(T, a);
            if(goTo.size()>0){
                std::set<int> U = getEpsClosure(goTo);

                // Step 4: Check if U is not in Dstates
                if (Dstates.find(U) == Dstates.end() ) {
                    // Add U as an unmarked state to Dstates
                    DstatesQueue.push(U);
                    Dstates.insert(U);
                }

                // Step 5: Add the transition T, a, U to Dtran
                Dtran[std::make_pair(T, a)] = U;
            }else{

                Dtran[std::make_pair(T, a)] = goTo;

            }
        }
    }

    if(debug) Utils::printDFATransitionhs(Dtran);

    return Dtran;
}

std::map<int, State> SubsetConstruction::minimizeDFA(std::map<int, State>& DFA) {
    std::vector<std::set<int>> II;
    std::vector<std::set<int>> IInew;
    std::vector<std::set<int>> IIfinal;

    // Separate accepting and non-accepting states into two groups
    std::set<int> acceptingStates, nonAcceptingStates;
    for ( auto& state : DFA) {
        if (state.second.getIsAccepting()) {
            acceptingStates.insert(state.first);
        } else {
            nonAcceptingStates.insert(state.first);
        }
    }
    II.push_back(acceptingStates);
    II.push_back(nonAcceptingStates);

    while (true) {
        IInew = II;

        for (const auto& group : II) {
            std::vector<std::set<int>> subgroups;
            for (int state : group) {
                auto representative = std::find_if(subgroups.begin(), subgroups.end(),
                    [state, &DFA](const std::set<int>& subgroup) {
                        return std::all_of(subgroup.begin(), subgroup.end(),
                            [state, &DFA](int otherState) {
                                return DFA[state].getTransitions() == DFA[otherState].getTransitions();
                            });
                    });

                if (representative == subgroups.end()) {
                    subgroups.push_back({ state });
                } else {
                    representative->insert(state);
                }
            }
    //                   std::cout << "Subgroups: ";
    // for (const auto& subgroup : subgroups) {
    //     std::cout << "{";
    //     for (int state : subgroup) {
    //         std::cout << state << " ";
    //     }
    //     std::cout << "} ";
    // }
    // std::cout << std::endl;


            auto it = std::find(IInew.begin(), IInew.end(), group);
            IInew.erase(it);
            IInew.insert(IInew.end(), subgroups.begin(), subgroups.end());
        }

        if (IInew == II) {
            IIfinal = II;
            break;
        }

        II = IInew;
    }

    // Construct the minimized DFA
    std::map<int, State> minimizedDFA;
    std::map<int, std::set<int>> stateMapping;
    for (const auto& group : IIfinal) {
        // Choose a representative for the group
        int representative = *group.begin();
        //  std::cout << "Representative for Group: " << representative << std::endl;
        minimizedDFA[representative] = DFA[representative];

        // If the group contains an accepting state, mark the representative as accepting in the minimized DFA
        if (std::any_of(group.begin(), group.end(), [&DFA](int state) { return DFA[state].getIsAccepting(); })) {
            minimizedDFA[representative].setIsAccepting(true);
        }
        stateMapping[representative] = group;
    }
//  std::cout << "State Mapping: " << std::endl;
// for (const auto& entry : stateMapping) {
//     std::cout << entry.first << " : { ";
//     for (int state : entry.second) {
//         std::cout << state << " ";
//     }
//     std::cout << "}" << std::endl;
// }
    
for (auto& entry : minimizedDFA) {
    int representative = entry.first;
    auto& state = entry.second;

    for (auto& transition : state.getTransitions()) {
        char inputSymbol = transition.first;
        int nextState = *transition.second.begin();

        // Find the representative of the group containing nextState
        for (const auto& mapping : stateMapping) {
            if (mapping.second.count(nextState) > 0) {
                nextState = mapping.first;
                break;
            }
        }

        // Set the transition for the character using the representative state
        state.setTransitionForCharacter(inputSymbol, { nextState });
    }
}


    return minimizedDFA;
}
