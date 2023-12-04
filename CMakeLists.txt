cmake_minimum_required(VERSION 3.26)
project(Lexical_Analyzer_Generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Lexical_Analyzer_Generator
        src/dfa.cpp
        src/dfa.h
        src/files_helper.h
        src/globals.h
        src/infix_to_postfix.cpp
        src/infix_to_postfix.h
        src/input_parser.cpp
        src/input_parser.h
        src/nfa.cpp
        src/nfa.h
        src/nfa_generator.cpp
        src/nfa_generator.h
        src/operations_handler.cpp
        src/operations_handler.h
        src/regular_expression.h
        src/state.cpp
        src/state.h
        src/subset_construction.h
        src/SubsetConstruction.cpp
        src/token.cpp
        src/token.h
        main.cpp)
