#pragma once
#include <cstdint>

/* Data types
Long int64_t
Integer uint32_t
Short uint16_t
Byte uint8_t
Timestamp int64_t
String char[]
Price int64_t
Event time uint32_t
*/
#pragma pack(1)

struct Message {};

struct Header {
	uint8_t Version;
	uint8_t Padding;
	uint16_t MessageProtocolId;
	uint32_t ChannelId;
	uint32_t SessionId;
	uint16_t PayloadLenght;
	uint16_t MessageCount;
	int64_t StreamOffset;
	int64_t FirstMessageSeqNum;
	int64_t SendTime;
};

struct MessageBlock {
	uint16_t MessageLenght;
	uint8_t MessageData[0];
};

struct TradeReport : Message {
	char MessageType;
	uint8_t SaleConditionFlags;
	int64_t Timestamp;
	char Symbol[8];
	uint32_t Size;
	int64_t Price;
	int64_t TradeId;
};

struct PriceLevelUpdate : Message {
	char MessageType;
	uint8_t EventFlags;
	int64_t Timestamp;
	char Symbol[8];
	uint32_t Size;
	int64_t Price;
};

#pragma pack(pop)