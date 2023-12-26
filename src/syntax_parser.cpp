#include "syntax_parser.h"
#include "globals.h"
// const std::regex PRODUCTION_RULE_REGEX(R"(^ *[A-Z_]+ *::= *('[a-z]'|[A-Z_]| |\x5C[L]|\\|)+$)");

SyntaxParser::SyntaxParser(string rulesStr){
    rulesStr =  Utils::trim(rulesStr);
    vector<string> rules = Utils::splitString(rulesStr,'#');
    if(rules[0] == "") rules.erase(rules.begin());
    bool isStart = true;
    for (int i=0; i<rules.size(); i++) {
        parseSyntacticRule(rules[i], isStart);
        isStart = false;
    }
}

void SyntaxParser::parseSyntacticRule(string rule, bool first = false){
    // assert(std::regex_match(rule, PRODUCTION_RULE_REGEX));
    size_t indexOfEqual = rule.find("::=");
    assert(indexOfEqual != std::string::npos);
    std::string part1 = rule.substr(0, indexOfEqual);
    std::string part2 = rule.substr(indexOfEqual + 3);
    std::string lhs = Utils::trim(part1);    
    if(first)   Globals::START_SYMBOL = lhs;      
    std::string rhs = Utils::trim(part2);  
    this->nonTerminals.insert(lhs);
    this->productions[lhs] = parseSyntaxRuleRHS(rhs);
}

vector<vector<string>> SyntaxParser::parseSyntaxRuleRHS(string rhs){
    vector<vector<string>> productionsVec;
    vector<string> productionStrs = Utils::splitString(rhs,'|');
    for (const auto &str : productionStrs){
        string trimmed = Utils::trim(str); //TODO make trim function able to trim \n 
        vector<string> terminalsOrNonTerminals = Utils::splitString(trimmed,' ');
        vector<string> toBeInserted;
        for(const auto &element : terminalsOrNonTerminals){
            if(!this->isTerminalString(element) && !this->isEpsillon(element))
                this->nonTerminals.insert(element);
            if(this->isEpsillon(element)) toBeInserted.push_back("");
            else toBeInserted.push_back(element);
        }
        productionsVec.push_back(toBeInserted);
    }
    return productionsVec;
}

bool SyntaxParser::isTerminalString(string str){
    return str[0] == '\'' && str[str.size()-1] == '\'';
}

set<string> SyntaxParser::getNonTerminals(){
    return this->nonTerminals;
}

map<string,vector<vector<string>>> SyntaxParser::getProductions(){
    return this->productions;
} 


bool SyntaxParser::isEpsillon(string str){
    return str.compare("\\L")==0;
}

