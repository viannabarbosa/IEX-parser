#pragma once
#include "Message.h"
#include <string>

class IWriter {
public:
	virtual void CreateTable(std::string table, std::string symbol) = 0;
	virtual void Insert(std::string table, std::string symbol, TradeReport* tr) = 0;
	virtual void SaveData(std::string table) = 0;
};