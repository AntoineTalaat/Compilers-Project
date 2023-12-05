#include <iostream>
#include "src/nfa.h"
#include "src/subset_construction.h"
#include "input_parser.h"


using namespace std;
int main(){




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
   
    SubsetConstruction s(NFAGenerator::getFullNFA(ip.allNFAs));
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
