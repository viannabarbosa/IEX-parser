#pragma once
#include "Message.h"
#include "Writer.h"
#include <unordered_set>

class Parser
{
public:
	Parser();
	void ParseMessage(const unsigned char* message);
	void End();
private:
	Writer writer_;
	std::unordered_set<std::string> symbols_;
};

