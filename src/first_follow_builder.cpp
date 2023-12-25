#include "first_follow_builder.h"
#include <algorithm>
#include <iostream>

FirstFollowBuilder::FirstFollowBuilder(std::map<std::string, std::vector<std::vector<std::string>>> productions, std::set<std::string> nonTerminals) {
    this->productions = productions;
    this->nonTerminals = nonTerminals;

    for(const auto nonTerminal : nonTerminals) {
        this->firstMap[nonTerminal] = {};
        this->followMap[nonTerminal] = {};
    }
};

std::map<std::string, std::set<std::pair<std::string, std::vector<std::string>>>> FirstFollowBuilder::getFirst() {
    // compute first of each non terminal
    for(const auto nonTerminal : this->nonTerminals) {
        computeFirst(nonTerminal);
    }

    return this->firstMap;
}

void FirstFollowBuilder::computeFirst(const std::string nonTerminal) {
    // iterate through each production of the correspoding current non-terminal productions
    for(const auto production : productions[nonTerminal]) {
        std::cout << "Vector of strings:" << "  ";
        for (const auto str : production) {
            std::cout << str << " ";
        }
        std::cout << std::endl;
        // iterate through each symbol in the production
        for (const auto symbol : production) {
            // epsillon or terminal
            if(isEpsillon(symbol)) {
                this->firstMap[nonTerminal].insert({symbol, std::vector<std::string>()});
                break;
            }
            else if (isTerminalString(symbol)) {
                this->firstMap[nonTerminal].insert({symbol, production});
                break;
            }
            // non-terminal
            else if (nonTerminals.count(symbol)) {
                // skip epsilon in the first set of the non-terminal
                if (!isEpsillon(symbol)) {
                    computeFirst(symbol);
                    const auto symbolFirstSet = this->firstMap[symbol];
                    for (const auto pair : symbolFirstSet) 
                        this->firstMap[nonTerminal].insert({pair.first, production});
                }
                // if epsilon is in the first set, continue to the next symbol
                if (!isEpsillon(symbol)) {
                    break;
                }
            }
        }
    }
}

std::map<std::string, std::set<std::string>> FirstFollowBuilder::getFollow() {
    // iterate through each non-terminal and compute its Follow set
    auto it = this->nonTerminals.begin();

    // check if the set is not empty before accessing the first element
    if (it != this->nonTerminals.end()) 
        this->followMap[*it].insert("$");
    for (const auto nonTerminal : this->nonTerminals) {
        computeFollow(nonTerminal);
    }

    return this->followMap;
}

void FirstFollowBuilder::computeFollow(std::string nonTerminal) {
    // iterate through each production
    for (auto rule : productions) {
        for(std::vector<std::string> production : rule.second) {
            for(int i=0; i<production.size(); i++) {
                if(production[i] == nonTerminal) {
                   // law ana fe a5er el production
                    if(i == production.size() - 1) {
                        auto lhsOfRule = rule.first;
                        if(lhsOfRule == nonTerminal)    continue;
                        computeFollow(lhsOfRule);
                        for(auto follow : this->followMap[lhsOfRule]) {
                            this->followMap[nonTerminal].insert(follow);
                        }
                    }
                    else if(isTerminalString(production[i+1])) {
                        this->followMap[nonTerminal].insert(production[i+1]);
                    }
                    else {
                        auto lhsOfRule = rule.first;
                        for(int j = i + 1; j<production.size(); j++) {
                            std::string nextSymbol = production[j];
                            if(isTerminalString(nextSymbol)) {
                                this->followMap[nonTerminal].insert(nextSymbol);
                                break;
                            }
                            bool nextHasEpsillonFirst = false;
                            auto nextFirstSet = this->firstMap[nextSymbol];
                            for(auto firstSymbol : nextFirstSet) {
                                if(!isEpsillon(firstSymbol.first)) {
                                    this->followMap[nonTerminal].insert(firstSymbol.first);
                                }
                                if(isEpsillon(firstSymbol.first)) {
                                    nextHasEpsillonFirst = true;
                                }
                            }
                            if(!nextHasEpsillonFirst) break;
                            if(j == production.size() - 1) {
                                if(lhsOfRule == nonTerminal) break;
                                computeFollow(lhsOfRule);
                                for(auto follow : this->followMap[lhsOfRule]) {
                                    this->followMap[nonTerminal].insert(follow);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}

bool FirstFollowBuilder::isTerminalString(std::string str) {
    if (this->nonTerminals.count(str) == 0) 
        return true;
    else
        return false;
}

bool FirstFollowBuilder::isEpsillon(std::string str){
    return str.compare("")==0;
}

void FirstFollowBuilder::printFirstMap() {
    std::cout << "Printing First Map:\n";
    for (const auto& entry : this->firstMap) {
        const std::string& nonTerminal = entry.first;
        const auto& productionList = entry.second;

        std::cout << nonTerminal << " -> ";
        for (const auto& production : productionList) {
            const std::string& currentNonTerminal = production.first;
            const auto& symbols = production.second;
            std::cout << "(" << currentNonTerminal << ", [";
            for (const auto& symbol : symbols) {
                std::cout << symbol;
            }
            std::cout << "]), ";
        }
        std::cout << "\n";
    }
}

void FirstFollowBuilder::printFollowMap() {
    std::cout << "\nPrinting Follow Map:\n";
    for (const auto entry : this->followMap) {
        const std::string nonTerminal = entry.first;
        const auto followSet = entry.second;

        std::cout << nonTerminal << " -> {";
        for (const auto symbol : followSet) {
            if(isEpsillon(symbol)) std::cout << "@";
            std::cout << symbol;// << ", ";
        }
        std::cout << "}\n";
    }
}