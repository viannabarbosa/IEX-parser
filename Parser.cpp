#include "Parser.h"

Parser::Parser()
{
	writer_ = Writer();
}

void Parser::ParseMessage(const unsigned char* message)
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
		if (!symbols_.contains(symbolStr)) {
			writer_.CreateTable("TradeReport", symbolStr);
			symbols_.insert(symbolStr);
		}
		writer_.Insert("TradeReport", symbolStr, tr);
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

void Parser::End()
{
	for (const auto& symbol : symbols_) {
		writer_.End("TradeReport_"+symbol);
	}
	
}
