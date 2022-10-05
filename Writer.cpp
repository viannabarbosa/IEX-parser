#include "Writer.h"
#include <stdexcept>

#define KXVER 3
//this needs to be AFTER including any std headers
//requires iphlpapi.lib and ws2_32.lib
#include "k.h"


Writer::Writer()
{
	handle_ = khp((S)"localhost", 5001);
	if (handle_ < 1) {
		throw std::runtime_error("error connecting to kdb server");
	}
}

void Writer::CreateTable(std::string table, std::string symbol)
{
	std::string query = table + "_" + symbol + R"(:([Id:`long$()]
				SaleConditionFlags:`byte$();
				Timestamp:`long$();
				Symbol:`symbol$();
				Size:`int$();
				Price:`long$();
				TradeId:`long$()))";
	k(handle_, (S)query.c_str(), 0);
	return;
}

void Writer::Insert(std::string table, std::string symbol, TradeReport* tr)
{
	std::string tableName = trim(table + "_" + symbol);


	K row = knk(7, kj(i++), kg(tr->SaleConditionFlags), kj(tr->Timestamp), ks((S)symbol.c_str()), ki(tr->Size), kj(tr->Price), kj(tr->TradeId));
	K r = k(-handle_, (S)"insert", ks((S)tableName.c_str()), row, 0);
	return;
}

std::string Writer::trim(const std::string& str, const std::string& whitespace)
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

void Writer::End(std::string table)
{
	std::string query = "`:C:/Gatech/Courses/PracticeQCF/kdb/data/" + table + " set " + table;
	k(handle_, (S)query.c_str(), 0);
}


