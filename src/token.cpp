#include "token.h"

Token::Token(){
    this->type = "unknown";
    this->lexeme = "";
    this->priority = 0;
}


Token::Token(std::string type, std::string lexeme, int priority)
{
    this->type = type;
    this->lexeme = lexeme;
    this->priority = priority;
}
