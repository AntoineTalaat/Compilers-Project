#include "utils.h"

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
        tokens.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }

    tokens.push_back(input.substr(start, end));
    return tokens;
}


std::string Utils::trim(std::string str){
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    }));

    // Trim trailing whitespaces
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), str.end());

    return str;
}

