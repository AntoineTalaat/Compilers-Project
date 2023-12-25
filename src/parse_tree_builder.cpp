//
// Created by veror on 12/22/2023.
//

#include <iostream>
#include <set>
#include "parse_tree_builder.h"
                                                                                      // terminal , nonTerminal
ParseTreeBuilder::ParseTreeBuilder(std::map<std::string, std::set<std::pair<std::string, std::vector<std::string>>>>
                                                            // nonTerminal (E) , terminals (id , (  , $)
                                    firstSet   , std::map<std::string, std::set<std::string>> followSet) {
    this->firstSet = firstSet;
    this->followSet = followSet;
}


std::map<std::string, std::map<std::string, std::vector<std::string>>> ParseTreeBuilder::buildParseTree() {
    // E --- ( id , [E + T] )
    std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree;

    for (auto const &row : firstSet) {

        std::string nonTerminal = row.first;     // E
        std::set <std::pair < std::string, std::vector < std::string>>>  transitions = row.second;

        std::cout << "nonTerminal = " << nonTerminal << std::endl;
        bool hasEpsillon = false;

        for (auto const &transition : transitions) {
            std::string terminal = transition.first;            // id -- ""
            std::vector<std::string> production = transition.second;    // [E + T]  -- []

            if(terminal.length()==0){
                hasEpsillon = true;
            }else{
                parseTree[nonTerminal][terminal] = production;
            }
        }

        std::set<std::string> follow= followSet[nonTerminal]; // follow of E >> id , ( , $
        if(hasEpsillon){
            for (auto const &followTerminal : follow ) {
                  parseTree[nonTerminal][followTerminal] = std::vector<std::string>();
            }
        }else{
            for (auto const &followTerminal : follow ) {
                parseTree[nonTerminal][followTerminal] = std::vector<std::string>({"sync" });
            }
        }
    }


    return parseTree;
}


// define function to print parse tree in detail
void ParseTreeBuilder::printParseTree(std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree) {
    std::cout << "--------------------------------Parse Tree ------------------------------------------" << std::endl;
    for (auto const &row : parseTree) {

        std::map<std::string, std::vector<std::string>> transitions = row.second;
        for (auto const &transition : transitions) {
            std::cout << row.first << " ";
            std::cout <<  transition.first << " ";
            std::vector<std::string> production = transition.second;

            for (auto const &productionItem : production) {
                std::cout << productionItem << " ";
            }
            std::cout << std::endl;
        }
    }
}

//                // Get from follow set
//                std::cout << "terminal is empty" << std::endl;
//
//                std::set<std::string> follow= followSet[nonTerminal]; // follow of E >> id , ( , $
//                for (auto const &followTerminal : follow ) {
//                    parseTree[nonTerminal][followTerminal] = production;
//                    std::cout << "nonTerminal = " << nonTerminal << std::endl;
//                    std::cout << "followTerminal = " << followTerminal << std::endl;
//                    std::cout << "production = ";
//                    for (auto const &productionItem : production) {
//                        std::cout << productionItem << " ";
//                    }
//                    std::cout << std::endl;
//                    std::cout <<"---------------------------------------------"<<std::endl;
//
//                }
//
//                printParseTree(parseTree);


//std::set<std::string> follow= followSet[nonTerminal]; // follow of E >> id , ( , $
//for (auto const &followTerminal : follow ) {
//
//parseTree[nonTerminal][followTerminal] =  std::vector<std::string>({"sync" });
//
//}
//std::cout << "terminal is not empty" << std::endl;
//std::cout << "nonTerminal = " << nonTerminal << std::endl;
//std::cout << "terminal = " << terminal << std::endl;
//std::cout << "production = ";
//for (auto const &productionItem : production) {
//std::cout << productionItem << " ";
//}
//std::cout << std::endl;
//
//std::cout <<"---------------------------------------------"<<std::endl;