#pragma once
#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

#define BUFSIZE 4096

class ClientIOServer
{
	WSADATA wsData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;
	bool _error = false;
	//
	std::string _ipAddr;
	int _port;

public:
	ClientIOServer(std::string ipAddr, int port);
	~ClientIOServer();
	void listenOnRecv();
	void clientIO();
};