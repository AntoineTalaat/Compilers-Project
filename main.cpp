#include <iostream>
#include "src/nfa.h"
#include "src/subset_construction.h"
#include "input_parser.h"
#include "lexical_analyzer.h"

using namespace std;
int main(){
    string file = "rules.txt";
//    string file = "D:\\Engineer\\Level 4\\semester 9\\compilers\\project\\Lexical-Analyzer-Generator\\rules.txt";

    string content = Utils::readFile(file);
    InputParser ip;
    char delimiter = '\n';
    Globals::alphabet.insert(EPSILLON);
    std::vector<std::string> lines = Utils::splitString(content, delimiter);

    for (int i=0;i<lines.size();i++){
        ip.tokenize(lines[i],i);
    }
    int i=0;
    std::vector<NFA> allNFAs = ip.allNFAs;
    NFA n = NFAGenerator::getFullNFA(ip.allNFAs) ;

    std::cout <<"NFA states size = " << n.getStatesMap().size() << std::endl;
    SubsetConstruction s(n);
    s.setAlphabet(Globals::alphabet);
    std::map< int , State> DFA = s.getDFA();
    
    std::cout <<"DFA states size = " << DFA.size() << std::endl;
    int startStateID = s.getStartStateID();
    int deadStateID = s.getDeadStateID();
    map<int,State> minimalDFA = s.minimizeDFA(DFA);
    
    std::cout <<"minimal DFA states size = " << minimalDFA.size() << std::endl;

    // string input = Utils::readFile("input.txt");
    string input = Utils::readFile("test.txt");
    vector<Token> tokens = LexicalAnalyzer::getTokens(input,startStateID,deadStateID,minimalDFA);
    for ( auto& token : tokens) {
        std::cout <<  token.type << std::endl;
    }
    return 0;

}
