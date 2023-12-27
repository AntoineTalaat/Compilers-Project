//
// Created by veror on 12/22/2023.
//

#include <iostream>
#include <set>
#include <fstream>
#include "parse_tree_builder.h"
#include "globals.h"
                                                                                      // terminal , nonTerminal
ParseTreeBuilder::ParseTreeBuilder(std::map<std::string, std::set<std::pair<std::string, std::vector<std::string>>>>
                                                            // nonTerminal (E) , terminals (id , (  , $)
                                    firstSet   , std::map<std::string, std::set<std::string>> followSet ,
                                    std::set<std::string> terminals) {
    this->firstSet = firstSet;
    this->followSet = followSet;
    this->terminals = terminals;
    this->terminals.insert("$");
}


std::map<std::string, std::map<std::string, std::vector<std::string>>> ParseTreeBuilder::buildParseTree() {
    // E --- ( id , [E + T] )
    std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree;

    for (auto const &row : this->firstSet) {

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
                // Check if the key already exists
                if (parseTree[nonTerminal].count(terminal) == 0) {
                    // Key does not exist, safe to add production
                    parseTree[nonTerminal][terminal] = production;
                } else {
                    // Key already exists, throw an exception
                    throw std::runtime_error("Duplicate entry for nonTerminal: " + nonTerminal +", terminal: " + terminal);
                }
            }
        }

        std::set<std::string> follow= followSet[nonTerminal]; // follow of E >> id , ( , $
        if(hasEpsillon){
            for (auto const &followTerminal : follow ) {
                  parseTree[nonTerminal][followTerminal] = std::vector<std::string>();
            }
        }else{
            for (auto const &followTerminal : follow ) {
                if (parseTree.find(nonTerminal) == parseTree.end() ||
                    parseTree[nonTerminal].find(followTerminal) == parseTree[nonTerminal].end()) {
                    parseTree[nonTerminal][followTerminal] = std::vector<std::string>({"sync"});
                }
            }
        }
    }

    std::map<std::string, std::map<std::string, std::vector<std::string>>> modified = modifyParseTable(parseTree);
    convertToCSV(modified, Globals::PARSE_TABLE_CSV_FILE);

    return parseTree;
}



void ParseTreeBuilder::printTerminals(std::set<std::string> terminals){
    std::cout << "terminals = ";
    for (auto const &terminal : terminals) {
        std::cout << terminal << " ";
    }
    std::cout << std::endl;
}

std::map<std::string, std::map<std::string, std::vector<std::string>>> ParseTreeBuilder::modifyParseTable
        ( std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree){

    std::map<std::string, std::map<std::string, std::vector<std::string>>> modifiedParseTree;

    for (auto const &row : this->firstSet) {

        std::string nonTerminal = row.first;     // E

        for(auto const &terminal : this->terminals){
            if(parseTree[nonTerminal].count(terminal) == 0){
                modifiedParseTree[nonTerminal][terminal] = std::vector<std::string>({"Error"});
            }else{
                modifiedParseTree[nonTerminal][terminal] = parseTree[nonTerminal][terminal];
            }
        }
    }

    return modifiedParseTree;
}


// define function to print parse tree in detail
void ParseTreeBuilder::printParseTree(std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree) {
    std::cout << "-------------------------------- Terminals ------------------------------------------" << std::endl;
    printTerminals(this->terminals);
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

// Utility function to join vector elements with a delimiter
std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
    std::string result;
    for (const auto& element : vec) {
        result += element + delimiter;
    }
    // Remove the trailing delimiter
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}


void ParseTreeBuilder::convertToCSV(const std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree, std::string csvFileName) {
    // Open the CSV file for writing
    std::ofstream csvFile(csvFileName);

    // Check if the file is open
    if (!csvFile.is_open()) {
        std::cerr << "Error: Unable to open the CSV file." << std::endl;
        return;
    }

    // Write the header row with terminal names
    csvFile << ",";
    for (const auto& terminalEntry : parseTree.begin()->second) {
        csvFile << terminalEntry.first << ",";
    }
    csvFile << std::endl;

    // Write rows with non-terminal names and corresponding vector elements
    for (const auto& nonTerminalEntry : parseTree) {
        csvFile << nonTerminalEntry.first << ",";
        for (const auto& terminalEntry : nonTerminalEntry.second) {
            // Join vector elements with spaces and write to CSV
            csvFile << join(terminalEntry.second, " ") << ",";
        }
        csvFile << std::endl;
    }

    // Close the file
    csvFile.close();
    std::cout << "Parse table written to CSV file successfully." << std::endl;
}



