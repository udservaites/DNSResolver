#define _WINSOCK_DEPRECATED_NO_WARNINGS //must come first

#pragma once
#include "winsock.h"




SOCKET Winsock::OpenSocket(void)
{
	// open a UDP socket
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);  //SOCK_DGRAM for UDP sockets
	if (sock == INVALID_SOCKET)
	{
		printf("socket() generated error %d\n", WSAGetLastError());
		WSACleanup();
		exit(-1);	// not graceful, but sufficient for our purposes
	}

	struct sockaddr_in bind_addr;

	// bind to the local address and port 0
	bind_addr.sin_family = AF_INET;
	bind_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // INADDR_ANY: choose the local address of this computer
	bind_addr.sin_port = htons(0);	// 0: let OS select the next available port on which
									// the UDP sock listens for incoming response						

	if (bind(sock, (struct sockaddr*) &bind_addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		printf("Bind failed with %d\n", WSAGetLastError());
		exit(-1);
	}

	// then sendto and recvfrom
	return sock;
}

//returns 1 for connect, 0 for fail
bool Winsock::send_to(SOCKET sock, char* send_buf, int count, const char* host_address, const char* port) {
	SOCKADDR_IN server;
	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = inet_addr(host_address);
	server.sin_port = htons(atoi(port));

	if (sendto(sock, send_buf, count, 0, (SOCKADDR*)&server, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("Fail to send to server with error = %d.\n", WSAGetLastError());
		return false;
	}
	return true;
}

