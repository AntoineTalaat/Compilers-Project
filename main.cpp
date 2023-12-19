#include <iostream>
#include "src/nfa.h"
#include "src/subset_construction.h"
#include "input_parser.h"
#include "lexical_analyzer.h"


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
    for ( auto& token : tokens) {
        std::cout <<  token.type << " ( " << token.lexeme<< " ) " << std::endl;
    }
    return 0;

}
