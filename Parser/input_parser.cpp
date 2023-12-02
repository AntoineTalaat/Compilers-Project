#include "input_parser.h"

const std::regex InputParser::regDefRegex = std::regex(R"((\w+)\s*=\s*(\w+))");
const std::regex InputParser::regExpRegex = std::regex(R"((\w+)\s*:\s*(\w+))");
const std::regex InputParser::keywordRegex = std::regex(R"(\{(\w+)\})");
const std::regex InputParser::punctuationRegex = std::regex(R"(\[(\w+)\])");
static std::vector<Token> tokens;

std::map<std::string, RegularExpression> InputParser::regularDefinitions;
std::vector<std::string> InputParser::keywords;
std::vector<std::string> InputParser::punctuationSymbols;

std::vector<Token> InputParser::parseLexicalRulesFile(std::string filePath, std::vector<Token> *tokens , std::vector<std::string> * priorites, std::set<char> *alphabet) {
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
};

void InputParser::tokenize(std::string line) {
    std::cout << line;
    if(regex_match(line, regDefRegex))            parseRegDef(line);
    else if(regex_match(line, regExpRegex))       parseRegExp(line);
    else if(regex_match(line, keywordRegex))      parseKeyword(line);
    else if(regex_match(line, punctuationRegex))  parsePunctuation(line);
    else { 
        throw std::invalid_argument("received unknownnnnn rule typeeeeee");
    }
};
void InputParser::parseRegDef(std::string) {

};

void InputParser::parseRegExp(std::string) {

};
void InputParser::parseKeyword(std::string line) {
  
};
   
            
void InputParser::parsePunctuation(std::string line) {
};
