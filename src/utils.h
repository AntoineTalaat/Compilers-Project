#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
#include "nfa.h"

class Utils{
    public:
        static std::string readFile(const std::string& filename);
        static std::vector<std::string> splitString(const std::string& input, char delimiter);
        static std::string trim(std::string str);
        static void printSet(std::set<int> s , NFA nfa);
        static std::string setToString(std::set<int> s);
        static void printDFATransitionhs(std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran);
        static void printMap(std::map<int, State> statesMap);

        static void printStringVector(std::vector<std::string> v);

};

#endif // UTILS_H
