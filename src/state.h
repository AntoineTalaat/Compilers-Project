#ifndef STATE_H
#define STATE_H

#include <bits/stdc++.h>
#include "token.h"

class State {
    private:
        int id;
        bool isAccepting;
        Token* acceptedToken;
        std::map<char, std::set<int>> transitions;
    public:
        static int counterGlobalId;

        State();
        State(bool isAccepting);
        State(int id, bool isAccepting);
        State(Token* t);
        
        
        static int generateId();

        void setId(int id);
        int getId() const;
        bool operator<(const State& other) const;
        bool operator==(const State& other) const;
        void setIsAccepting(bool isAccepting);
        bool getIsAccepting();
        Token* getAcceptedToken();
        void setAcceptedToken(Token* t);
        std::map<char, std::set</**State*/int>> getTransitions();
        void addTransition(char letter, int state);
        void printTransitions();
        void printTransitions(int nextStateNumLowerBound);
        std::string toString();
};
namespace std {
    template <>
    struct hash<State> {
        std::size_t operator()(const State& s) const;
    };
}
#endif  // STATE_H