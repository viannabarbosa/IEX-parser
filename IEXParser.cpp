#include <string>
#include <iostream>
// tutorial: https://www.rhyous.com/2011/11/12/how-to-compile-winpcap-with-visual-studio-2010/
// small error on Configuration 4 - should be wpcap.lib, not winpcap.lib
// note: we are using x64 so path is Lib\x64 https://stackoverflow.com/questions/46890411/how-to-read-a-pcap-file-from-wireshark-with-visual-c
// using npcap
#include <pcap.h>

int main()
{
    std::string file = "C:\\users\\jared\\testfiles\\smallcapture.pcap";
    char errbuff[PCAP_ERRBUF_SIZE];

    pcap_t* pcap = pcap_open_offline(file.c_str(), errbuff);

    std::cout << "Hello World!\n";
}
