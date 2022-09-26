#include <string>
#include <iostream>
#include <time.h>
#include <iomanip>
// tutorial: https://www.rhyous.com/2011/11/12/how-to-compile-winpcap-with-visual-studio-2010/
// small error on Configuration 4 - should be wpcap.lib, not winpcap.lib
// note: we are using x64 so path is Lib\x64 https://stackoverflow.com/questions/46890411/how-to-read-a-pcap-file-from-wireshark-with-visual-c
// using npcap
#include <pcap.h>

#include "Decoder.h"

int main()
{
    if constexpr (std::endian::native == std::endian::big)
    {
        std::cout << "big endian system" << std::endl;
    }
    else if constexpr (std::endian::native == std::endian::little)
    {
        std::cout << "little endian system" << std::endl;
    }
    std::cout << sizeof(MessageBlock) << std::endl;

    std::string file = "20170515_IEXTP1_DEEP1.0.pcap";
    char errbuff[PCAP_ERRBUF_SIZE];

    pcap_t* pcap = pcap_open_offline_with_tstamp_precision(file.c_str(), PCAP_TSTAMP_PRECISION_MICRO, errbuff);

    struct pcap_pkthdr* header;
    const u_char* data;

    u_int packetCount = 0;
    Decoder decoder;
    while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
    {
        ++packetCount;
        if (packetCount % 1000 == 0) {
            printf("Packet # %i\n", packetCount);
        }        
        //printf("Packet size: %ld bytes\n", header->len);

        //if (header->len != header->caplen)
        //    printf("Warning! Capture size different than packet size: %ld bytes\n", header->len);

        //printf("Epoch Time: %d:%d seconds\n", header->ts.tv_sec, header->ts.tv_usec);

        //time_t nowtime = header->ts.tv_sec;
        //struct tm nowtm;
        //localtime_s(&nowtm , &nowtime);
        //char tmbuf[64], buf[64];
        //std::cout << std::put_time(&nowtm, "%Z %c") << "." << header->ts.tv_usec << '\n';

        // loop through the packet and print it as hexidecimal representations of octets
        // We also have a function that does this similarly below: PrintData()
        for (u_int i = 0; (i < header->caplen); i++)
        {
            // Start printing on the next after every 16 octets
            //if ((i % 16) == 0) printf("\n");

            // Print each octet as hex (x), make sure there is always two characters (.2).
            //printf("%.2x ", data[i]);
        }
        decoder.DecodeData(data);

        // Add two lines between packets
        printf("\n\n");
    }

    std::cout << "Hello World!\n";
}