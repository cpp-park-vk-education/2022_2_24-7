// #include "Command.hpp"
#include "../include/Command.hpp"

std::vector<std::string> parseString(std::string str, char separator) {
        std::vector <std::string> parseString;
        
        std::stringstream stream(str);
        std::string segmentOfStream;

        while (std::getline(stream,segmentOfStream, separator)) {
            parseString.push_back(segmentOfStream);
        }

        return parseString;
};