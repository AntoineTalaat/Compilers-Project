#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <bits/stdc++.h>
#include <algorithm>
#include "token.h"
#include "utils.h"
#include "nfa.h"
#include "infix_to_postfix.h"
#include "nfa_generator.h"
class InputParser
{
private:
    static std::vector<Token *> tokens;
    static const std::regex regDefRegex;
    static const std::regex regExpRegex;
    static const std::regex keywordRegex;
    static const std::regex punctuationRegex;
    static std::vector<std::string> keywords;
    static std::vector<std::string> punctuationSymbols;

    void parseRegDef(std::string);
    void parseRegExp(std::string, int);
    void parseKeyword(std::string);
    void parsePunctuation(std::string);

public:
    std::vector<NFA> allNFAs;
    void tokenize(std::string, int);
    std::vector<std::string> generateInfix(std::string s);
};

#endif // INPUT_PARSER_H