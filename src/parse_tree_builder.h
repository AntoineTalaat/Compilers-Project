//
// Created by veror on 12/22/2023.
//

#include <map>
#include <string>
#include <vector>

#ifndef LEXICAL_ANALYZER_GENERATOR_PARSE_TREE_BUILDER_H
#define LEXICAL_ANALYZER_GENERATOR_PARSE_TREE_BUILDER_H

#endif //LEXICAL_ANALYZER_GENERATOR_PARSE_TREE_BUILDER_H

class ParseTreeBuilder {
    private:
        std::map<std::string, std::vector <std::pair<std::string, std::vector<std::string>>>> firstSet;
        std::map<std::string,  std::vector<std::string>> followSet;

    public:
        ParseTreeBuilder(std::map<std::string, std::vector<std::pair<std::string, std::vector<std::string>>>> firstSet,
                         std::map<std::string,  std::vector<std::string>> followSet);

        std::map<std::string, std::map<std::string, std::vector<std::string>>> buildParseTree();
        void printParseTree(std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree);

};