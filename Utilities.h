#pragma once
#include <vector>
#include <string>

class Utilities
{
public:
    /* Finds all float values separated by space in a line, starting at startPos and pushes them into vec */
    static void addValues(std::vector<float>* vec, int startPos, std::string* lineString);

    /* Splits a given string into integers, given a delimeter and starting point*/
    static std::vector<int> splitStringInts(std::string* str, int startPos, char delim);

    /* Splits a string by delimeter character */
    static std::vector<std::string> splitString(std::string* str, int startPos, char delim);

    /* Reads file into a string */
    static std::string getFileContent(const std::string& path);

    /* Reads file into a string, adding \n on each line */
    static std::string getFileContentDirect(const std::string& path);
};

