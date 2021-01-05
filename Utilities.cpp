#include "Utilities.h"
#include <fstream>

void Utilities::addValues(std::vector<float>* vec, int startPos, std::string* lineString)
{
    int newPosition = lineString->find(' ', startPos);
    while (newPosition != std::string::npos)
    {
        newPosition = lineString->find(' ', startPos);
        vec->push_back(std::stof(lineString->substr(startPos, newPosition - startPos)));
        startPos = newPosition + 1;
    }
}

std::vector<int> Utilities::splitStringInts(std::string* str, int startPos, char delim)
{
    std::vector<int> returnVec;
    int newPosition = str->find(delim, startPos);
    while (newPosition != std::string::npos)
    {
        newPosition = str->find(delim, startPos);
        returnVec.push_back(std::stoi(str->substr(startPos, newPosition - startPos)));
        startPos = newPosition + 1;
    }
    return returnVec;
}

std::vector<std::string> Utilities::splitString(std::string* str, int startPos, char delim)
{
    std::vector<std::string> returnVec;
    int newPosition = str->find(delim, startPos);
    while (newPosition != std::string::npos)
    {
        newPosition = str->find(delim, startPos);
        returnVec.push_back(str->substr(startPos, newPosition - startPos));
        startPos = newPosition + 1;
    }
    return returnVec;
}

std::string Utilities::getFileContent(const std::string& path)
{
    std::ifstream file(path);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return content;
}

std::string Utilities::getFileContentDirect(const std::string& path)
{
    std::ifstream fileStream;
    fileStream.open(path, std::ifstream::in);
    std::string lineString = "";
    std::string content = "";
    while (std::getline(fileStream, lineString))
    {
        content += lineString + "\n";
    }

    return content;
}
