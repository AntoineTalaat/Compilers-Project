#include "ll1_processor.h"

map<string,vector<vector<string>>> LL1_Processor::getLL1productions(map<string,vector<vector<string>>> old){
    std::vector<string> orderedNonTerminals;
    for (const auto& pair : old) {
        orderedNonTerminals.push_back(pair.first);
        this->nonTerminalsUsed.insert(pair.first);
    }
    
    for(int i=0;i<orderedNonTerminals.size();i++){
        string Ai = orderedNonTerminals[i];
        for(int j=0;j<i;j++){
            string Aj = orderedNonTerminals[j];
            bool causeLR = false;
            for(int ruleInd = 0; ruleInd<old[Aj].size();ruleInd++){
                for(int ruleIndI = 0; ruleIndI<old[Ai].size();ruleIndI++){
                    causeLR = causeLR || isImmediateLRCause(Ai,old[Aj][ruleInd]) && Aj.compare(old[Ai][ruleIndI][0])==0;
                }
            }
            if(causeLR){
                vector<vector<string>> newAiRule = replaceNtInRule(Ai,old[Ai],Aj,old[Aj]);
                old[Ai] = newAiRule;
            }
        }
  

        map<string,vector<vector<string>>> newProductions=eliminateImmediateLR(Ai,old[Ai]);
        for (const auto& pair : newProductions) {
            old[pair.first] = pair.second;
        }
    }    
    for(int i=0;i<orderedNonTerminals.size();i++){
        string Ai = orderedNonTerminals[i];
        while(containsLF(old[Ai])){
            map<string,vector<vector<string>>> newProductions=executeLeftFactoring(Ai,old[Ai]);
            for (const auto& pair : newProductions) {
                old[pair.first] = pair.second;
            }
        }
    }
    return old;

}


set<string> LL1_Processor::getNonTerminals(){
    return this->nonTerminalsUsed;
}


vector<vector<string>> LL1_Processor::replaceNtInRule(
    string Ai,vector<vector<string>> AiRHS,string Aj,vector<vector<string>> AjRHS){
        int numReplacements = AjRHS.size();
        vector<vector<string>> output;
        for(int productionInd = 0; productionInd<AiRHS.size(); productionInd++){
                // search for the Aj location
                auto it = find(AiRHS[productionInd].begin(), AiRHS[productionInd].end(), Aj);
                if (it != AiRHS[productionInd].end()) {
                    // contains Aj
                    for(int replacementInd=0;replacementInd<numReplacements;replacementInd++){
                        vector<string> changed;
                        std::size_t position = distance(AiRHS[productionInd].begin(), it); 
                        for(int symbolAiInd = 0;symbolAiInd<AiRHS[productionInd].size();symbolAiInd++){
                            if(symbolAiInd!=position){
                                changed.push_back(AiRHS[productionInd][symbolAiInd]);
                            } else {
                                for(int symbolAjInd = 0; symbolAjInd<AjRHS[replacementInd].size();symbolAjInd++){
                                    // don't do that if AjRHS[replacementInd][symbolAjInd] and not alone
                                    // not alone is !changed.empty() || symbolAiInd <AiRHS[productionInd].size()-1
                                    bool alone = changed.empty() && symbolAiInd==AiRHS[productionInd].size()-1;
                                    if(AjRHS[replacementInd][symbolAjInd].compare("")==0 && alone // epsilon alone
                                    || AjRHS[replacementInd][symbolAjInd].compare("")!=0) // not epsillon
                                    changed.push_back(AjRHS[replacementInd][symbolAjInd]);
                                }
                            }
                        }
                        output.push_back(changed);
                    }

                }else{
                    vector<string> unchanged = AiRHS[productionInd];
                    output.push_back(unchanged);
                }

        }
    return output;
}

bool LL1_Processor::isImmediateLRCause(string lhs, vector<string> rhsProduction){
    return lhs == rhsProduction[0];
}
bool LL1_Processor::containsLF(vector<vector<string>> rhsProductions){
    map<string,int> symbolOccurances;
    for(int ruleInd=0;ruleInd<rhsProductions.size();ruleInd++){
        symbolOccurances[rhsProductions[ruleInd][0]]++;
        if(symbolOccurances[rhsProductions[ruleInd][0]]>1) return true;
    }
    return false;
}



map<string,vector<vector<string>>> LL1_Processor::executeLeftFactoring(
    std::string lhs, vector<vector<string>> rhsProductions) {
    
    map<string, vector<vector<string>>> temp;
    temp[lhs] = rhsProductions;

    map<string,int> symbolOccurances;
    for(int ruleInd=0;ruleInd<rhsProductions.size();ruleInd++){
        symbolOccurances[rhsProductions[ruleInd][0]]++;
    }
    set<string> commonSymbols;
    for (const auto& pair : symbolOccurances) {
        if(pair.second>1)
            commonSymbols.insert(pair.first);
    }

    map<string, vector<vector<string>>> outputMiniMap;
    vector<vector<string>> oldRuleRhs;
    for(const auto& symbol : commonSymbols){
        string newLHS = generateNewNonTerminalFrom(lhs);
        nonTerminalsUsed.insert(newLHS);
        vector<vector<string>> newRuleRHS;
        bool replaced = false;
        for(int ruleInd=0;ruleInd<rhsProductions.size();ruleInd++){
            if(rhsProductions[ruleInd][0].compare(symbol)==0){
                vector<string> rest;
                for(int symbolInd = 1; symbolInd<rhsProductions[ruleInd].size();symbolInd++){
                    rest.push_back(rhsProductions[ruleInd][symbolInd]);
                }
                newRuleRHS.push_back(rest);
                vector<string> modifiedOldProduction;
                if(!replaced){
                    modifiedOldProduction.push_back(symbol);
                    modifiedOldProduction.push_back(newLHS);
                    oldRuleRhs.push_back(modifiedOldProduction);
                    replaced = true;
                }            
            }else{
                oldRuleRhs.push_back(rhsProductions[ruleInd]);
            }
        } 
        outputMiniMap[newLHS] = newRuleRHS;
    }
    outputMiniMap[lhs] = oldRuleRhs;
    return outputMiniMap;
}

string LL1_Processor::generateNewNonTerminalFrom(string oldNonTerminal){
    string current = oldNonTerminal+'`';
    while(nonTerminalsUsed.count(current)>0){
        current = current+'`';
    }
    return current;
}


map<string,vector<vector<string>>> LL1_Processor::eliminateImmediateLR(
    string lhs, vector<vector<string>> rhsProductions){
        // Assume lhs non terminal only repeated once 
        int ruleLRCauseInd=-1;
        for(int ruleInd=0;ruleInd<rhsProductions.size();ruleInd++){
            if(this->isImmediateLRCause(lhs,rhsProductions[ruleInd])){
                ruleLRCauseInd=ruleInd;
                break;
            }
        }
        map<string,vector<vector<string>>> outputProductions;
        if(ruleLRCauseInd==-1){ // There is no immediate LR
            outputProductions[lhs] = rhsProductions;
            // cout<<"Found no LR in rule starting with lhs: " << lhs <<endl;
            return outputProductions;
        }
        // now we know which caused the LR
        vector<string> restOfLRProduction;
        for(int symbolInd = 1 /* skip first LR cause*/; symbolInd<rhsProductions[ruleLRCauseInd].size();symbolInd++){
            restOfLRProduction.push_back(rhsProductions[ruleLRCauseInd][symbolInd]);
        }
        string newlhs = generateNewNonTerminalFrom(lhs);
        nonTerminalsUsed.insert(newlhs);
        // main production
        vector<vector<string>> newPrimaryRHS;
        for(int ruleInd=0;ruleInd<rhsProductions.size();ruleInd++){
            if(ruleInd!=ruleLRCauseInd){
                vector<string> newProduction;
                for(int symbolInd = 0; symbolInd<rhsProductions[ruleInd].size();symbolInd++){
                    newProduction.push_back(rhsProductions[ruleInd][symbolInd]);
                }
                newProduction.push_back(newlhs);
                newPrimaryRHS.push_back(newProduction);
            }
        }
        outputProductions[lhs]=newPrimaryRHS;

        //new production
        vector<vector<string>> newSecondaryRHS;
        vector<string> epsillonProduction;
        epsillonProduction.push_back(""); //CAREFUL IF EPSILLON REPRESENTATION CHANGED
        vector<string> terminalProduction;
        for(int symbolInd = 0; symbolInd<restOfLRProduction.size();symbolInd++){
            terminalProduction.push_back(restOfLRProduction[symbolInd]);
        }
        terminalProduction.push_back(newlhs);
        newSecondaryRHS.push_back(terminalProduction);
        newSecondaryRHS.push_back(epsillonProduction);
        outputProductions[newlhs]=newSecondaryRHS;

        return outputProductions;
}
