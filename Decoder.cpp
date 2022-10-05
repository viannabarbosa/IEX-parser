#include "Decoder.h"
#include "Parser.h"
#include <iostream>

void Decoder::DecodeData(const unsigned char* data)
{
	//ethernet + IP + UDP headers
	auto ptr = data + 42;
	Header* header = (Header*)ptr;
	ptr += sizeof(Header);

	for (size_t i = 0; i < header->MessageCount; i++)
	{		
		MessageBlock* messageBlock = (MessageBlock*)ptr;

		//for (auto i = 0; (i < messageBlock->MessageLenght); i++)
		//{
		//	// Start printing on the next after every 16 octets
		//	if ((i % 16) == 0) printf("\n");

		//	// Print each octet as hex (x), make sure there is always two characters (.2).
		//	printf("%.2x ", messageBlock->MessageData[i]);
		//}

		ptr += sizeof(MessageBlock);
		parser.ParseMessage(ptr);

		ptr += messageBlock->MessageLenght;
	}

}

void Decoder::End()
{
	parser.End();
}
