#include "Parser.h"
#include <iostream>
#include <stdexcept>

void Parser::ParseMessage(const unsigned char* message)
{
	char messageType = (char) (*message);
	std::cout << "message type: " << messageType << std::endl;
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
		//https://github.com/apache/arrow/blob/master/cpp/examples/parquet/parquet_stream_api/stream_reader_writer.cc
		//std::shared_ptr<arrow::io::FileOutputStream> outfile;

		//PARQUET_ASSIGN_OR_THROW(
		//	outfile,
		//	arrow::io::FileOutputStream::Open("test.parquet"));

		//parquet::WriterProperties::Builder builder;
		//std::shared_ptr<parquet::schema::GroupNode> schema;

		//// Set up builder with required compression type etc.
		//// Define schema.
		//// ...
		//builder.compression(parquet::Compression::ZSTD);

		//parquet::schema::NodeVector fields;

		//fields.push_back(parquet::schema::PrimitiveNode::Make(
		//	"string_field", parquet::Repetition::REQUIRED, parquet::Type::BYTE_ARRAY,
		//	parquet::ConvertedType::UTF8));

		//schema = std::static_pointer_cast<parquet::schema::GroupNode>(
		//	parquet::schema::GroupNode::Make("schema", parquet::Repetition::REQUIRED, fields));

		//parquet::StreamWriter os{
		//   parquet::ParquetFileWriter::Open(outfile, schema, builder.build()) };

		//// Loop over some data structure which provides the required
		//// fields to be written and write each row.
		//for (const auto& a : getArticles())
		//{
		//	os << a.name() << a.price() << a.quantity() << parquet::EndRow;
		//}
		TradeReport* tr = (TradeReport*)message;
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
		throw std::runtime_error("");
		break;
	}
}
