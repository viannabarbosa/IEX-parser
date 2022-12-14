#pragma once
#include "IParser.h"
#include "Message.h"
#include "IWriter.h"
#include <unordered_map>
#include <memory>

class IexParser : public IParser
{
public:
	explicit IexParser(std::unique_ptr<IWriter> writer) : writer_{ std::move(writer) } {};
	void ParseMessage(const unsigned char* message);
	void CreateTables(std::string& symbolStr);
	void SaveData();
	void SetDate(std::string date);
private:
	std::unique_ptr<IWriter> writer_;
	std::unordered_map<std::string, std::string> symbols_;
	std::string AvoidNameCollision(std::string& alphaNumSymbolStr);
	bool UpdateSymbolMap(std::string& symbolStr);
	std::string date_;
};

