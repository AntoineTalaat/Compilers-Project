#ifndef TOKEN_H
#define TOKEN_H

#include <bits/stdc++.h>
// #include <string>



class Token {
public:
    std::string type;
    std::string lexeme;
    int priority;

    Token();
    Token(std::string type,std::string lexeme, int priority);
};

#endif  // TOKEN_H