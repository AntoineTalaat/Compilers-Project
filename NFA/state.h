#ifndef STATE_H
#define STATE_H

#include <string>
#include <set>
#include <map>
#include <bits/stdc++.h>
class State {
    private:
        int id;
        bool isAccepting;
        std::set<int> h;
        std::map<char, std::set</**State*/int>> transitions;
        int generateId();

    public:
        State();
        State(bool isAccepting);
        State(int id, bool isAccepting);
        
        void setId(int id);
        int getId();
        void setIsAccepting(bool isAccepting);
        bool getIsAccepting();
        std::map<char, std::set</**State*/int>> getTransitions();
        void State::addTransition(char letter, int state);
};
#endif  // STATE_H