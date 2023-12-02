#include "parser.h"

const std::regex Parser::regDefRegex = std::regex(R"((\w+)\s*=\s*(\w+))");
const std::regex Parser::regExpRegex = std::regex(R"((\w+)\s*:\s*(\w+))");
const std::regex Parser::keywordRegex = std::regex(R"(\{(\w+)\})");
const std::regex Parser::punctuationRegex = std::regex(R"(\[(\w+)\])");
static std::vector<Token> tokens;

std::map<std::string, RegularExpression> Parser::regularDefinitions;
std::vector<std::string> Parser::keywords;
std::vector<std::string> Parser::punctuationSymbols;

std::vector<Token> Parser::parseLexicalRulesFile(std::string filePath, std::vector<Token> *tokens , std::vector<std::string> * priorites, std::set<char> *alphabet) {
    std::string line;
        std::ifstream file(filePath);
        if (file.is_open()) {
            while (getline(file, line)) {
                if(line.empty())    continue;
                tokenize(line);
            }
            file.close();
        }
        return;
}

void Parser::tokenize(std::string line) {
    std::cout << line;
    if(regex_match(line, regDefRegex))            parseRegDef(line);
    else if(regex_match(line, regExpRegex))       parseRegExp(line);
    else if(regex_match(line, keywordRegex))      parseKeyword(line);
    else if(regex_match(line, punctuationRegex))  parsePunctuation(line);
    else { 
        throw std::invalid_argument("received unknownnnnn rule typeeeeee");
    }
};
void Parser::parseRegDef(std::string) {

};

void Parser::parseRegExp(std::string) {

};
void Parser::parseKeyword(std::string line) {
  
};
   
            
void Parser::parsePunctuation(std::string line) {
};
