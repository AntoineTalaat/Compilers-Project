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

// if A -> xBy is a production rule >> everything in FIRST(y) is FOLLOW(B) except E
// If ( A -> xB is a production rule ) or ( A -> xBy is a production rule and E is in FIRST(y)) >> everything in FOLLOW(A) is in FOLLOW(B).


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

void FirstFollowBuilder::computeFollow(const std::string nonTerminal) {
    // iterate through each production
    std::cout << "henaaaaa" << std::endl;
    for (const auto rule : productions) {
        std::cout << "henaaaaa2222" << std::endl;
        for(std::vector<std::string> production : rule.second) {
            std::cout << "henaaaaa33333" << std::endl;
            for(int i=0; i<production.size(); i++) {
                std::cout << "henaaaaa4444" << std::endl;
                if(production[i] == nonTerminal) {
                    std::cout << "henaaaaa5555" << std::endl;
                    if(i == production.size() - 1) {
                        auto lhsOfRule = rule.first;
                      //  if(lhsOfRule == nonTerminal)    continue;
                        computeFollow(lhsOfRule);
                        std::cout << "henaaaaa12222222" << std::endl;
                        for(auto follow : this->followMap[lhsOfRule]) {
                            std::cout << "henaaaaa66666" << std::endl;
                            this->followMap[nonTerminal].insert(follow);
                        }
                    }
                    else if(isTerminalString(production[i+1])) {
                        this->followMap[nonTerminal].insert(production[i+1]);
                    }
                    else {
                        std::cout << "henaaaaa7777777" << std::endl;
                        auto lhsOfRule = rule.first;
                        for(int j = i + 1; j<production.size(); j++) {
                            std::cout << "henaaaaa88888" << std::endl;
                            std::string nextSymbol = production[j];
                            if(isTerminalString(nextSymbol)) {
                                this->followMap[nonTerminal].insert(nextSymbol);
                                break;
                            }
                            bool nextHasEpsillonFirst = false;
                            auto nextFirstSet = this->firstMap[nextSymbol];
                            std::cout << "henaaaaa10000000" << std::endl;
                            for(auto firstSymbol : nextFirstSet) {
                                std::cout << "henaaaaa99999" << std::endl;
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
                                    std::cout << "henaaaaa1111111" << std::endl;
                                    this->followMap[nonTerminal].insert(follow);
                                }
                            }
                        }
                    }
                }
            }
        }
        /*
        const auto& leftHandSide = entry.first;
        const auto& productionList = entry.second;

        // Iterate through each production of the current non-terminal
        for (const auto& production : productionList) {
            auto pos = std::find(production.begin(), production.end(), nonTerminal);
            if (pos != production.end()) {
                // If non-terminal is found in the production
                auto nextPos = pos + 1;
                while (nextPos != production.end()) {
                    // Iterate through the symbols after the non-terminal in the production
                    const auto& nextSymbol = *nextPos;

                    // If the next symbol is a terminal, add it to the Follow set and break
                    if (isTerminalString(nextSymbol)) {
                        this->followMap[nonTerminal].insert(nextSymbol);
                        break;
                    }

                    // If the next symbol is a non-terminal, add its First set to the Follow set
                    const auto& symbolFirstSet = getFirst()[nextSymbol];
                    for (const auto& pair : symbolFirstSet) {
                        this->followMap[nonTerminal].insert(pair.second.begin(), pair.second.end());
                    }

                    // If epsilon is in the First set, continue to the next symbol
                    auto it = *symbolFirstSet.begin();
                    if (symbolFirstSet.empty() || it.second.empty()) {
                        break;
                    }

                    // Move to the next symbol in the production
                    ++nextPos;
                }

                // if end of the production, add the follow set of the left-hand side non-terminal to the follow set of the current non-terminal
                if (nextPos == production.end()) {
                    computeFollow(leftHandSide);
                    const auto& leftHandSideFollowSet = this->followMap[leftHandSide];
                    this->followMap.insert(leftHandSideFollowSet.begin(), leftHandSideFollowSet.end());
                }
            }
        }
        */
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
            std::cout << symbol << ", ";
        }
        std::cout << "}\n";
    }
}