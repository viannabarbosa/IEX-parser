#include <string>
#include <iostream>
#include <time.h>
#include <iomanip>

// tutorial: https://www.rhyous.com/2011/11/12/how-to-compile-winpcap-with-visual-studio-2010/
// small error on Configuration 4 - should be wpcap.lib, not winpcap.lib
// note: we are using x64 so path is Lib\x64 https://stackoverflow.com/questions/46890411/how-to-read-a-pcap-file-from-wireshark-with-visual-c
// using npcap
#include <pcap.h>

#include "IDecoder.h"
#include "IexDecoder.h"
#include "IexParser.h"
#include "IexWriter.h"
#include <memory>

int main()
{
    std::unique_ptr<IDecoder> decoder = std::make_unique<IexDecoder>(
        std::make_unique<IexParser>(
            std::make_unique<IexWriter>()));
    
    if constexpr (std::endian::native == std::endian::big)
    {
        //IEX Data is little endian
        throw std::runtime_error("big endian system");
    }
    else if constexpr (std::endian::native == std::endian::little)
    {
        std::cout << "little endian system" << std::endl;
    }
    
    std::string file = "20170522_IEXTP1_DEEP1.0.pcap";
    decoder->SetDate("20170522");
    char errbuff[PCAP_ERRBUF_SIZE];

    pcap_t* pcap = pcap_open_offline_with_tstamp_precision(file.c_str(), PCAP_TSTAMP_PRECISION_MICRO, errbuff);

    struct pcap_pkthdr* header;
    const u_char* data;

    u_int packetCount = 0;
    
    while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
    {
        ++packetCount;
        if (packetCount % 100000 == 0) {
            printf("Packet # %i\n", packetCount);
        }        
        decoder->DecodeData(data);
    }
    decoder->SaveData();
    std::cout << "End of file";
}