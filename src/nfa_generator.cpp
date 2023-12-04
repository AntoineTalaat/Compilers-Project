#include "nfa_generator.h"
#include "globals.h"
#include "operations_handler.h"
#include "infix_to_postfix.h"


NFAGenerator::NFAGenerator() {
    // this->rulesFile = "";

};

NFAGenerator::NFAGenerator(std::string file) {
    // NFAGenerator::rulesFile = file;
};

NFA* NFAGenerator::getFullNFA(std::vector<NFA*> allNFAs) {
    if(allNFAs.empty())    return nullptr;
    NFA* final = allNFAs.front();
    for(auto it = std::next(allNFAs.begin()); it != allNFAs.end(); ++it) {
        final = OperationsHandler::joinNFAs(final, *it);
    }

    return final;
};

NFA* NFAGenerator::generateNFAFromPostfix(std::vector<std::string> postfix) {
    std::stack<NFA*> stk;   
    for (const auto& string : postfix) {
        if(!InfixToPostfix::isOperatorString(string)){
            // either named regular definition, or letters 
            if(regularDefinitionNFA.find(string)!=regularDefinitionNFA.end()){
                // retrieve the nfa from the map
                stk.push(regularDefinitionNFA[string]);
            }else if(InfixToPostfix::isOperatorString(string)){
                NFA* first = stk.top();
                stk.pop();
                if(InfixToPostfix::isBinaryOperatorString(string)){
                    NFA* second = stk.top();
                    stk.pop();
                    NFA* generated = OperationsHandler::handleBinaryOperator(string[0],first,second);
                    stk.push(generated);
                } else {
                    NFA* generated = OperationsHandler::handleUnaryOperator(string[0],first);
                    stk.push(generated);
                }
            } else if(string.length() == 1 || string.length()==2 && string[0]=='\\'){
                //either one letter,
                // or letter after backslash
                NFA* appended = OperationsHandler::basicNFA(string[string.length()-1]);
                stk.push(appended);
            }else{
                //stacked letters
                // IMPORTANT 
                std::cout<<"got a postfix string: " << string <<"\n";
                NFA* appended = generateNFAFromString(string);
                stk.push(appended);
            }
        }
    }
    assert(stk.size()==1);
    return stk.top();
    
};

NFA* NFAGenerator::generateNFAFromString(std::string s) {
    NFA* first = OperationsHandler::basicNFA(s[0]);
    for(int i=1;i<s.length();i++){
        NFA* next = OperationsHandler::basicNFA(s[i]);
        first = OperationsHandler::concatOp(first,next);
    }
    return first;
}