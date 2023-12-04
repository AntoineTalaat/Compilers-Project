#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include <bits/stdc++.h>
#include <stack>

class InfixToPostfix {
    private:
        std::vector<std::string> infix;
        static int  getPriority(char c);
        static void handleClosingParenthesis(std::stack<char>& operatorStack,  std::vector<std::string>& postfix);
        static void handleOperandOrOperator(std::string s, bool& nextConcat, std::stack<char>& operatorStack, std::vector<std::string>& postfix);
        static void handleOperator(char ch, std::stack<char>& operatorStack, std::vector<std::string>& postfix, int priority);

    public:
        InfixToPostfix();
        InfixToPostfix(std::string infix);
        static std::vector<std::string> convert(std::vector<std::string> infix);
        static bool isOperatorString(std::string s);
        static bool isOperator(char c);
        static bool isBinaryOperatorString(std::string s);
        static bool isUnaryOperatorString(std::string s);
};
#endif  // INFIX_TO_POSTFIX_H