#include "operations_handler.h"



NFA* OperationsHandler::basicNFA(char c) {
    State* start = new State();
    State* final = new State();
    start->addTransition(c,final->getId());
    
    NFA* oneCharNFA = new NFA();
    oneCharNFA->setStartState(start);
    oneCharNFA->setFinalState(final);
    
    return oneCharNFA;
};



NFA* OperationsHandler::unionOp(NFA* first, NFA* second) {
    NFA* newNfa = new NFA();
    // std::cout<<"a " <<'\n';
    State* firstStart = first->getStartState();
    // std::cout<<"b " <<'\n';
    State* firstFinal = first->getFinalState();
    // std::cout<<"c " <<'\n';
    State* secondStart = second->getStartState();
        // std::cout<<"d " <<'\n';
    State* secondFinal = second->getFinalState();
    // std::cout<<"e " <<'\n';
    State* start = new State();     // set new start state for both NFAs
    // first->setStartState(start);
        // std::cout<<"f " <<'\n';
    // second->setStartState(start);
    // std::cout<<"g " <<'\n';
    start->addTransition(EPSILLON, firstStart->getId());
        std::cout<<"h " << secondStart <<'\n';

    start->addTransition(EPSILLON, secondStart->getId());
    std::cout<<"i " <<'\n';

    State* final = new State(true); // set new final state for both NFAs
        // std::cout<<"j " <<'\n';
    first->setFinalState(final);
        // std::cout<<"k " <<'\n';
    second->setFinalState(final);
    // std::cout<<"l " <<'\n';
    firstFinal->addTransition(EPSILLON, final->getId());
    // std::cout<<"m " <<'\n';
    secondFinal->addTransition(EPSILLON, final->getId());
    // std::cout<<"n " <<'\n';
    firstFinal->setIsAccepting(false);
        // std::cout<<"o " <<'\n';
    secondFinal->setIsAccepting(false);
        // std::cout<<"p " <<'\n';
    newNfa->setStartState(start);
        // std::cout<<"q " <<'\n';

    newNfa->setFinalState(final);
        // std::cout<<"r " <<'\n';
    newNfa->setBatchStates(first->getStatesMap());
        // std::cout<<"s " <<'\n';
    newNfa->setBatchStates(second->getStatesMap());

    return newNfa;
};

NFA* OperationsHandler::concatOp(NFA* first, NFA* second) {
    NFA* newNfa = new NFA();
    State* firstStart = first->getStartState();
    // std::cout<<"c " <<'\n';
    State* firstFinal = first->getFinalState();
    // std::cout<<"d " <<'\n';
    State* secondStart = second->getStartState();
    // std::cout<<"e " <<'\n';
    State* secondFinal = second->getFinalState();
    // std::cout<<"f " <<'\n';

    firstFinal->setIsAccepting(false);
    std::cout<<"g " <<'\n';
    std::cout<<"g2 " << secondStart->getId() <<'\n';

    firstFinal->addTransition(EPSILLON, secondStart->getId());
    std::cout<<"h " <<'\n';


    newNfa->setStartState(firstStart);

    newNfa->setFinalState(secondFinal);
    std::cout<<"i " <<'\n';

    newNfa->setBatchStates(first->getStatesMap());
    // std::cout<<"j " <<'\n';

    newNfa->setBatchStates(second->getStatesMap());
    // std::cout<<"k " <<'\n';

    return newNfa;
};

NFA* OperationsHandler::kleeneClosureOp(NFA* nfa) {
    nfa = positiveClosureOp(nfa);
    nfa->getStartState()->addTransition(EPSILLON, nfa->getFinalState()->getId());
    
    return nfa;
};





NFA* OperationsHandler::positiveClosureOp(NFA* nfa) {
    State* start = new State();
    State* final = new State(true);

    State* oldStart = nfa->getStartState();
    State* oldFinal = nfa->getFinalState();
    oldFinal->setIsAccepting(false);

    // nfa 
//                            <<<<<<<<<<<<<<< 
    //                oldStart >>   stuff >>  oldFinalx    
    //    start   >>                                     >>    final


    start->addTransition(EPSILLON, oldStart->getId());
    oldFinal->addTransition(EPSILLON, oldStart->getId());
    oldFinal->addTransition(EPSILLON, final->getId());

    nfa->setStartState(start);
    nfa->setFinalState(final);

    return nfa;
};

NFA* OperationsHandler::rangeOp(char from, char to) {
    NFA* nfa = new NFA(new State(), new State());
    State* s1 = nfa->getStartState();
    State* s2 = nfa->getFinalState();
    for(char c = from; c <= to; c++) {
        NFA* newNfa = new NFA(new State(), new State());
        newNfa->getStartState()->addTransition(c, newNfa->getFinalState()->getId());
        nfa->getStartState()->addTransition(EPSILLON, newNfa->getStartState()->getId());
        newNfa->getFinalState()->addTransition(EPSILLON, nfa->getFinalState()->getId());
        nfa->setBatchStates(newNfa->getStatesMap());
    }
    return nfa;
};

NFA* OperationsHandler::rangeOp(NFA* from, NFA* to) {
    NFA* nfa = new NFA(new State(), new State());
    State* s1 = nfa->getStartState();
    State* s2 = nfa->getFinalState();


    assert(from->getStartState()->getTransitions().size() == 1);
    assert(to->getStartState()->getTransitions().size() == 1);

    // Get the entry from the map
    std::pair<char, std::set<int>> entryFirst = *from->getStartState()->getTransitions().begin();
    std::pair<char, std::set<int>> entryLast  = *to->getStartState()->getTransitions().begin();

    assert(entryFirst.second.size()==1);
    assert( entryLast.second.size()==1);;

    for(char c = entryFirst.first; c <= entryLast.first; c++) {
        NFA* newNfa = new NFA(new State(), new State());
        newNfa->getStartState()->addTransition(c, newNfa->getFinalState()->getId());
        nfa->getStartState()->addTransition(c, nfa->getFinalState()->getId());
        newNfa->getFinalState()->addTransition(EPSILLON, nfa->getFinalState()->getId());
        nfa->setBatchStates(newNfa->getStatesMap());
    }
    return nfa;
};

 NFA* OperationsHandler::joinNFAs(NFA* first, NFA* second) {
    NFA* newNfa = new NFA(new State());
    newNfa->getStartState()->addTransition(EPSILLON, first->getStartState()->getId());
    newNfa->getStartState()->addTransition(EPSILLON, second->getStartState()->getId());

    newNfa->setBatchStates(first->getStatesMap());
    newNfa->setBatchStates(second->getStatesMap());

    return newNfa;
 };

NFA* OperationsHandler::handleBinaryOperator(char op,NFA* first, NFA* second) {
    switch (op)
    {
    case '&':
        // std::cout<<"before & "  <<'\n';
        return OperationsHandler::concatOp(first,second);
        break;
    case '-':
        return OperationsHandler::rangeOp(first,second);
        break;
    case '|':
        return OperationsHandler::unionOp(first,second);
        break;
    
    default:
        std::cout<<"Unknown operator received"<<'\n';
        break;
    }
    return nullptr;
}

NFA* OperationsHandler::handleUnaryOperator(char op,NFA* first) {
    switch (op)
    {
    case '+':
        return OperationsHandler::positiveClosureOp(first);
        break;
    case '*':
        return OperationsHandler::kleeneClosureOp(first);
        break;

    
    default:
        std::cout<<"Unknown operator received"<<'\n';
        break;
    }
    return nullptr;
}

