#include "input_parser.h"
#include "globals.h"

const std::regex InputParser::regDefRegex("\\s*\\w*\\s*=[\\s*[\\w\\W]*]*");
const std::regex InputParser::regExpRegex("\\s*\\w*\\s*:[\\s*[\\w\\W]*]*");
const std::regex InputParser::keywordRegex("\\s*\\{[\\s\\a-zA-Z]+\\}\\s*");
const std::regex InputParser::punctuationRegex("\\s*\\[\\W+\\]\\s*");
static std::vector<Token> tokens;
std::vector<std::string> InputParser::keywords;
std::vector<std::string> InputParser::punctuationSymbols;
std::vector<NFA*> allNFAs;

void InputParser::tokenize(std::string line, int priority) {
    std::cout << line<<"\n";
    if(regex_match(line, regDefRegex))            parseRegDef(line);
    else if(regex_match(line, regExpRegex))       parseRegExp(line, priority);
    else if(regex_match(line, keywordRegex))      parseKeyword(line, priority);
    else if(regex_match(line, punctuationRegex))  parsePunctuation(line, priority);
    else { 
        throw std::invalid_argument("received unknownnnnn rule typeeeeee");
    }
};

void InputParser::parseRegDef(std::string str) {
    str = Utils::trim(str);                                            // trim expression
    std::vector<std::string> sides = Utils::splitString(str, '=');     // split on =
    assert(sides.size()==2);                                           // assert 2 sides only
    std::string lhs=Utils::trim(sides[0]);                             // trim lhs
    std::string rhs=Utils::trim(sides[1]);                             // trim rhs
    assert(Utils::splitString(lhs, ' ').size()==1);                    // assert the lhs is one word not separated by more spaces
    std::vector<std::string> infix = *generateInfix(rhs);
    std::vector<std::string> postfix = InfixToPostfix::convert(infix);
    NFA* nfa = NFAGenerator::generateNFAFromPostfix(postfix);
    Globals::regularDefinitionNFA[lhs]=nfa;
    std::cout<<"ADDED TO NFA MAP " << lhs<< ">>>"<< rhs <<'\n';
    Globals::regularDefinitionNFA[lhs]=nfa;

    // std::cout<<"MAP " << (Globals::regularDefinitionNFA.find(lhs)!=Globals::regularDefinitionNFA.end()) <<'\n';
    allNFAs.push_back(nfa);
};

void InputParser::parseRegExp(std::string str, int priority) {
    // std::cout<<"found reg def" << "\n";
    str = Utils::trim(str);                                            // trim expression
    std::vector<std::string> sides = Utils::splitString(str, ':');     // split on :
    assert(sides.size()==2);                                           // assert 2 sides only
    std::string lhs=Utils::trim(sides[0]);                             // trim lhs
    std::string rhs=Utils::trim(sides[1]);                             // trim rhs
    assert(Utils::splitString(lhs, ' ').size()==1);                    // assert the lhs is one word not separated by more spaces
    std::vector<std::string> infix = *generateInfix(rhs);
    std::vector<std::string> postfix = InfixToPostfix::convert(infix);
    NFA* nfa = NFAGenerator::generateNFAFromPostfix(postfix);
    
    // TODO setup the token
    Token* tk = new Token(lhs, "", priority);
    nfa->getFinalState()->setAcceptedToken(tk);
    allNFAs.push_back(nfa);
};

void InputParser::parseKeyword(std::string line, int priority) {
    // std::cout<<"found keyword" << "\n";
    std::string keywordStr = line.substr(1, line.length() - 2); 
    keywordStr=Utils::trim(keywordStr);
    std::vector<std::string> keywords = Utils::splitString(keywordStr,' ');
    for (const auto& keyword : keywords) {
        NFA* nfa = NFAGenerator::generateNFAFromString(keyword);
        allNFAs.push_back(nfa);
        // TODO setup the token
        Token* tk = new Token(keyword, "", priority);
        nfa->getFinalState()->setAcceptedToken(tk);
        allNFAs.push_back(nfa);
    }

};

void InputParser::parsePunctuation(std::string line, int priority) {
    // std::cout<<"found punct" << "\n";
    std::string punctStr = line.substr(1, line.length() - 2); 
    punctStr=Utils::trim(punctStr);
    std::vector<std::string> puncts = Utils::splitString(punctStr,' ');
    for (const auto& punct : puncts) {
        assert(punct.length()==1 || punct.length()==2 && punct[0] =='\\');
        std::string str = "" ;
        str += punct[punct.length()-1];
        NFA* nfa = NFAGenerator::generateNFAFromString(str);
        allNFAs.push_back(nfa);
        // TODO setup the token
        Token* tk = new Token(punct, "", priority);
        nfa->getFinalState()->setAcceptedToken(tk);
        allNFAs.push_back(nfa);
    }
};

std::vector<std::string>* InputParser::generateInfix(std::string s){
    int size = s.length();
    int i=0;
    std::vector<std::string>* infix = new std::vector<std::string> (); //TODO check if u need pointer
    std::string word= "";
    while (i<size) {
        if(s[i] == ' ') {
            if(!word.empty()) {
                (*infix).push_back(word);
                // std::cout<< "HHHHHH " << word << "\n";
                word = "";
            }
            i++;
            continue;
        } 
        
        if(InfixToPostfix::isOperator(s[i]) || s[i]==')' || s[i]=='(') {
                if(!word.empty()) {
                    // std::cout<< "HHHHHH2 " << word << "\n";
                    (*infix).push_back(word);}
                word = "";
                word+= s[i];
                (*infix).push_back(word);
                // std::cout<< "HHHHHH3 " << word << "\n";
                word = "";
        }
        else {
            if(s[i]=='\\') {
                if(!word.empty()) {
                    // std::cout<< "HHHHHH4 " << word << "\n";
                    (*infix).push_back(word);
                }
                word = "";
                word=word+s[i]; // 
                i++;
                assert(i!=s.length());
                word=word+s[i]; // 
            }else{
                word=word+s[i];

            }
        }
        i++;
    }
    if(!word.empty()) {
        // std::cout<< "HHHHHH2 " << word << "\n";
        (*infix).push_back(word);
    }
    std::cout<<"Infix: ";
    for(const auto& line : *infix) {
        std::cout <<line<<" , ";
    }
    std::cout<<'\n';
    return infix;
};