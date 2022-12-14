#include "IexDecoder.h"
#include <iostream>

void IexDecoder::DecodeData(const unsigned char* data)
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
		parser_->ParseMessage(ptr);

		ptr += messageBlock->MessageLenght;
	}

}

void IexDecoder::SaveData()
{
	parser_->SaveData();
}

void IexDecoder::SetDate(std::string date)
{
	parser_->SetDate(date);
}
