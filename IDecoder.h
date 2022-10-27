#pragma once
#include <string>

class IDecoder {
public:
    virtual void DecodeData(const unsigned char* data) = 0;
    virtual void SaveData() = 0;
    virtual void SetDate(std::string date) = 0;
};