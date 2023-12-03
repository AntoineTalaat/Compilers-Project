#ifndef STATE_H
#define STATE_H

#include <string>
#include <set>
#include <map>
#include <bits/stdc++.h>
#include "token.h"

class State {
    private:
        int id;
        bool isAccepting;
        Token acceptedToken;
        std::map<char, std::set<int>> transitions;

    public:
        static int counterGlobalId;

        State();
        State(bool isAccepting);
        State(int id, bool isAccepting);
        
        
        static int generateId();

        void setId(int id);
        int getId();
        void setIsAccepting(bool isAccepting);
        bool getIsAccepting();
        Token getAcceptedToken();
        void setAcceptedToken(Token t);
        std::map<char, std::set</**State*/int>> getTransitions();
        void addTransition(char letter, int state);
};
#endif  // STATE_H