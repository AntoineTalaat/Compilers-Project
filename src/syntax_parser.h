
#ifndef SYNTAX_PARSER_H
#define SYNTAX_PARSER_H

#include <bits/stdc++.h>
#include "token.h"
#include "utils.h"
using namespace std;
class SyntaxParser
{
private:
    set<string> nonTerminals;
    set<string> terminals;
    map<string,vector<vector<string>>> productions;
    bool isTerminalString(string str);
    bool isEpsillon(string str);
public:
    SyntaxParser(string rulesStr);
    void parseSyntacticRule(string rule);
    vector<vector<string>> parseSyntaxRuleRHS(string rhs);
    set<string> getNonTerminals();
    map<string,vector<vector<string>>> getProductions;    
};

#endif // SYNTAX_PARSER_H