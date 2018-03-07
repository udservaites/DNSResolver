/*	winsock.h
CPS 472 Sample Code

Define a class that handles socket APIs
*/


#pragma once 
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include "headers.h"

class Winsock {

private:
	char* recvBuffer;
	int recvBufferSize;
	int totalBytesRecv;

public:
	SOCKET	OpenSocket(void);
	bool send_to(SOCKET sock, char* send_buf, int count, const char* address, const char* port);
	bool recvFrom(SOCKET sock);

};