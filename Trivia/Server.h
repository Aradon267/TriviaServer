#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <cstring>
#include <vector>
#include "Communicator.h"


class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:
	void accept();
	void clientHandler(SOCKET clientSocket);
	Communicator m_communicator;
	SOCKET _serverSocket;

};

