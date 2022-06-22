#pragma once
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <thread>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Helper.h"
#include "requestsCodes.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

using namespace std;

class Communicator
{
public:
	void startHandleRequests();
	void setSocket(SOCKET sock);
private:
	RequestHandlerFactory m_handlerFactory;
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET sock);
};