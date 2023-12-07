#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include <bits/stdc++.h>
#include "token.h" 
#include "nfa.h"
#include "state.h"
class LexicalAnalyzer {
    private:
    public:
    static std::vector<Token> getTokens(std::string input,NFA dfa );  // to be replaced with DFA class
    static std::vector<Token> getTokens(std::string input, int startStateID,int deadStateID, std::map< int , State> dfaMap);
    
};
#endif  // LEXICAL_ANALYZER