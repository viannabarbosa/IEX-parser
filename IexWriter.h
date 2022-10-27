#pragma once
#include "Message.h"
#include "IWriter.h"
#include <string>

#define KXVER 3
//this needs to be AFTER including any std headers
//requires iphlpapi.lib and ws2_32.lib
#include "k.h"

class IexWriter : public IWriter
{
public:
	IexWriter();
	void CreateTable(std::string table, std::string symbol);
	void Insert(std::string table, std::string symbol, Message* msg);
	void SaveData(std::string table, std::string date, std::string symbol);
private:
	std::string GetQuery(const std::string& table, const std::string& symbol);
	K GetRow(const std::string& table, const std::string& symbol, Message* msg);
	int handle_;
	int i = 0;
};

