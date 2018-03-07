
#include "headers.h"
#include <regex>




int Question::parseLine(string line) {
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

void Question::analyzeQueryType(string token) {
	int tokenAnalysis = parseLine(token);
	if (tokenAnalysis == 0) {
		//convert into c_string
		char* tokenCstr = new char[token.length + 1];
		strcpy(tokenCstr, token.c_str());
		//check validity of ip address using inet_addr()
		if (inet_addr(tokenCstr) != INADDR_NONE) {
			//ip address is good
			this->qhead.type = DNS_PTR;
		} //not good, discard
	}
	else if (tokenAnalysis == 1) {
		this->qhead.type = DNS_A;
	}
	
}



//Question::Question(void)  // constructor
//{
//
//
//}