#include "operations_handler.h"

NFA* OperationsHandler::unionOp(NFA* first, NFA* second) {
    NFA* newNfa = new NFA();
    State* firstStart = first->getStartState();
    State* firstFinal = first->getFinalState();

    State* secondStart = second->getStartState();
    State* secondFinal = second->getFinalState();

    State* start = new State();     // set new start state for both NFAs
    first->setStartState(start);
    second->setStartState(start);

    start->addTransition(EPSILLON, firstStart->getId());
    start->addTransition(EPSILLON, secondStart->getId());

    State* final = new State(true); // set new final state for both NFAs
    first->setFinalState(final);
    second->setFinalState(final);

    firstFinal->addTransition(EPSILLON, final->getId());
    secondFinal->addTransition(EPSILLON, final->getId());

    firstFinal->setIsAccepting(false);
    secondFinal->setIsAccepting(false);

    newNfa->setStartState(start);
    newNfa->setFinalState(final);
    newNfa->setBatchStates(first->getStatesMap());
    newNfa->setBatchStates(second->getStatesMap());

    return newNfa;
};

NFA* OperationsHandler::concatOp(NFA* first, NFA* second) {
    NFA* newNfa = new NFA();

    State* firstStart = first->getStartState();
    State* firstFinal = first->getFinalState();

    State* secondStart = second->getStartState();
    State* secondFinal = second->getFinalState();

    firstFinal->setIsAccepting(false);
    secondFinal->setIsAccepting(false);

    firstFinal->addTransition(EPSILLON, secondStart->getId());
    State* final = new State(true);
    secondFinal->addTransition(EPSILLON, final->getId());

    newNfa->setFinalState(final);
    newNfa->setBatchStates(first->getStatesMap());
    newNfa->setBatchStates(second->getStatesMap());
    // deallocate first and second
    return newNfa;
};

NFA* OperationsHandler::kleeneClosureOp(NFA* nfa) {
    nfa = positiveCloruseOp(nfa);
    nfa->getStartState()->addTransition(EPSILLON, nfa->getFinalState()->getId());
    
    return nfa;
};

NFA* OperationsHandler::positiveCloruseOp(NFA* nfa) {
    State* start = new State();
    State* final = new State(true);

    State* oldStart = nfa->getStartState();
    State* oldFinal = nfa->getFinalState();
    oldFinal->setIsAccepting(false);

    start->addTransition(EPSILLON, oldStart->getId());
    oldFinal->addTransition(EPSILLON, oldStart->getId());
    oldFinal->addTransition(EPSILLON, final->getId());

    nfa->setStartState(start);
    nfa->setFinalState(final);

    return nfa;
};

NFA* OperationsHandler::rangeOp(char from, char to) {
    NFA* nfa = new NFA();
    
    for(char c = from; c <= to; c++) {
        NFA* newNfa = new NFA();
        newNfa->getStartState()->addTransition(c, newNfa->getFinalState()->getId());
        nfa->getStartState()->addTransition(EPSILLON, newNfa->getStartState()->getId());
        newNfa->getFinalState()->addTransition(EPSILLON, nfa->getFinalState()->getId());
        nfa->setBatchStates(newNfa->getStatesMap());
    }
    return nfa;
};

 NFA* OperationsHandler::joinNFAs(NFA* first, NFA* second) {
    NFA* newNfa = new NFA();
    newNfa->getStartState()->addTransition(EPSILLON, first->getStartState()->getId());
    newNfa->getStartState()->addTransition(EPSILLON, second->getStartState()->getId());

    newNfa->setBatchStates(first->getStatesMap());
    newNfa->setBatchStates(second->getStatesMap());

    return newNfa;
 };