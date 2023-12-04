#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H


#include <bits/stdc++.h>
#include <algorithm>
#include "token.h"
#include "utils.h"
#include "infix_to_postfix.h"
#include "regular_expression.h"

class InputParser {
    private:
        static std::vector<Token*> tokens;
        static const std::regex regDefRegex;
        static const std::regex regExpRegex;
        static const std::regex keywordRegex;
        static const std::regex punctuationRegex;
        static std::map<std::string, RegularExpression> regularDefinitions;
        static std::vector<std::string> keywords;
        static std::vector<std::string> punctuationSymbols;

        void parseRegDef(std::string);
        void parseRegExp(std::string);
        void parseKeyword(std::string);
        void parsePunctuation(std::string);
    public:
        // InputParser();
        void tokenize(std::string);
        std::vector<std::string>* generateInfix(std::string s);
        std::vector<Token> parseLexicalRulesFile(std::string filePath, std::vector<Token> *tokens , std::vector<std::string> * priorites, std::set<char> *alphabet);
};

#endif  // INPUT_PARSER_H