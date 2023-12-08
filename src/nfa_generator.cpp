#include "nfa_generator.h"
#include "globals.h"
#include "operations_handler.h"
#include "infix_to_postfix.h"
#include "utils.h"

NFAGenerator::NFAGenerator() {
    // this->rulesFile = "";

};

NFAGenerator::NFAGenerator(std::string file) {
    // NFAGenerator::rulesFile = file;
};

NFA NFAGenerator::getFullNFA(std::vector<NFA> allNFAs) {
    if(allNFAs.empty())    
        throw std::invalid_argument("empty full nfa");
 
    NFA final = allNFAs.front();
    for(auto it = std::next(allNFAs.begin()); it != allNFAs.end(); ++it) {
        final = OperationsHandler::joinNFAs(final,  *it);
    }

    return final;
};

NFA NFAGenerator::generateNFAFromPostfix(std::vector<std::string> postfix) {
    Utils::printStringVector(postfix);
    // std::cout<<"\nSTARTING "<< '\n';
    std::stack<NFA> stk;   
    for (const auto& string : postfix) {
        // std::cout<<"\nhandling string:_" << string <<"_ " << stk.size() <<'\n';
        if(Globals::regularDefinitionNFA.find(string)!=Globals::regularDefinitionNFA.end()){
            // std::cout<<"push known regdef nfa " << string <<'\n';
            stk.push(Globals::regularDefinitionNFA[string]);
        }else if(InfixToPostfix::isOperatorString(string)){
            NFA  first = NFA::deepCopy(stk.top());
            std::cout<<"pop1 due to " << string <<'\n';
            std::cout<<"start " << first.getStartState().getId() <<" " << first.getFinalState().getId()<<'\n';

            Utils::printMap(first.getStatesMap());

            stk.pop();
            if(InfixToPostfix::isBinaryOperatorString(string)){
                NFA  second = NFA::deepCopy(stk.top());
                std::cout<<"start " << second.getStartState().getId() <<" " << second.getFinalState().getId()<<'\n';

                std::cout<<"pop2 due to " << string <<'\n';
                Utils::printMap(second.getStatesMap());
                stk.pop();
                NFA  generated = OperationsHandler::handleBinaryOperator(string[0],second,first);
                stk.push(generated);
                // std::cout<<"pushed binary operator nfa by " << string <<'\n';
            } else {
                NFA  generated = OperationsHandler::handleUnaryOperator(string[0],first);
                // std::cout<<"pushed unary operator nfa by " << string <<'\n';
                stk.push(generated);
            }
        } else if(string.length() == 1 || string.length()==2 && string[0]=='\\'){
            NFA  appended;
            if(string.length()==2 && string[1]=='L')
                appended = OperationsHandler::basicNFA(EPSILLON);
            else 
                appended = OperationsHandler::basicNFA(string[string.length()-1]);
            // std::cout<<"push one char nfa " << string <<'\n';
            stk.push(appended);
        }else{
            NFA appended = generateNFAFromString(string);
            // std::cout<<"push concatenated string nfa " << string <<'\n';
            stk.push(appended);
        }
    }
    // std::cout<<"Final "<<stk.size()<< '\n'<<'\n';
    assert(stk.size()==1);
    return stk.top();
};

NFA NFAGenerator::generateNFAFromString(std::string s) {
    NFA first = OperationsHandler::basicNFA(s[0]);
    for(int i=1;i<s.length();i++){
        NFA  next = OperationsHandler::basicNFA(s[i]);
        first = OperationsHandler::concatOp(first,next);
    }
    
    return first;
}