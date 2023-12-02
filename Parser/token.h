#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token {
public:
    std::string type;
    std::string value;

    Token(const std::string& type, const std::string& value) : type(type), value(value) {}
};

#endif  // TOKEN_H