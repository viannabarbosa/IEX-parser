#pragma once
#include "IParser.h"
#include "Message.h"
#include "IWriter.h"
#include <unordered_set>
#include <memory>

class IexParser : public IParser
{
public:
	explicit IexParser(std::unique_ptr<IWriter> writer) : writer_{ std::move(writer) } {};
	void ParseMessage(const unsigned char* message);
	void SaveData();
private:
	std::unique_ptr<IWriter> writer_;
	std::unordered_set<std::string> symbols_;
};

