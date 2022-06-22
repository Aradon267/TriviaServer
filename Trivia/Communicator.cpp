#include "Communicator.h"

void Communicator::startHandleRequests()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	IRequestHandler* newLog = m_handlerFactory.createLoginRequestHandler(&m_handlerFactory);
	this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, newLog));
	// the function that handle the conversation with the client
	std::thread t2(&Communicator::handleNewClient, this, client_socket);
	t2.detach();
}

void Communicator::setSocket(SOCKET sock)
{
	this->m_serverSocket = sock;
}

void Communicator::handleNewClient(SOCKET sock)
{
	IRequestHandler::requestInfo req;
	try
	{
		JsonResponsePacketSerializer* serializer = new JsonResponsePacketSerializer();
		bool dissconnected = false;
		while (true && !dissconnected)
		{
			IRequestHandler::requestResult res;
			int code = Helper::getMessageTypeCode(sock);
			req.code = code;
			req.recieve = Helper::getDateNow();
			int size = Helper::getJsonSize(sock);
			string msg = Helper::getStringPartFromSocket(sock, size);
			req.buffer = msg.c_str();
			switch (code)
			{
			case LoginCode:
			case SignupCode:
			{
				if (m_clients.at(sock)->isRequestRelevent(req))
				{
					res = m_clients.at(sock)->handleRequest(req);
					string respMsg(res.response.begin(), res.response.end());
					Helper::sendData(sock, respMsg);
					this->m_clients[sock] = res.newHandler;
				}
				else
				{
					JsonResponsePacketSerializer::ErrorResponse err{ "Failed to login or signup" };
					vector<unsigned char> resp = serializer->serializeErrorResponse(err);
					Helper::sendData(sock, string(resp.begin(), resp.end()));
					break;
				}
				break;
			}
			case logoutCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				cout << "User logged out!" << endl;
				break;
			}
			case CreateRoomRequestCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case GetRoomsRequestCode:
			{
				if (m_clients.at(sock)->isRequestRelevent(req))
				{
					res = this->m_clients.at(sock)->handleRequest(req);
					string respMsg(res.response.begin(), res.response.end());
					Helper::sendData(sock, respMsg);
					this->m_clients[sock] = res.newHandler;
					break;
				}
				break;
			}
			case JoinRoomRequestCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case GetPlayersInRoomRequestCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case AddQuestionCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case LeaveRoomCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case GetRoomStateCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case CloseRoomCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case StartGameCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case LeaveGameCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case GetQuestionCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case SubmitAnswerCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			case GetGameResultCode:
			{
				res = this->m_clients.at(sock)->handleRequest(req);
				string respMsg(res.response.begin(), res.response.end());
				Helper::sendData(sock, respMsg);
				this->m_clients[sock] = res.newHandler;
				break;
			}
			default:
				dissconnected = true;
				break;
			}
		}
	}
	catch (const std::exception& e)//close the socket whan the client disconnct
	{
		cout << e.what() << endl;
	}
	IRequestHandler::requestResult res;
	req.code = logoutCode;
	res = this->m_clients.at(sock)->handleRequest(req);
	string respMsg(res.response.begin(), res.response.end());
	try
	{
		Helper::sendData(sock, respMsg);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	cout << "Sock removed" << endl;
	m_clients.erase(sock);
	closesocket(sock);
}
