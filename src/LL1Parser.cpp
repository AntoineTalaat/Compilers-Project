#include "LL1Parser.h"

LL1Parser::LL1Parser(
    const std::map<std::string, std::map<std::string, std::vector<std::string>>>& parsingTable
) : parsingTable(parsingTable) {}

void LL1Parser::parse(
    const std::vector<Token>& tokens,
    const std::string& startSymbol
) {
    
    
    std::stack<std::string> stack;

    std::cout << "--------------------------------- Parsing Simulation-------------------------------" << std::endl;
    // Initialize stack with start symbol
    stack.push("$");
    stack.push(startSymbol);

    // Token index
    size_t tokenIndex = 0;
    std::cout << "Stack: " << stackToString(stack) << std::endl;
    std::cout << "Input: " << inputToString(tokens, tokenIndex) << std::endl;
    // Parsing loop
    while (!stack.empty()) {
        std::string stackTop = stack.top();
        

        // Check if stackTop exists in parsingTable case : (Non-terminal)
        if (parsingTable.find(stackTop) != parsingTable.end()) {
            // Get the current input token
            Token currentToken = (tokenIndex < tokens.size()) ? tokens[tokenIndex] : Token();  // Handle end of input
             if(currentToken.type != "$" && currentToken.type != "sync"){
                currentToken.type = "\'"+currentToken.type + "\'";
             }
            // Check if currentToken.type exists in the inner map
            if (parsingTable.at(stackTop).find(currentToken.type) != parsingTable.at(stackTop).end()) {
                // Get the corresponding production from the parsing table
                std::vector<std::string> production = parsingTable.at(stackTop).at(currentToken.type);
                 stack.pop();
               
     
                    // Case 1: Production rule has only "sync" in the rhs
                    if (production.size() == 1 && production[0] == "sync") {
                        std::cout << "Output: Error Missing " << stackTop << std::endl;
                       
                        // Pop from the stack and continue
                    } else {
                        // Case 2: Production rule has non-"sync" elements in the rhs
                        // Push the production onto the stack in reverse order
                        std::string prod =  "";

                        for (auto it = production.rbegin(); it != production.rend(); ++it) {
                            if (*it != "epsilon") {
                                stack.push(*it);
                                prod =  *it+ prod;
                                
                            }
                        }
                        std::cout << "Output: "<< stackTop <<" --> "<< prod << std::endl;
                    }
              
            } else {
                 // Case 3: No production for the input token
                // Handle the case where currentToken.type is not found in the inner map
                std::cout << "Output: Error Discard input token - " << currentToken.type << std::endl;
                // Move to the next input token
                ++tokenIndex;
                std::cout << "-----------leeeh----------" << std::endl;
                std::cout << "Stack: " << stackToString(stack) << std::endl;
                std::cout << "Input: " << inputToString(tokens, tokenIndex) << std::endl;
                if(currentToken.type=="$"){
                    break;
                }
                continue;
            }
        } else if (stackTop == "$" || tokens[tokenIndex].type=="$") {
            // If the stack is empty except for '$', parsing is successful
            std::cout << "Output: Parsing successful!" << std::endl;
            break;
        } else {
            // case :  ( terminal )
             stack.pop();
            Token currentToken = (tokenIndex < tokens.size()) ? tokens[tokenIndex] : Token();  // Handle end of input
          if(currentToken.type != "$" && currentToken.type != "sync"){
                currentToken.type = "\'"+currentToken.type + "\'";
             }
             
            // case 1: Match 
            if (stackTop == currentToken.type) {
                // Match found, move to the next input token
                std::cout << "Output : Match " << currentToken.type << " \" " << currentToken.lexeme << " \" " << std::endl;
                ++tokenIndex;
            } else {
                //case 2: mismatch 
                // Error handling: mismatch between stack and input
                std::cout << "Output: Error Mismatch between stack and input. Expected " << stackTop << std::endl;
                // Pop from the stack and continue
            }
        }
        
        // Print the current step (for demonstration purposes)
        std::cout << "---------------------" << std::endl;
        std::cout << "Stack: " << stackToString(stack) << std::endl;
        std::cout << "Input: " << inputToString(tokens, tokenIndex) << std::endl;
        
    }


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
