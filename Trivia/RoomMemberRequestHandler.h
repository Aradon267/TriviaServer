#pragma once
#include "IRequestHandler.h"
#include "requestsCodes.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "Room.h"


class RequestHandlerFactory;
class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser, Room* m_room);
	virtual bool isRequestRelevent(requestInfo info);
	virtual requestResult handleRequest(requestInfo info);
	Room* getRoom();
private:

	RequestHandlerFactory* m_handlerFactory;
	LoggedUser* m_user;
	Room* m_room;
	RoomManager* m_RoomManager;

	requestResult getPlayersInRoom(requestInfo info);
	requestResult leaveRoom(requestInfo info);
	requestResult getRoomState(requestInfo info);
	requestResult signout(requestInfo info);
};