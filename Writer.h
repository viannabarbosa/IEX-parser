#pragma once
#include "Message.h"
#include <string>

class Writer
{
public:
	Writer();
	void CreateTable(std::string table, std::string symbol);
	void Insert(std::string table, std::string symbol, TradeReport* tr);
	void End(std::string table);
	std::string trim(const std::string& str, const std::string& whitespace = " \t");
private:
	int handle_;
	int i = 0;
};

