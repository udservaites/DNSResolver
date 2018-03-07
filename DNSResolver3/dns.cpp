/*	dns.h
CPS 472 Sample Code
*/

#include "headers.h"
#include "dns.h"
#include <regex>

// NOTE: link with Iphlpapi.lib; prints primary/second DNS server info

int DNS::parseLine(string line) {
	//compare line to regex for ip address or host name
	//cout << "\tChecking IP Address... " << endl;
	const regex regex_ip("\\d{1,}[.]\\d{1,}[.]\\d{1,}[.]\\d{1,}");
	const regex regex_host("(www.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}[.][a-zA-Z]{2,6}");
	smatch smatches;
	string tmp_port;
	int match = 0;
	try {
		if (regex_match(line, regex_ip)) {
			//cout << "IP address found!\n";
			return 0;
		}
		else if (regex_match(line, regex_host)) {
			//check if host. If not host, discard. 
			//cout << "Host found!" << endl;
			return 1;
		}

	}
	catch (...)
	{
		//cout << "Unable to parse ip address\n";
	}
	return -1;
}

// dnsIP is assigned the first IP address of local DNS servers after called
void DNS::printDNSServer(string & dnsIP)
{
	// MSDN sample code
	FIXED_INFO *FixedInfo;
	ULONG    ulOutBufLen;
	DWORD    dwRetVal;
	IP_ADDR_STRING * pIPAddr;

	ulOutBufLen = sizeof(FIXED_INFO);
	FixedInfo = (FIXED_INFO *)GlobalAlloc(GPTR, sizeof(FIXED_INFO));
	ulOutBufLen = sizeof(FIXED_INFO);

	if (ERROR_BUFFER_OVERFLOW == GetNetworkParams(FixedInfo, &ulOutBufLen)) {
		GlobalFree(FixedInfo);
		FixedInfo = (FIXED_INFO *)GlobalAlloc(GPTR, ulOutBufLen);
	}

	if (dwRetVal = GetNetworkParams(FixedInfo, &ulOutBufLen)) {
		printf("Call to GetNetworkParams failed. Return Value: %08x\n", dwRetVal);
	}
	else {
		printf("Host Name: %s\n", FixedInfo->HostName);
		printf("Domain Name: %s\n", FixedInfo->DomainName);

		printf("DNS Servers:\n");
		printf("\t%s\n", FixedInfo->DnsServerList.IpAddress.String);
		dnsIP = FixedInfo->DnsServerList.IpAddress.String;

		pIPAddr = FixedInfo->DnsServerList.Next;
		while (pIPAddr) {
			printf("\t%s\n", pIPAddr->IpAddress.String);
			pIPAddr = pIPAddr->Next;
		}
	}

	GlobalFree(FixedInfo);
}