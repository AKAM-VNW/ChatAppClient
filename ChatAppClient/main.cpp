#include <iostream>
#include <thread>
#include "ClientIOServer.hpp"

int main()
{
	ClientIOServer cios("127.0.0.1", 54000);
	std::thread getServerMsg(&ClientIOServer::listenOnRecv, cios);
	cios.clientIO();
}