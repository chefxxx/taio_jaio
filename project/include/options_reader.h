//
// Created by mshamrai on 11/25/25.
//

#ifndef TAIO_PROJECT_OPTIONS_READER_H
#define TAIO_PROJECT_OPTIONS_READER_H
#include <algorithm>
#include <string>

inline char* getCmdOption(char** begin, char** end, const std::string& option)
{
    char** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return nullptr;
}

inline bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

void getAllParameters(std::string &inFile, std::string &outFile, std::string &algType, int& k, int argc, char **argv);

#endif // TAIO_PROJECT_OPTIONS_READER_H
