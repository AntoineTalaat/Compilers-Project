#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include <string>
#include <stack>

class InfixToPostfix {
    private:
        std::string infix;
        static int  getPriority(char c);
        static void handleClosingParenthesis(std::stack<char>& operatorStack, std::string& postfix);
        static void handleOperandOrOperator(char c, std::stack<char>& operatorStack, std::string& postfix);
        static void handleOperator(char ch, std::stack<char>& operatorStack, std::string& postfix, int priority);
        static bool isOperator(char c);
        
    public:
        InfixToPostfix();
        InfixToPostfix(std::string infix);
        std::string convert();
};
#endif  // INFIX_TO_POSTFIX_H