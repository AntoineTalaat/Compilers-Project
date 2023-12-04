#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
class Utils{
    public:
        static std::string readFile(const std::string& filename);
        static std::vector<std::string> splitString(const std::string& input, char delimiter);
        static std::string trim(std::string str);
};

#endif // UTILS_H
