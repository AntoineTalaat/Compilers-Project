#include "infix_to_postfix.h"
#include <stack>

InfixToPostfix::InfixToPostfix() {
    this->infix = "";
}

InfixToPostfix::InfixToPostfix(std::string infix) {
    this->infix = infix;
}

int InfixToPostfix::getPriority(char c) {
	switch (c) {
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
std::string InfixToPostfix::convert() {
    int size = InfixToPostfix::infix.length();
    std::stack<char> operatorStack;
    std::string postfix = "";
    int i = 0;
        
    while(i < size) {
        char c = InfixToPostfix::infix[i];
        if(c == '\\') {
            postfix += c;
            i++;
        } 
        else if(c == '(') {
            operatorStack.push(c);
        } 
        else if(c == ')') {
            handleClosingParenthesis(operatorStack, postfix);
        } 
        else {
            handleOperandOrOperator(c, operatorStack, postfix);
        }
        i++;
    }
    // Pop remaining operators from the stack
    while(!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
};

void InfixToPostfix::handleClosingParenthesis(std::stack<char>& operatorStack, std::string& postfix) {
    while(!operatorStack.empty() && operatorStack.top() != '(') {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    if(!operatorStack.empty()) {
        operatorStack.pop(); // Pop the opening parenthesis
    }
};
void InfixToPostfix::handleOperandOrOperator(char c, std::stack<char>& operatorStack, std::string& postfix) {
    if(isOperator(c)) {
        int priority = getPriority(c);
        handleOperator(c, operatorStack, postfix, priority); 
    }
    else {
        postfix += c;
    }
};

void InfixToPostfix::handleOperator(char c, std::stack<char>& operatorStack, std::string& postfix, int priority) {
    if(operatorStack.empty() || operatorStack.top() == '(' || priority > getPriority(operatorStack.top())) {
        operatorStack.push(c);
    }
    else {
        while(!operatorStack.empty() && operatorStack.top() != '(' && priority <= getPriority(operatorStack.top())) {
            postfix += operatorStack.top();
            operatorStack.pop();
        }
        operatorStack.push(c);
    }
};

bool InfixToPostfix::isOperator(char c) {
    if(c == '|' || c == '&' || c == '*' || c == '+')    return true;
    else    return false;
};
