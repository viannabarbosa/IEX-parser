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
	auto query = GetQuery(table, symbol);
	k(handle_, (S)query.c_str(), 0);
}

void IexWriter::Insert(std::string table, std::string symbol, Message* msg)
{
	K row = GetRow(table, symbol, msg);
	std::string tableName = table + "_" + symbol;

	K r = k(-handle_, (S)"insert", ks((S)tableName.c_str()), row, 0);
}

void IexWriter::SaveData(std::string table, std::string date, std::string symbol)
{
	auto tableName = table + "_" + symbol;
	std::string query = "`:C:/Gatech/Courses/PracticeQCF/kdb/data/" + date + "/" + table + "/" + tableName + " set " + tableName;
	k(handle_, (S)query.c_str(), 0);
}

std::string IexWriter::GetQuery(const std::string& table, const std::string& symbol)
{
	std::string query;
	if (table == "TradeReport") {
		query = table + "_" + symbol + ":([Id:`long$()]\n" +
			"SaleConditionFlags:`byte$();\n"
			"Timestamp:`long$();\n"
			"Symbol:`symbol$();\n"
			"Size:`int$();\n"
			"Price:`long$();\n"
			"TradeId:`long$())";
	}
	else if (table == "PriceLevelUpdate") {
		query = table + "_" + symbol + ":([Id:`long$()]\n" +
			"EventFlags:`byte$();\n"
			"Timestamp:`long$();\n"
			"Symbol:`symbol$();\n"
			"Size:`int$();\n"
			"Price:`long$();\n"
			"IsBuy:`boolean$())";
	}	
	return query;
}

K IexWriter::GetRow(const std::string& table, const std::string& symbol, Message* msg)
{
	K row = nullptr;
	if (table == "TradeReport") {
		auto tr = static_cast<TradeReport*>(msg);
		row = knk(7, kj(i++), kg(tr->SaleConditionFlags), kj(tr->Timestamp), ks((S)symbol.c_str()), ki(tr->Size), kj(tr->Price), kj(tr->TradeId));
	}
	else if (table == "PriceLevelUpdate") {
		auto plu = static_cast<PriceLevelUpdate*>(msg);
		auto isBuy = plu->MessageType == '8' ? true : false;
		row = knk(7, kj(i++), kg(plu->EventFlags), kj(plu->Timestamp), ks((S)symbol.c_str()), ki(plu->Size), kj(plu->Price), kb(isBuy));
	}
	return row;
}


