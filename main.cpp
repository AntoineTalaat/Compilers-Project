// #include <iostream>
#include "src/nfa.h"
#include "src/input_parser.h"
#include "src/subset_construction.h"
#include "src/nfa_generator.h"

using namespace std;
int main(){

    // State* s1 = new State();
    // State* s2 = new State();
    // State* s3 = new State();
    // State* s4 = new State();
    // State* s5 = new State();
    // State* s6 = new State();
    // State* s7 = new State();
    // State* s8 = new State();
    // State* s9 = new State();
    // State* s10 = new State();
    // State* s11 = new State();

    // s1->addTransition(EPSILLON, s2->getId());
    // s1->addTransition(EPSILLON, s8->getId());

    // s2->addTransition(EPSILLON, s3->getId());
    // s2->addTransition(EPSILLON, s5->getId());

    // s3->addTransition('a', s4->getId());
    // s4->addTransition(EPSILLON, s7->getId());

    // s5->addTransition('b', s6->getId());
    // s6->addTransition(EPSILLON, s7->getId());

    // s7->addTransition(EPSILLON, s2->getId());
    // s7->addTransition(EPSILLON, s8->getId());

    // s8->addTransition('a', s9->getId());
    // s9->addTransition('b', s10->getId());
    // s10->addTransition('b', s11->getId());

    // map<int, State *> m;
    // m[s1->getId()] = s1;
    // m[s2->getId()] = s2;
    // m[s3->getId()] = s3;
    // m[s4->getId()] = s4;
    // m[s5->getId()] = s5;
    // m[s6->getId()] = s6;
    // m[s7->getId()] = s7;
    // m[s8->getId()] = s8;
    // m[s9->getId()] = s9;
    // m[s10->getId()] = s10;
    // m[s11->getId()] = s11;

    // NFA *nfa = new NFA(s1 ,m);

    // SubsetConstruction *s = new SubsetConstruction(*nfa);
    // s->setAlphabet({'a', 'b' , EPSILLON});
    // std::map<std::pair<std::set<int>, char>, std::set<int>> Dtrans = s->convertNFAToDFA();


    string file = "rules.txt";
    string content = Utils::readFile(file);
    cout<<content<<endl;
    InputParser ip;
    char delimiter = '\n';

    std::vector<std::string> lines = Utils::splitString(content, delimiter);

    for (const auto& line : lines) {
        cout<<"\nLINE " <<line<<endl;
        ip.tokenize(line);
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
