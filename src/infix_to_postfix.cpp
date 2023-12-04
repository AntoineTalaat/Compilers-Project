#include "infix_to_postfix.h"
#include <stack>

InfixToPostfix::InfixToPostfix() {
    // this->infix = "";
}

InfixToPostfix::InfixToPostfix(std::string infix) {
    // this->infix = infix;
}

int InfixToPostfix::getPriority(char c) {
	switch (c) {
        case '-':
            return 4;
        case '+':
            return 3;
        case '*':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
        default:
            return 0;
	}
}

// convert infix expression to postfix using a stack
std::vector<std::string> InfixToPostfix::convert(std::vector<std::string> infix) {
    int size = infix.size();
    std::stack<char> operatorStack;
    std::vector<std::string> postfix;
    int i = 0;
    bool nextConcat = false;

    while(i < size) {
        std::string s = infix[i];

        if(s.compare("(")==0){
            if(nextConcat){
                handleOperator('&',operatorStack,postfix,getPriority('&'));
            }
            operatorStack.push(s[0]);
            nextConcat=false;
        } else if(s.compare(")")==0){
            handleClosingParenthesis(operatorStack, postfix);
            nextConcat=true;
        } else {
            handleOperandOrOperator(s,nextConcat, operatorStack, postfix);
        }
        i++;
    }
    // Pop remaining operators from the stack
    while(!operatorStack.empty()) {
        std::string charStr = "";
        charStr+=operatorStack.top();
        postfix.push_back(charStr);
        operatorStack.pop();
    }

    for (const auto& line : postfix) {
        std::cout <<line<<" , ";
    }
    std::cout<<'\n';

    return postfix;
};

void InfixToPostfix::handleClosingParenthesis(std::stack<char>& operatorStack,
                                              std::vector<std::string>& postfix) {
    while(!operatorStack.empty() && operatorStack.top() != '(') {
        std::string charStr = "";
        charStr+=operatorStack.top();
        postfix.push_back(charStr);
        operatorStack.pop();
    }

    if(!operatorStack.empty()) {
        operatorStack.pop(); // Pop the opening parenthesis
    }
};
void InfixToPostfix::handleOperandOrOperator(std::string s,
                                             bool& nextConcat,
                                             std::stack<char>& operatorStack,  
                                             std::vector<std::string>& postfix) {
    if(isOperatorString(s)) {
        int priority = getPriority(s[0]);
        handleOperator(s[0], operatorStack, postfix, priority); 
        if(isUnaryOperatorString(s)) nextConcat = true;
        else nextConcat=false;
    }
    else {
        if(nextConcat){
            handleOperator('&',operatorStack,postfix,getPriority('&'));
        }
        postfix.push_back(s);
        nextConcat=true;
    }
};

void InfixToPostfix::handleOperator(char c, std::stack<char>& operatorStack, std::vector<std::string>& postfix, int priority) {
    // std::cout<<"handling op "<<c<<'\n';
    if(operatorStack.empty() || operatorStack.top() == '(' || priority > getPriority(operatorStack.top())) {
        operatorStack.push(c);
    }
    else {
        while(!operatorStack.empty() && operatorStack.top() != '(' && priority <= getPriority(operatorStack.top())) {
            std::string charStr = "";
            charStr+=operatorStack.top();
            postfix.push_back(charStr);
            operatorStack.pop();
        }
        operatorStack.push(c);
    }
};

bool InfixToPostfix::isOperatorString(std::string s) {
    return (s.size() == 1) && (InfixToPostfix::isOperator(s[0]));
};

bool InfixToPostfix::isOperator(char c) {
    return (c == '|' || c == '&' || c == '*' || c == '+'  || c=='-') ;
};

bool InfixToPostfix::isBinaryOperatorString(std::string s) {
    return (s.size() == 1) && (s[0] == '|' || s[0] == '&' || s[0]=='-') ;
};

bool InfixToPostfix::isUnaryOperatorString(std::string s){
    return (s.size() == 1) && (s[0]=='+' || s[0]=='*');
}
