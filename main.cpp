#include <iostream>
#include "src/nfa.h"
#include "src/subset_construction.h"
#include "input_parser.h"


using namespace std;
int main(){

//    string file = "D:\\Engineer\\Level 4\\semester 9\\compilers\\project\\Lexical-Analyzer-Generator\\rules.txt";
   string file = "rules.txt";
   string content = Utils::readFile(file);
   cout<<content<<endl;
   InputParser ip;
   char delimiter = '\n';

   std::vector<std::string> lines = Utils::splitString(content, delimiter);

   for (int i=0;i<lines.size();i++){
       cout<<"\nLINE " <<lines[i]<<endl;
       ip.tokenize(lines[i],i);
       cout<<endl;
   }

    int i=0;
    std::vector<NFA> allNFAs = ip.allNFAs;
    // for ( auto& nfa : allNFAs) {
    //     std::cout << "NFA index " <<i << std::endl;
    //     std::cout << "NFA start state : " << nfa.getStartState().getId() << ", " << nfa.getStartState().getIsAccepting()<< std::endl;
    //     std::cout << "NFA final state: " << nfa.getFinalState().getId() << ", " << nfa.getFinalState().getIsAccepting()<< std::endl;
    //     std::map<int, State> statesMap = nfa.getStatesMap();
    //     std::cout << "statesMap size: " << statesMap.size() << std::endl;
    //     for ( auto& state : statesMap) {
    //         std::cout << "      state: " << state.first << ", " << state.second.getIsAccepting() << std::endl;
    //     }
    //     std::cout << "------------------------------------------------------------------" << std::endl;
    //     i++;
    // }

    NFA n = NFAGenerator::getFullNFA(ip.allNFAs) ;
    std::cout << "start state: " << n.getStartState().getId() << ", " << n.getStartState().getIsAccepting()<< std::endl;
    std::cout << "final state: " << n.getFinalState().getId() << ", " << n.getFinalState().getIsAccepting()<< std::endl;
    std::map<int, State> statesMap = n.getStatesMap();
    std::cout << "statesMap size: " << statesMap.size() << std::endl;
    for ( auto& state : statesMap) {
        std::cout << "state: " << state.first << ", " << state.second.getIsAccepting() << std::endl;
    }

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
   std::map<std::pair<State, char>, State> Dtrans = s.getDFA();
   std::cout << Dtrans.size() << std::endl;

   std::cout << "Dtrans new states :\n";
   for ( const auto& transition : Dtrans) {
       State T = transition.first.first;
       char a = transition.first.second;
       State U = transition.second;
       std::cout << "Dtran[{" << T.getId() << ", " << T.getIsAccepting() <<
                                               "}, " << a << "] = {" <<
                                   U.getId() << ", " << U.getIsAccepting()
                                   <<"}\n";

       // std::cout << "Dtran[{" << T.getId() << ", " << T.getIsAccepting() << "] = {" <<
       //                     U.getId() << ", " << U.getIsAccepting()  << "}\n";
   }


   return 0;

}
