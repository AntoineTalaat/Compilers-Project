#include "operations_handler.h"



NFA OperationsHandler::basicNFA(char c) {
    State start;
    State final;
    start.addTransition(c,final.getId());
    
    NFA oneCharNFA;
    oneCharNFA.setStartState(start);
    oneCharNFA.setFinalState(final);
    
    return oneCharNFA;
};



NFA OperationsHandler::unionOp(NFA first, NFA second) {
    NFA newNfa;
    State& firstStart = first.getStartState();
    State& firstFinal = first.getFinalState();
    State& secondStart = second.getStartState();
    State& secondFinal = second.getFinalState();
    State start ;     // set new start state for both NFAs
    start.addTransition(EPSILLON, firstStart.getId());
    // std::cout<<"h "  <<'\n';
    start.addTransition(EPSILLON, secondStart.getId());
    // std::cout<<"i " <<'\n';

    State final; // set new final state for both NFAs
    first.setFinalState(final);
    second.setFinalState(final);
    firstFinal.addTransition(EPSILLON, final.getId());
    secondFinal.addTransition(EPSILLON, final.getId());
    firstFinal.setIsAccepting(false);
    secondFinal.setIsAccepting(false);
    newNfa.setStartState(start);
    newNfa.setFinalState(final);
    newNfa.setBatchStates(first.getStatesMap());
    newNfa.setBatchStates(second.getStatesMap());

    return newNfa;
};

NFA  OperationsHandler::concatOp(NFA  first, NFA  second) {
    NFA newNfa;
    State&  firstStart = first.getStartState();
    State&  firstFinal = first.getFinalState();
    State&  secondStart = second.getStartState();
    State&  secondFinal = second.getFinalState();

    firstFinal.setIsAccepting(false);
    firstFinal.addTransition(EPSILLON, secondStart.getId());

    newNfa.setStartState(firstStart);
    newNfa.setFinalState(secondFinal);

    newNfa.setBatchStates(first.getStatesMap());
    newNfa.setBatchStates(second.getStatesMap());

    return newNfa;
};

NFA  OperationsHandler::kleeneClosureOp(NFA  nfa) {
    nfa = positiveClosureOp(nfa);
    (nfa.getStartState()).addTransition(EPSILLON, nfa.getFinalState().getId());
    return nfa;
};





NFA  OperationsHandler::positiveClosureOp(NFA  nfa) {
    State  start;
    State  final;

    State&  oldStart = nfa.getStartState();
    State&  oldFinal = nfa.getFinalState();
    oldFinal.setIsAccepting(false);
    // nfa 
//                            <<<<<<<<<<<<<<< 
    //                oldStart >>   stuff >>  oldFinalx    
    //    start   >>                                     >>    final
    start.addTransition(EPSILLON, oldStart.getId());
    oldFinal.addTransition(EPSILLON, oldStart.getId());
    oldFinal.addTransition(EPSILLON, final.getId());

    nfa.setStartState(start);
    nfa.setFinalState(final);

    return nfa;
};

NFA  OperationsHandler::rangeOp(char from, char to) {
    State newStart;
    State newEnd;
    NFA  nfa;
    nfa.setStartState(newStart);
    nfa.setFinalState(newEnd);

    State&  s1 = nfa.getStartState();
    State&  s2 = nfa.getFinalState();
    for(char c = from; c <= to; c++) {
        State s;
        State e;
        NFA newNfa;
        newNfa.setStartState(s);
        newNfa.setFinalState(e);
        newNfa.getStartState().addTransition(c, newNfa.getFinalState().getId());
        nfa.getStartState().addTransition(EPSILLON, newNfa.getStartState().getId());
        newNfa.getFinalState().addTransition(EPSILLON, nfa.getFinalState().getId());
        nfa.setBatchStates(newNfa.getStatesMap());
    }
    return nfa;
};

NFA  OperationsHandler::rangeOp(NFA from, NFA to) {
    State s;
    State e;
    NFA nfa;
    nfa.setStartState(s);
    nfa.setFinalState(e);
    State  s1 = nfa.getStartState();
    State  s2 = nfa.getFinalState();


    assert(from.getStartState().getTransitions().size() == 1);
    assert(to.getStartState().getTransitions().size() == 1);

    // Get the entry from the map
    std::pair<char, std::set<int>> entryFirst =  *from.getStartState().getTransitions().begin();
    std::pair<char, std::set<int>> entryLast  =  *to.getStartState().getTransitions().begin();

    assert(entryFirst.second.size()==1);
    assert( entryLast.second.size()==1);;

    for(char c = entryFirst.first; c <= entryLast.first; c++) {
        State ns;
        State ne;
        NFA newNfa;
        newNfa.setStartState(ns);
        newNfa.setFinalState(ne);
        newNfa.getStartState().addTransition(c, newNfa.getFinalState().getId());
        nfa.getStartState().addTransition(c, nfa.getFinalState().getId());
        newNfa.getFinalState().addTransition(EPSILLON, nfa.getFinalState().getId());
        nfa.setBatchStates(newNfa.getStatesMap());
    }
    return nfa;
};

 NFA  OperationsHandler::joinNFAs(NFA  first, NFA  second) {
    State start;
    NFA  newNfa;
    newNfa.setStartState(start);
    newNfa.getStartState().addTransition(EPSILLON, first.getStartState().getId());
    newNfa.getStartState().addTransition(EPSILLON, second.getStartState().getId());

    newNfa.setBatchStates(first.getStatesMap());
    newNfa.setBatchStates(second.getStatesMap());

    return newNfa;
 };

NFA  OperationsHandler::handleBinaryOperator(char op,NFA  first, NFA  second) {
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
        std::cout<<"Unknown operator received ::: "<< op<<'\n';
        throw std::invalid_argument("received unknown operator");
        break;
    }
}

NFA  OperationsHandler::handleUnaryOperator(char op,NFA  first) {
    switch (op)
    {
    case '+':
        return OperationsHandler::positiveClosureOp(first);
        break;
    case '*':
        return OperationsHandler::kleeneClosureOp(first);
        break;
    default:
        std::cout<<"Unknown operator received ::: "<< op<<'\n';
        throw std::invalid_argument("received unknown operator");
        break;
    }
}

