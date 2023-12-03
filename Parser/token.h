#ifndef TOKEN_H
#define TOKEN_H

#include <bits/stdc++.h>
// #include <string>



class Token {
public:
    std::string type;
    std::string value;

    Token();
    Token(std::string type,std::string value);
};

#endif  // TOKEN_H