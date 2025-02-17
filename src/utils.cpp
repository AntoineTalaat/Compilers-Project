#include "utils.h"
#include "nfa.h"

std::string Utils::readFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return ""; // Return an empty string to indicate an error
    }
    std::stringstream buffer;
    buffer << inputFile.rdbuf(); // Read the entire file into the buffer
    inputFile.close();
    return buffer.str();
}


std::vector<std::string> Utils::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != std::string::npos) {
        if(!input.substr(start, end - start).empty());
            tokens.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }

    if(!input.substr(start, end - start).empty());
        tokens.push_back(input.substr(start, end));
    return tokens;
}


std::string Utils::trim(std::string str) {
    // Trim leading whitespaces and newline characters
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch) && ch != '\n';
    }));

    // Trim trailing whitespaces and newline characters
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch) && ch != '\n';
    }).base(), str.end());

    return str;
}


void Utils::printProductions(std::map<std::string, std::vector<std::vector<std::string>>> productions) {
    for (const auto& pair : productions) {
        std::cout << pair.first << " -> [";

        // Iterate through the vector of vectors
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it) {
            std::cout << "[";

            // Iterate through the inner vector
            for (auto elem_it = it->begin(); elem_it != it->end(); ++elem_it) {           
                if(*elem_it == "") std::cout << "@";
                else std::cout << *elem_it;
                // Print comma if not the last element in the vector
                if (std::next(elem_it) != it->end()) {
                    std::cout << ",";
                }
            }

            std::cout << "]";

            // Print comma if not the last vector
            if (std::next(it) != pair.second.end()) {
                std::cout << ",";
            }
        }

        std::cout << "]" << std::endl;
    }
}


void Utils::printSet(std::set<int> s , NFA nfa) {
    std::cout << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {

        std::cout << *it << " " << nfa.getStatesMap()[*it].getIsAccepting() << std::endl  ;
        
        if(nfa.getStatesMap()[*it].getIsAccepting()){
            std::cout << " " << nfa.getStatesMap()[*it].getAcceptedToken()->type << " " << 
            nfa.getStatesMap()[*it].getAcceptedToken()->priority;
        }

    }
    std::cout << "}";
}

void Utils::printMap(std::map<int, State> statesMap){
    std::cout << "States:\n";
    for (auto& state : statesMap) {
        std::cout << state.first << ": ";
        std::cout << (state.second.toString())<< std::endl;
    }
}
void Utils::printMapFile(std::map<int, State> statesMap){
    const std::string fileName = "TransitionTable.txt";

    // Open the file in output mode to overwrite existing content
    std::ofstream outputFile(fileName, std::ios_base::out);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    for (auto& state : statesMap) {
        outputFile << state.first << ": ";
        outputFile << (state.second.toString()) << std::endl;
    }

    outputFile.close();
}


void Utils::printStringVector(std::vector<std::string> v){
    for (const auto& str : v) {
        std::cout << str << ", ";
    }
    std::cout<<"\n";
}


std::string Utils::setToString(std::set<int> s) {

    std::string result = "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        result += std::to_string(*it);
        if (std::next(it) != s.end()) {
            result += ", ";
        }
    }
    result += "}";
    return result;
}



void Utils::printDFATransitionhs(std::map<std::pair<std::set<int>, char>, std::set<int>> Dtran){
    std::cout << "Nfa states " << std::endl ;
    for (const auto& transition : Dtran) {
        const auto& T = transition.first.first;
        char a = transition.first.second;
        const auto& U = transition.second;
        std::cout << "Dtran[{" << setToString(T)<< "}, " << a << "] = {" << setToString(U)<< "}\n";
    }
}
