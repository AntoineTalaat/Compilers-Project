
#ifndef LL1_PROCESSOR_H
#define LL1_PROCESSOR_H

#include <bits/stdc++.h>
#include "utils.h"
using namespace std;
class LL1_Processor
{
private:
    set<string> nonTerminalsUsed;
    string generateNewNonTerminalFrom(string oldNonTerminal);
    bool isImmediateLRCause(string lhs,vector<string> rhsProduction);
    bool containsLF(vector<vector<string>> rhsProduction);
    map<string,vector<vector<string>>>  eliminateImmediateLR(string lhs, vector<vector<string>> rhsProductions);
    map<string,vector<vector<string>>>  executeLeftFactoring(string lhs, vector<vector<string>> rhsProductions);
    vector<vector<string>> replaceNtInRule(string Ai,vector<vector<string>> AiRHS,string Aj,vector<vector<string>> AjRHS);
public:
    map<string,vector<vector<string>>> getLL1productions(map<string,vector<vector<string>>> old);
};

#endif // LL1_PROCESSOR_H