#include <iostream>
#include "src/nfa.h"
#include "src/subset_construction.h"
#include "input_parser.h"
#include "lexical_analyzer.h"

using namespace std;
int main(){
    string file = "rules.txt";
    string content = Utils::readFile(file);
    InputParser ip;
    char delimiter = '\n';

    std::vector<std::string> lines = Utils::splitString(content, delimiter);

    for (int i=0;i<lines.size();i++){
        ip.tokenize(lines[i],i);
        cout<<endl;
    }
    int i=0;
    std::vector<NFA> allNFAs = ip.allNFAs;
    NFA n = NFAGenerator::getFullNFA(ip.allNFAs) ;
    SubsetConstruction s(n);
    s.setAlphabet({
        'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p', 'q', 'r',
        's', 't', 'u', 'v', 'w', 'x',
        'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '>','=','<','!',';', ',', '(', ')', '{', '}',
        '+', '-', '*', '/', EPSILLON});
    std::map< int , State> DFA = s.getDFA();
    std::cout << "DFA states size = " << DFA.size() << std::endl;
    std::map< int , State> minimizedDFA = s.minimizeDFA(DFA);
    std::cout << "MinimizedDFA states size = " << minimizedDFA.size() << std::endl;

    int startStateID = s.getStartStateID();
    int deadStateID = s.getDeadStateID();
    // string input = Utils::readFile("input.txt");
    string input = Utils::readFile("test.txt");

    vector<Token> tokens = LexicalAnalyzer::getTokens(input,startStateID,deadStateID,DFA);
    for ( auto& token : tokens) {
        std::cout << "token: " << token.type << " ( " << token.lexeme<< " ) " << std::endl;
    }
   return 0;

}
