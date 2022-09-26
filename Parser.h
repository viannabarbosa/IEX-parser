#pragma once
#include "Message.h"
//#include <parquet/stream_writer.h>
//#include <arrow/io/file.h>

class Parser
{
public:
	Parser();
	void ParseMessage(const unsigned char* message);
private:
	int handle_;
	int i = 0;
};

