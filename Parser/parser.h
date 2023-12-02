#ifndef PARSER_H
#define PARSER_H

#include <regex>
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include "token.h"
#include "regular_expression.h"

class Parser {
    private:
        static std::vector<Token*> tokens;
        static const std::regex regDefRegex;
        static const std::regex regExpRegex;
        static const std::regex keywordRegex;
        static const std::regex punctuationRegex;
        static std::map<std::string, RegularExpression> Parser::regularDefinitions;
        static std::vector<Token> Parser::tokens;
        static std::vector<std::string> Parser::keywords;
        static std::vector<std::string> Parser::punctuationSymbols;

        void parseRegDef(std::string);
        void parseRegExp(std::string);
        void parseKeyword(std::string);
        void parsePunctuation(std::string);
        void tokenize(std::string);
    public:
        std::vector<Token> parseLexicalRulesFile(std::string filePath, std::vector<Token> *tokens , std::vector<std::string> * priorites, std::set<char> *alphabet);
};

#endif  // PARSER_H