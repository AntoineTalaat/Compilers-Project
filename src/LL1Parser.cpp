#include "LL1Parser.h"

LL1Parser::LL1Parser(
    const std::map<std::string, std::map<std::string, std::vector<std::string>>>& parsingTable
) : parsingTable(parsingTable) {}

std::vector<std::string> LL1Parser::parse(
    const std::vector<Token>& tokens,
    const std::string& startSymbol
) {
    
    
    std::stack<std::string> stack;
    std::vector<std::string> output;
    output.push_back("--------------------------------- Parsing Simulation-------------------------------");
    // Initialize stack with start symbol
    stack.push("$");
    stack.push(startSymbol);

    // Token index
    size_t tokenIndex = 0;
    output.push_back("Stack: " + stackToString(stack));
    output.push_back("Input: " + inputToString(tokens, tokenIndex));
    // Parsing loop
    while (!stack.empty()) {
        std::string stackTop = stack.top();
        stack.pop();

        // Check if stackTop exists in parsingTable case : (Non-terminal)
        if (parsingTable.find(stackTop) != parsingTable.end()) {
            // Get the current input token
            Token currentToken = (tokenIndex < tokens.size()) ? tokens[tokenIndex] : Token();  // Handle end of input

            // Check if currentToken.type exists in the inner map
            if (parsingTable.at(stackTop).find(currentToken.type) != parsingTable.at(stackTop).end()) {
                // Get the corresponding production from the parsing table
                std::vector<std::string> production = parsingTable.at(stackTop).at(currentToken.type);

                // Case 1: No production for the input token
                // if (production.empty()) {
                //     output.push_back("Error: Discard input token - " + currentToken.type);
                //     // Move to the next input token
                //     ++tokenIndex;
                // } else {
                    // Case 2: Production rule has only "sync" in the rhs
                    if (production.size() == 1 && production[0] == "sync") {
                        output.push_back("Output: Error Missing " + stackTop);
                        // Pop from the stack and continue
                    } else {
                        // Case 3: Production rule has non-"sync" elements in the rhs
                        // Push the production onto the stack in reverse order
                        std::string prod =  "";

                        for (auto it = production.rbegin(); it != production.rend(); ++it) {
                            if (*it != "epsilon") {
                                stack.push(*it);
                                prod =  *it+ prod;
                                
                            }
                        }
                        output.push_back("Output: "+ stackTop +" --> "+ prod );
                    }
                //}
            } else {
                // Handle the case where currentToken.type is not found in the inner map
                 output.push_back("Output: Error Discard input token - " + currentToken.type);
                // Move to the next input token
                ++tokenIndex;
            }
        } else if (stackTop == "$") {
            // If the stack is empty except for '$', parsing is successful
            output.push_back("Output: Parsing successful!");
            break;
        } else {
            // case :  ( terminal )

            Token currentToken = (tokenIndex < tokens.size()) ? tokens[tokenIndex] : Token();  // Handle end of input

            if (stackTop == currentToken.type) {
                // Match found, move to the next input token
                output.push_back("Output : Match " + currentToken.type + " \" " + currentToken.lexeme + " \" ");
                ++tokenIndex;
            } else {
                // Error handling: mismatch between stack and input
                output.push_back("Output: Error Mismatch between stack and input. Expected " + stackTop);
                // Pop from the stack and continue
            }
        }
        
        // Print the current step (for demonstration purposes)
        output.push_back("---------------------");
        output.push_back("Stack: " + stackToString(stack));
        output.push_back("Input: " + inputToString(tokens, tokenIndex));
        
    }

    return output;
}



std::string LL1Parser::stackToString(const std::stack<std::string>& stack) {
    std::stack<std::string> tempStack = stack;
    std::vector<std::string> elements;

    while (!tempStack.empty()) {
        elements.push_back(tempStack.top());
        tempStack.pop();
    }

    std::string result;
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        result += *it + " ";
    }

    return result + "| ";
}


std::string LL1Parser::inputToString(const std::vector<Token>& tokens, size_t index) {
    std::string result;
    for (size_t i = index; i < tokens.size(); ++i) {
        result += tokens[i].type + " ";
    }
    return result + "| ";
}
