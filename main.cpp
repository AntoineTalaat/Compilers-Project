#include <iostream>
#include "src/nfa.h"
#include "src/subset_construction.h"
#include "input_parser.h"
#include "lexical_analyzer.h"
#include "syntax_parser.h"
#include "parse_tree_builder.h"
#include "first_follow_builder.h"
#include "ll1_processor.h"
#include "LL1Parser.h"

using namespace std;

struct DFA {
    int startStateID;
    int deadStateID;
    map<int,State> minimalDFA;

    DFA(int startID, int deadID, const map<int,State>& minimal)
        : startStateID(startID), deadStateID(deadID), minimalDFA(minimal) {}
};

struct DFA initialize_lexical_parser(){
    string file = Globals::LEXICAL_RULES_FILE;
    string content = Utils::readFile(file);
    InputParser ip;
    char delimiter = '\n';
    Globals::alphabet.insert(EPSILLON);
    std::vector<std::string> lines = Utils::splitString(content, delimiter);

    for (int i=0;i<lines.size();i++){
        ip.tokenize(lines[i],i);
    }
    std::vector<NFA> allNFAs = ip.allNFAs;
    NFA n = NFAGenerator::getFullNFA(ip.allNFAs) ;
    std::cout <<"NFA states size = " << n.getStatesMap().size() << std::endl;
    SubsetConstruction s(n);
    s.setAlphabet(Globals::alphabet);
    std::map< int , State> DFA = s.getDFA();
    
    std::cout <<"DFA states size = " << DFA.size() << std::endl;
    
    map<int,State> minimalDFA = s.minimizeDFA(DFA);
    int startStateID = s.getStartStateID();
    int deadStateID = s.getDeadStateID();
    std::cout <<"minimal DFA states size = " << minimalDFA.size() << std::endl;
    struct DFA dfa(startStateID,deadStateID,minimalDFA);
    return dfa;
}


int main(){
    struct DFA dfa = initialize_lexical_parser();
    string program_input = Utils::readFile(Globals::PROGRAM_INPUT_FILE);
    string test_program_input = Utils::readFile(Globals::TEST_INPUT_FILE);
    vector<Token> tokens = LexicalAnalyzer::getTokens(program_input,dfa.startStateID,dfa.deadStateID,dfa.minimalDFA);
    Utils::printMapFile(dfa.minimalDFA);  
    Token endToken("$","$",112);
    tokens.push_back(endToken);

    string syntaxRules = Utils::readFile(Globals::SYNTAX_RULES_FILE);
    // cout<< "Read file \n";
    SyntaxParser sp(syntaxRules);
    // cout<< "Passed rules to parser \n";

    cout<< "\nProductions before LL1\n";
    Utils::printProductions(sp.getProductions());
    LL1_Processor processor;
    cout<< "\nProductions after LL1\n";
    map<string,vector<vector<string>>> processedProduction = processor.getLL1productions(sp.getProductions());

    Utils::printProductions(processedProduction);
    FirstFollowBuilder ffb(processedProduction, processor.getNonTerminals());
    // cout<< "first follow \n";
    auto first = ffb.getFirst();
    auto follow = ffb.getFollow();
    ParseTreeBuilder parseTreeBuilder(first,  follow, sp.getTerminals());
    cout<< "First sets \n";
    ffb.printFirstMap();
    // cout<< "map  \n";
    cout<< "Follow sets \n";
    ffb.printFollowMap();
    // cout<< "map  \n";
    
    std::map<std::string, std::map<std::string, std::vector<std::string>>> parseTree = parseTreeBuilder.buildParseTree();
    parseTreeBuilder.printParseTree(parseTree);


    LL1Parser ll1parser(parseTree); 
    ll1parser.parse(tokens, Globals::START_SYMBOL);

    ll1parser.saveToCSV("SimulationParsing.csv");


    return 0;
}
