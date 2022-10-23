#pragma once
#include "Message.h"
#include "IWriter.h"
#include <string>

class IexWriter : public IWriter
{
public:
	IexWriter();
	void CreateTable(std::string table, std::string symbol);
	void Insert(std::string table, std::string symbol, TradeReport* tr);
	void SaveData(std::string table);
private:
	int handle_;
	int i = 0;
};

