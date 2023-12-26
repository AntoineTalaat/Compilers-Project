#ifndef FIRST_FOLLOW_BUILDER_H
#define FIRST_FOLLOW_BUILDER_H

#include <map>
#include <string>
#include <vector>
#include <set>

class FirstFollowBuilder
{
private:
    std::map<std::string, std::set<std::pair<std::string, std::vector<std::string>>>> firstMap;   
    std::map<std::string, std::set<std::string>> followMap;
    std::set<std::string> nonTerminals;
    std::set<std::string> terminals;
    std::map<std::string, std::vector<std::vector<std::string>>> productions;
    std::map<std::string, bool> isFirstSet;
    std::map<std::string, bool> isFollowSet;
    void computeFirst(const std::string);
    void computeFollow(const std::string);
    bool isTerminalString(std::string str);
    bool isEpsillon(std::string str);
    void handleFollowLast(std::string lhsNonterminal, std::string rhsNonterminal);
    void handleFollow(std::string lhsNonterminal, std::string rhsNonterminal, std::vector<std::string> productions, int index);
    
public:
    FirstFollowBuilder(std::map<std::string, std::vector<std::vector<std::string>>> productions, std::set<std::string> nonTerminals);
    std::map<std::string, std::set<std::pair<std::string, std::vector<std::string>>>> getFirst();   
    std::map<std::string, std::set<std::string>> getFollow();
    void printFirstMap();
    void printFollowMap();  
};

#endif  // FIRST_FOLLOW_BUILDER_H