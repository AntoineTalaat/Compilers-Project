#include <iostream>
#include "NFA/state.h"
#include "NFA/nfa.h"
#include "DFA/subset_construction.h"

using namespace std;
int main() { 
   // cout << "hi";
    State* s1 = new State();
    State* s2 = new State();
    State* s3 = new State();
    State* s4 = new State();
    State* s5 = new State();
    State* s6 = new State();
    State* s7 = new State();


    s1->addTransition('Epsilon', s1->getId());
    s1->addTransition('Epsilon', s7->getId());

    s2->addTransition('Epsilon', s3->getId());
    s2->addTransition('Epsilon', s5->getId());

    s3->addTransition('a', s4->getId());
    s4->addTransition('Epsilon', s7->getId());

    s5->addTransition('b', s6->getId());
    s6->addTransition('Epsilon', s7->getId());

    s7->addTransition('Epsilon', s2->getId());





    NFA nfa = *new NFA(s1, s7 , {s1, s2, s3, s4, s5, s6, s7});

    SubsetConstruction s = *new SubsetConstruction(nfa);
    s.setAlphabet({'a', 'b',static_cast<char>('Epsilon')});
    std::map<std::pair<std::set<int>, char>, std::set<int>> Dtrans = s.convertNFAToDFA();

    std::cout << "DFA Transitions:\n";
    for (const auto& transition : Dtrans) {
        const auto& T = transition.first.first;
        char a = transition.first.second;
        const auto& U = transition.second;
        std::cout << "Dtran[{" << *T.begin() << "}, " << a << "] = {" << *U.begin() << "}\n";
    }


    return 0;
};