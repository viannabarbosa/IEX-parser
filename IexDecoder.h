#pragma once
#include "IDecoder.h"
#include "Message.h"
#include "IParser.h"
#include <memory>

class IexDecoder : public IDecoder
{
public:
	explicit IexDecoder(std::unique_ptr<IParser> parser) : parser_{ std::move(parser) } {};
	void DecodeData(const unsigned char* data);
	void SaveData();
private:
	std::unique_ptr<IParser> parser_;
};

