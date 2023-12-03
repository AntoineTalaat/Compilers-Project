#include <iostream>
#include "src/nfa.h"
#include "src/input_parser.h"
#include "src/subset_construction.h"
#include "src/nfa_generator.h"

using namespace std;
int main() { 
    cout << "hi";
    auto* s1 = new State();
    auto* p1 = new InputParser();
    auto* nfa = new NFAGenerator();


    /*
    State s2 = new State();
    State s3 = new State();
    State s4 = new State();
    State s5 = new State();
    State s6 = new State();
    State s7 = new State();


    s1.addTransition(EPSILLON, s1.getId());
    s1.addTransition(EPSILLON, s7.getId());

    s2.addTransition(EPSILLON, s3.getId());
    s2.addTransition(EPSILLON, s5.getId());

    s3.addTransition('a', s4.getId());
    s4.addTransition(EPSILLON, s7.getId());

    s5.addTransition('b', s6.getId());
    s6.addTransition(EPSILLON, s7.getId());

    s7.addTransition(EPSILLON, s2.getId());

    std::map<int, State> m;

    m[s1.getId()] = s1;
    m[s2.getId()] = s2;
    m[s3.getId()] = s3;
    m[s4.getId()] = s4;
    m[s5.getId()] = s5;
    m[s6.getId()] = s6;
    m[s7.getId()] = s7;



    NFA nfa = *new NFA(s1 ,m);

    SubsetConstruction s = *new SubsetConstruction(nfa);
    s.setAlphabet({'a', 'b',static_cast<char>(EPSILLON)});
    std::map<std::pair<std::set<int>, char>, std::set<int>> Dtrans = s.convertNFAToDFA();

    std::cout << "DFA Transitions:\n";
    for (const auto& transition : Dtrans) {
        const auto& T = transition.first.first;
        char a = transition.first.second;
        const auto& U = transition.second;
        std::cout << "Dtran[{" << *T.begin() << "}, " << a << "] = {" << *U.begin() << "}\n";
    }

*/
    return 0;
};