#include "IexParser.h"
#include <stdexcept>

void IexParser::ParseMessage(const unsigned char* message)
{
	char messageType = (char) (*message);
	switch (messageType)
	{
	//Adminstrative messages
	case('S')://System Event Message
	{
		break;
	};
	case('D')://Security Directory Message
	{
		break;
	};
	case('H')://Trading Status Message
	{
		break;
	};
	case('I')://Retail Liquidity Indicator Message
	{
		break;
	};
	case('O')://Operational Halt Status Message
	{
		break;
	};
	case('P')://Short Sale Price Test Status Message
	{
		break;
	};
	case('E')://Security Event Message
	{
		break;
	};
	//Trading messages
	case('8')://Price Level Update Message - Buy
	{
		break;
	};
	case('5')://Price Level Update Message - Sell
	{
		break;
	};
	case('T')://Trade Report Message
	{
		TradeReport* tr = (TradeReport*)message;
		auto symbolStr = std::string(tr->Symbol, 8);
		CreateTable(symbolStr, "TradeReport");
		writer_->Insert("TradeReport", symbols_[symbolStr], tr);
		break;
	}		
	case('X')://Official Price Message
	{
		break;
	};
	case('B')://Trade Break Message
	{
		break;
	};
	//Auction messages
	case('A')://Auction Information Message
	{
		break;
	}
	default:
		break;
	}
}

void IexParser::CreateTable(std::string& symbolStr, std::string table) {
	if (!symbols_.contains(symbolStr)) {
		auto alphaNumSymbolStr = symbolStr;
		alphaNumSymbolStr.erase(std::remove_if(alphaNumSymbolStr.begin(), alphaNumSymbolStr.end(), [](auto const& c) -> bool {
			return !std::isalnum(c);
			}), alphaNumSymbolStr.end());

		alphaNumSymbolStr = AvoidNameCollision(alphaNumSymbolStr);

		writer_->CreateTable(table, alphaNumSymbolStr);
		symbols_[symbolStr] = alphaNumSymbolStr;
	}
}

std::string IexParser::AvoidNameCollision(std::string& alphaNumSymbolStr)
{
	for (const auto& [key, value] : symbols_) {
		if (value == alphaNumSymbolStr) {
			alphaNumSymbolStr.push_back('a');
			alphaNumSymbolStr = AvoidNameCollision(alphaNumSymbolStr);
		}
	}
	return alphaNumSymbolStr;
}

void IexParser::SaveData()
{
	for (const auto& [key, value]: symbols_) {
		writer_->SaveData("TradeReport_" + value);
	}
	
}
