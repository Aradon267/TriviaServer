#pragma once
#include "IRequestHandler.h"
#include "requestsCodes.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "Room.h"

class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser);
	virtual bool isRequestRelevent(requestInfo info);
	virtual requestResult handleRequest(requestInfo info);
	unsigned int getRoomId();

private:
	LoginManager* m_LoginManager;
	RoomManager* m_RoomManager;
	StatisticsManager* m_StatisticsManager;
	LoggedUser* m_LoggedUser;
	RequestHandlerFactory* m_RequestHandlerFactory;
	static unsigned int roomId;

	requestResult createRoom(requestInfo info);
	requestResult getRooms(requestInfo info);
	requestResult getPlayersInRoom(requestInfo info);
	requestResult getPersonalStats(requestInfo info);
	requestResult getHighScore(requestInfo info);
	requestResult joinRoom(requestInfo info);
	requestResult signout(requestInfo info);
	requestResult addQuestion(requestInfo info);

};

