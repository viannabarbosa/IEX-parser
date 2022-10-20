#pragma once

class IDecoder {
public:
    virtual void DecodeData(const unsigned char* data) = 0;
    virtual void SaveData() = 0;
};