# Lexical Analyzer Generator
 Phase-1 of a compilers project. This module uses rules written as regular definitions or regular expressions to generate recognizers for tokens in the form of deterministic (and non-deterministic) finite automata. 

 First, the rules are parsed and each rule is converted to NFA. then the NFAs are combined to do one general NFA to recognize all tokens. Then the NFA is converted to DFA 
