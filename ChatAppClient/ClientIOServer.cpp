#include "ClientIOServer.hpp"

ClientIOServer::ClientIOServer(std::string ipAddr, int port) {
	if (WSAStartup(MAKEWORD(2, 2), &wsData)) {
		std::cerr << "Can't initialise winsock" << std::endl;
		_error = true;
	}
	else {
		//Client socket
		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "Can't create client socket" << std::endl;
			_error = true;
		}
		else {
			//Init client vars
			_ipAddr = ipAddr;
			_port = port;
			//Server address
			serverAddr;
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(port);
			inet_pton(AF_INET, ipAddr.c_str(), &serverAddr.sin_addr);

			if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
				std::cerr << "Can't connect with server" << std::endl;
				_error = true;
				closesocket(clientSocket);
			}
		}
	}
}
ClientIOServer::~ClientIOServer() {}
void ClientIOServer::listenOnRecv() {
	while (!_error) {
		char buf[BUFSIZE];
		SecureZeroMemory(buf, BUFSIZE);

		int bytesRecv = recv(clientSocket, buf, BUFSIZE, 0);

		if (bytesRecv <= 0) {
			std::cout << "Server is out of service" << std::endl;
			return;
		}
		else {
			std::string bufStr(buf);
			bufStr.erase(std::remove(bufStr.begin(), bufStr.end(), '\r'), bufStr.end());
			bufStr.erase(std::remove(bufStr.begin(), bufStr.end(), '\n'), bufStr.end());
			std::cout << bufStr << std::endl;
		}
	}
	closesocket(clientSocket);
	WSACleanup();
}
void ClientIOServer::clientIO() {
	std::string msg = "";
	while (true) {
		std::getline(std::cin, msg);
		send(clientSocket, msg.c_str(), msg.length(), 0);
	}

	closesocket(clientSocket);
	WSACleanup();
}