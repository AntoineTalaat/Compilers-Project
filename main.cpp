#include <iostream>
#include "src/nfa.h"
#include "src/subset_construction.h"
#include "input_parser.h"


using namespace std;
int main(){

    //  State* s1 = new State(new Token("", "",  0));
    //  State* s2 = new State(new Token("", "",  0));
    //  State* s3 = new State(new Token("", "",  0));
    //  State* s4 = new State(new Token("", "",  0));
    //  State* s5 = new State(new Token("", "",  0));
    //  State* s6 = new State(new Token("", "",  0));
    //  State* s7 = new State(new Token("", "",  0));
    //  State* s8 = new State(new Token("id", "",  1));
    //  s8->setIsAccepting(true);
    //  State* s9 = new State(new Token("", "",  0));
    //  State* s10 = new State(new Token("", "",  0));
    //  State* s11 = new State(new Token("if", "",  0));
    //  s11->setIsAccepting(true);

    //  s1->addTransition(EPSILLON, s2->getId());
    //  s1->addTransition(EPSILLON, s8->getId());

    //  s2->addTransition(EPSILLON, s3->getId());
    //  s2->addTransition(EPSILLON, s5->getId());

    //  s3->addTransition('a', s4->getId());
    //  s4->addTransition(EPSILLON, s7->getId());

    //  s5->addTransition('b', s6->getId());
    //  s6->addTransition(EPSILLON, s7->getId());

    //  s7->addTransition(EPSILLON, s2->getId());
    //  s7->addTransition(EPSILLON, s8->getId());


    //  s8->addTransition('a', s9->getId());
    //  s9->addTransition('b', s10->getId());
    //  s10->addTransition('b', s11->getId());

    // s8->addTransition('a', s9->getId());
    // s9->addTransition('b', s10->getId());
    // s10->addTransition('b', s11->getId());




    //  map<int, State *> m;
    //  m[s1->getId()] = s1;
    //  m[s2->getId()] = s2;
    //  m[s3->getId()] = s3;
    //  m[s4->getId()] = s4;
    //  m[s5->getId()] = s5;
    //  m[s6->getId()] = s6;
    //  m[s7->getId()] = s7;
    //  m[s8->getId()] = s8;
    //  m[s9->getId()] = s9;
    //  m[s10->getId()] = s10;
    //  m[s11->getId()] = s11;

    //  NFA *nfa = new NFA(s1 ,m);




    // SubsetConstruction *s = new SubsetConstruction(*nfa);
    // s->setAlphabet({'a', 'b' , EPSILLON});
    // std::map<std::pair<State*, char>, State*> Dtrans = s->getDFA();
    // std::cout << Dtrans.size() << std::endl;

    // std::cout << "Dtrans new states :\n";
    // for (const auto& transition : Dtrans) {
    //     const auto& T = transition.first.first;
    //     char a = transition.first.second;
    //     const auto& U = transition.second;
    //     std::cout << "Dtran[{" << T->getId() << ", " << T->getIsAccepting() << "," << T->getAcceptedToken()->type<<
    //                                             "}, " << a << "] = {" <<
    //                                 U->getId() << ", " << U->getIsAccepting()<<  "," << U->getAcceptedToken()->type << ","
    //                                 << U->getAcceptedToken()->priority<<"}\n";
    // }



   string file = "rules.txt";
   string content = Utils::readFile(file);
   cout<<content<<endl;
   InputParser ip;
   char delimiter = '\n';

   std::vector<std::string> lines = Utils::splitString(content, delimiter);

   for (const auto& line : lines) {
       cout<<"\nLINE " <<line<<endl;
       ip.tokenize(line,0);
       cout<<endl;
   }
   return 0;

}
/*
 * int main() {

    State* s1 = new State();
    State* s2 = new State();
    State* s3 = new State();
    State* s4 = new State();
    State* s5 = new State();
    State* s6 = new State();
    State* s7 = new State();


    s1->addTransition(EPSILLON, s2->getId());
    s1->addTransition(EPSILLON, s7->getId());

    s2->addTransition(EPSILLON, s3->getId());
    s2->addTransition(EPSILLON, s5->getId());

    s3->addTransition('a', s4->getId());
    s4->addTransition(EPSILLON, s7->getId());

    s5->addTransition('b', s6->getId());
    s6->addTransition(EPSILLON, s7->getId());

    s7->addTransition(EPSILLON, s2->getId());

    map<int, State *> m;

    m[s1->getId()] = s1;
    m[s2->getId()] = s2;
    m[s3->getId()] = s3;
    m[s4->getId()] = s4;
    m[s5->getId()] = s5;
    m[s6->getId()] = s6;
    m[s7->getId()] = s7;



    NFA *nfa = new NFA(s1 ,m);

    SubsetConstruction *s = new SubsetConstruction(*nfa);
    s->setAlphabet({'a', 'b'});
    std::map<std::pair<std::set<int>, char>, std::set<int>> Dtrans = s->convertNFAToDFA();




    return 0;
};
 */
