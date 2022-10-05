#pragma once

#include "Message.h"
#include "Parser.h"

class Decoder
{
public:
	void DecodeData(const unsigned char* data);
	void End();
private:
	Parser parser;
};

