#include "first_follow_builder.h"
#include <algorithm>
#include <iostream>
#include "globals.h"

FirstFollowBuilder::FirstFollowBuilder(std::map<std::string, std::vector<std::vector<std::string>>> productions, std::set<std::string> nonTerminals) {
    this->productions = productions;
    this->nonTerminals = nonTerminals;

    for(const auto nonTerminal : nonTerminals) {
        this->firstMap[nonTerminal] = {};
        this->followMap[nonTerminal] = {};
        this->isFirstSet[nonTerminal] = false;
        this->isFollowSet[nonTerminal] = false;
    }
};

std::map<std::string, std::set<std::pair<std::string, std::vector<std::string>>>> FirstFollowBuilder::getFirst() {
    // compute first of each non terminal
    for(auto nonTerminal : this->nonTerminals) {
        if(!this->isFirstSet[nonTerminal]) computeFirst(nonTerminal);
    }

    return this->firstMap;
}

void FirstFollowBuilder::computeFirst(const std::string nonTerminal) {
    this->isFirstSet[nonTerminal] = true;
    // iterate through each production of the correspoding current non-terminal productions
    for(auto production : productions[nonTerminal]) {
        // iterate through each symbol in the production
        for (const auto symbol : production) {
            // epsillon or terminal
            if(isEpsillon(symbol)) {
                this->firstMap[nonTerminal].insert({symbol, std::vector<std::string>()});
                break;
            }
    
            else if(isTerminalString(symbol)) {
                this->firstMap[nonTerminal].insert({symbol, production});
                break;
            }
            // non-terminal
            if(nonTerminals.count(symbol)) {
                // 1. lw ana(symbol) kol ely ablya 3ndhom epsillon fel first yb2a hzwd my first 3la nonterminal first
                // 2. lw epsillon mwgoda fe kolo yb2a hzwd epsillon 3la nonterminal first
                if(!this->isFirstSet[symbol]) computeFirst(symbol);
                bool symbolHasEpsillonFirst = false;
                const auto symbolFirstSet = this->firstMap[symbol];
                for(const auto pair : symbolFirstSet) {
                    if(isEpsillon(pair.first))  symbolHasEpsillonFirst = true;
                    else this->firstMap[nonTerminal].insert({pair.first, production});
                }
                if(!symbolHasEpsillonFirst) break;
                if(symbol == production.back()) {
                    this->firstMap[nonTerminal].insert({"", std::vector<std::string>()});
                }
            }
        }
    } 
}

std::map<std::string, std::set<std::string>> FirstFollowBuilder::getFollow() {
    this->followMap[Globals::START_SYMBOL].insert("$");
    
    for(auto production : this->productions)
        if(!this->isFollowSet[production.first]) computeFollow(production.first);

    return this->followMap;
}

void FirstFollowBuilder::computeFollow(std::string nonTerminal) {
    // iterate through each production
    for(auto rule : productions) {
        for(std::vector<std::string> production : rule.second) {
            for(int i=0; i<production.size(); i++) {
                if(production[i] == nonTerminal) {
                   // law ana fe a5er el production
                    if(i == production.size() - 1) {
                        handleFollowLast(rule.first, nonTerminal);
                    }
                    else if(isTerminalString(production[i+1])) {
                        this->followMap[nonTerminal].insert(production[i+1]);
                    }
                    else {
                        handleFollow(rule.first, nonTerminal, production, i + 1);
                    }
                }
            }
        }
    }
    this->isFollowSet[nonTerminal] = true;
}
void FirstFollowBuilder::handleFollowLast(std::string lhsNonterminal, std::string rhsNonterminal) {

    if(lhsNonterminal == rhsNonterminal)    return;
    // check lw el lhsOfRule mwgod 3ndy a5er wa7ed
    if(!this->isFollowSet[lhsNonterminal]) computeFollow(lhsNonterminal);
    for(auto follow : this->followMap[lhsNonterminal]) {
        this->followMap[rhsNonterminal].insert(follow);
    }                    
}

void FirstFollowBuilder::handleFollow(std::string lhsNonterminal, std::string rhsNonterminal, std::vector<std::string> productions, int index) {
    for(int j = index; j < productions.size(); j++) {
        std::string nextSymbol = productions[j];
        if(isTerminalString(nextSymbol)) {
            this->followMap[rhsNonterminal].insert(nextSymbol);
            break;
        }
        bool nextHasEpsillonFirst = false;
        auto nextFirstSet = this->firstMap[nextSymbol];
        for(auto firstSymbol : nextFirstSet) {
            if(!isEpsillon(firstSymbol.first)) {
                this->followMap[rhsNonterminal].insert(firstSymbol.first);
            }
            if(isEpsillon(firstSymbol.first)) {
                nextHasEpsillonFirst = true;
            }
        }
        if(!nextHasEpsillonFirst) break;
        if(j == productions.size() - 1) {
            if(lhsNonterminal == rhsNonterminal) break;
            if(!this->isFollowSet[lhsNonterminal]) computeFollow(lhsNonterminal);
            for(auto follow : this->followMap[lhsNonterminal]) {
                this->followMap[rhsNonterminal].insert(follow);
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