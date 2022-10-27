#pragma once
#include <string>

class IParser {
public:
    virtual void ParseMessage(const unsigned char* message) = 0;
    virtual void SaveData() = 0;
    virtual void SetDate(std::string date) = 0;
};