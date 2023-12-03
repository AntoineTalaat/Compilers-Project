#include "token.h"

Token::Token(){
    this->type="unknown";
    this->value="";
}


Token::Token(std::string type, std::string value)
{
    this->type = type;
    this->value = value;
}
