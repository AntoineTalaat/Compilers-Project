//
// Created by veror on 12/22/2023.
//

#include <iostream>
#include "parse_tree_builder.h"
                                                                                      // terminal , nonTerminal
ParseTreeBuilder::ParseTreeBuilder(std::map < std::string, std::vector <std::pair < std::string, std::vector < std::string>>>>
                                                            // nonTerminal (E) , terminals (id , (  , $)
                                    firstSet   , std::map<std::string, std::vector<std::string>> followSet) {
    this->firstSet = firstSet;
    this->followSet = followSet;
}


std::map<std::string, std::map<std::string, std::vector<std::string>>> ParseTreeBuilder::buildParseTree() {
    // E --- ( id , [E + T] )
    // E --- ( ) , [E + T] )
    std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree;

    for (auto const &row : firstSet) {
        // E
        std::string nonTerminal = row.first;
        std::cout << "nonTerminal = " << nonTerminal << std::endl;
        // E --- ( id , [E + T] )
        // E --- ( ) , [E + T] )
        // E --- ( '' , [] )
        std::vector <std::pair < std::string, std::vector < std::string>>>  transitions = row.second;

        for (auto const &transition : transitions) {
            // id
            std::string terminal = transition.first;
//            std::cout << "terminal = " << terminal << std::endl;
            // [E + T]
            std::vector<std::string> production = transition.second;
//            std::cout << "production = ";
//            for (auto const &productionItem : production) {
//                std::cout << productionItem << " ";
//            }
//            std::cout << std::endl;

            if(terminal.length()==0){
                // Get from follow set
//                std::cout << "terminal is empty" << std::endl;

                std::vector<std::string> follow= followSet[nonTerminal]; // follow of E >> id , ( , $
                for (auto const &followTerminal : follow ) {
                    parseTree[nonTerminal][followTerminal] = production;
//                    std::cout << "nonTerminal = " << nonTerminal << std::endl;
//                    std::cout << "followTerminal = " << followTerminal << std::endl;
//                    std::cout << "production = ";
//                    for (auto const &productionItem : production) {
//                        std::cout << productionItem << " ";
//                    }

                }

            }else{
                parseTree[nonTerminal][terminal] = production;
                std::vector<std::string> follow= followSet[nonTerminal]; // follow of E >> id , ( , $
                for (auto const &followTerminal : follow ) {
                    parseTree[nonTerminal][followTerminal] =  std::vector<std::string>({"sync" });

                }
//                std::cout << "terminal is not empty" << std::endl;
//                std::cout << "nonTerminal = " << nonTerminal << std::endl;
//                std::cout << "terminal = " << terminal << std::endl;
//                std::cout << "production = ";
//                for (auto const &productionItem : production) {
//                    std::cout << productionItem << " ";
//                }
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

