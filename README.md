# Project Name: Compiler Project - Phases 1 & 2

## Overview
This repository contains the source code and documentation for a team project involving the implementation of two phases of a compiler. The project was a collaborative effort of four team members aimed at building a compiler capable of lexical analysis (Phase 1) and syntax analysis (Phase 2).

## Project Phases

### Phase 1: Lexical Analysis
In Phase 1, our primary focus was on lexical analysis, where we designed and implemented algorithms to recognize tokens by scanning lexical rules. This involved the following steps:

1. **Lexical Rule Specification**: We defined lexical rules to describe the syntax of tokens in the input programming language.
2. **Nondeterministic Finite Automaton (NFA) Construction**: Based on the lexical rules, we constructed NFAs to represent the token recognition process.
3. **Deterministic Finite Automaton (DFA) Minimization**: We converted NFAs into minimal DFAs to optimize the token recognition process.
4. **Token Detection**: Utilizing the DFA, we implemented token detection logic to identify tokens from the input source code.

### Phase 2: Syntax Analysis
Phase 2 of the project involved syntax analysis, where we focused on parsing the input code based on grammar rules. Our approach included:

1. **Grammar Rule Examination**: We scanned the grammar rules of the programming language to understand its syntax structure.
2. **LL(1) Grammar Transformation**: To facilitate parsing, we transformed the grammar into LL(1) format by addressing issues such as left factoring and removing left recursion (both immediate and non-immediate).
3. **First and Follow Set Calculation**: We identified the first and follow sets of each non-terminal symbol in the grammar.
4. **Parse Table Generation**: Using the calculated first and follow sets, we constructed a parse table that facilitated the parsing process.
5. **Parsing Algorithm Implementation**: With the parse table in place, we implemented parsing algorithms to scan the input code and generate a stack of actions for each token, this also allows us to build parse tree.

## Team Members
- Antoine Talaat
- Mark Ehab
- Veronica Romany
- Yara Hossam

## Usage
- Input code followed some rules and constraints, they are to be added to the repository.
- A test input is to be found in the repo.
- The simulation stack is saved in an csv file in the same root directory.

## Dependencies
- Programming Language: C++

