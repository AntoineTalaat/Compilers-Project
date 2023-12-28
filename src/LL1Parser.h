#ifndef LL1_PARSER_H
#define LL1_PARSER_H

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include "token.h"

class LL1Parser {
public:
    LL1Parser(
        const std::map<std::string, std::map<std::string, std::vector<std::string>>>& parsingTable
    );

    void parse(
        const std::vector<Token>& tokens,
        const std::string& startSymbol
    );
    void saveToCSV(const std::string& filename);

private:
    const std::map<std::string, std::map<std::string, std::vector<std::string>>> parsingTable;

    std::string stackToString(const std::stack<std::string>& stack);
    std::string inputToString(const std::vector<Token>& tokens, size_t index);
    std::vector<std::vector<std::string>> csvOutput;
};

#endif // LL1_PARSER_H
