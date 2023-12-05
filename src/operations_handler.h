#ifndef OPERATIONS_HANDELR_H
#define OPERATIONS_HANDLER_H

#include <string>
#include "nfa.h"
#include "globals.h"
#include "state.h"
class OperationsHandler {
    
    public:
        static NFA unionOp(NFA first, NFA second);
        static NFA concatOp(NFA first, NFA second);
        static NFA kleeneClosureOp(NFA nfa);
        static NFA positiveClosureOp(NFA nfa);
        static NFA rangeOp(char from, char to);
        static NFA rangeOp(NFA from, NFA to);
        static NFA joinNFAs(NFA first, NFA second);
        static NFA basicNFA(char c);  
        static NFA handleBinaryOperator(char op,NFA first, NFA second);
        static NFA handleUnaryOperator(char op,NFA first);
};

#endif  // OPREATIONS_HANDLER_H