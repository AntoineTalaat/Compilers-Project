#ifndef OPERATIONS_HANDELR_H
#define OPERATIONS_HANDLER_H

#include <string>
#include "nfa.h"
#include "globals.h"
#include "state.h"
class OperationsHandler {
    private:
        
    public:
        static NFA* unionOp(NFA* first, NFA* second);
        static NFA* concatOp(NFA* first, NFA* second);
        static NFA* kleeneClosureOp(NFA* nfa);
        static NFA* positiveCloruseOp(NFA* nfa);
        static NFA* rangeOp(char from, char to);
        static NFA* joinNFAs(NFA* first, NFA* second);
};

#endif  // OPREATIONS_HANDLER_H