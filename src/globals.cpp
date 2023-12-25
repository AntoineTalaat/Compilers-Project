
#include "globals.h"
std::map<std::string,NFA> Globals::regularDefinitionNFA=*(new std::map<std::string,NFA>());
std::set<char> Globals::alphabet = *(new std::set<char>());
std::string Globals::START_SYMBOL = "";

#ifdef VS_CODE
const std::string Globals::LEXICAL_RULES_FILE = "lexical_rules.txt";
const std::string Globals::SYNTAX_RULES_FILE = "syntax_rules.txt";
const std::string Globals::PROGRAM_INPUT_FILE = "input.txt";
const std::string Globals::TEST_INPUT_FILE = "test.txt";
#else
const std::string BASE_PATH = "D:\\Engineer\\Level 4\\semester 9\\compilers\\project\\Lexical-Analyzer-Generator\\";
const std::string Globals::LEXICAL_RULES_FILE = BASE_PATH + "lexical_rules.txt";
const std::string Globals::SYNTAX_RULES_FILE = BASE_PATH +"syntax_rules.txt";
const std::string Globals::PROGRAM_INPUT_FILE = BASE_PATH +"input.txt";
const std::string Globals::TEST_INPUT_FILE = BASE_PATH + "text.txt";
#endif