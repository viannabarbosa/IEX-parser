#pragma once
#include "Message.h"
//#include <parquet/stream_writer.h>
//#include <arrow/io/file.h>

class Parser
{
public:
	static void ParseMessage(const unsigned char* message);
};

