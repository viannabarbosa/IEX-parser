#pragma once

class IParser {
public:
    virtual void ParseMessage(const unsigned char* message) = 0;
    virtual void SaveData() = 0;
};