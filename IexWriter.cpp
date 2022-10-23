#include "IexWriter.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

#define KXVER 3
//this needs to be AFTER including any std headers
//requires iphlpapi.lib and ws2_32.lib
#include "k.h"


IexWriter::IexWriter()
{
	handle_ = khp((S)"localhost", 5001);
	if (handle_ < 1) {
		throw std::runtime_error("error connecting to kdb server");
	}
}

void IexWriter::CreateTable(std::string table, std::string symbol)
{
	std::string query = table + "_" + symbol + ":([Id:`long$()]\n" +
		"SaleConditionFlags:`byte$();\n"
		"Timestamp:`long$();\n"
		"Symbol:`symbol$();\n"
		"Size:`int$();\n"
		"Price:`long$();\n"
		"TradeId:`long$())";

	k(handle_, (S)query.c_str(), 0);
}

void IexWriter::Insert(std::string table, std::string symbol, TradeReport* tr)
{
	std::string tableName = table + "_" + symbol;

	K row = knk(7, kj(i++), kg(tr->SaleConditionFlags), kj(tr->Timestamp), ks((S)symbol.c_str()), ki(tr->Size), kj(tr->Price), kj(tr->TradeId));
	K r = k(-handle_, (S)"insert", ks((S)tableName.c_str()), row, 0);
}

void IexWriter::SaveData(std::string table)
{
	std::string query = "`:C:/Gatech/Courses/PracticeQCF/kdb/data/" + table + " set " + table;
	k(handle_, (S)query.c_str(), 0);	
}


