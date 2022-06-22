#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser, Room* m_room)
{
	this->m_room = m_room;
	this->m_handlerFactory = m_RequestHandlerFactory;
	this->m_user = m_LoggedUser;
	this->m_RoomManager = m_RequestHandlerFactory->getRoomManager();

}

bool RoomMemberRequestHandler::isRequestRelevent(requestInfo info)
{
	if (info.code == LeaveRoomCode || info.code == GetRoomStateCode)
	{
		return true;
	}
	return false;
}

IRequestHandler::requestResult RoomMemberRequestHandler::handleRequest(requestInfo info)
{
	requestResult res;
	switch (info.code)
	{
	case LeaveRoomCode:
		res = this->leaveRoom(info);
		break;
	case GetRoomStateCode:
		res = this->getRoomState(info);
		break;
	case GetPlayersInRoomRequestCode:
		res = this->getPlayersInRoom(info);
		break;
	case logoutCode:
		res = this->signout(info);
		break;
	default:
		break;
	}
	return res;
}

Room* RoomMemberRequestHandler::getRoom()
{
	return this->m_room;
}

IRequestHandler::requestResult RoomMemberRequestHandler::leaveRoom(requestInfo info)
{
	requestResult res;
	JsonResponsePacketSerializer::LeaveRoomResponse resp;
	this->m_RoomManager->removeUser(this->m_room->getData().id, *(this->m_user));
	resp.status = success;
	res.response = this->serializer->serializeLeaveRoomResponse(resp);
	res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);
	return res;
}

IRequestHandler::requestResult RoomMemberRequestHandler::getPlayersInRoom(requestInfo info)
{
	JsonResponsePacketSerializer::GetPlayersInRoomResponse resp;
	requestResult res;
	JsonRequestPacketDeserializer::GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(info.buffer);
	map<int, Room> rooms = this->m_RoomManager->getRoomsMap();
	if (rooms.find(req.room_id) == rooms.end()) {
		resp.status = noRoomFound;
		resp.players = rooms[req.room_id].getAllUsers();
		res.response = this->serializer->serializeGetPlayersInRoomResponse(resp);
		res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);
		return res;
	}
	resp.status = success;
	resp.players = rooms[req.room_id].getAllUsers();
	res.response = this->serializer->serializeGetPlayersInRoomResponse(resp);
	res.newHandler = this;
	return res;
}

IRequestHandler::requestResult RoomMemberRequestHandler::getRoomState(requestInfo info)
{
	requestResult res;
	JsonResponsePacketSerializer::GetRoomStateResponse resp;
	map<int, Room> rooms = this->m_RoomManager->getRoomsMap();
	if (rooms.find(this->m_room->getData().id) == rooms.end()) {
		resp.status = noRoomFound;
		//Room::GetRoomStateResponse temp = this->m_RoomManager->getRoomState(this->m_room->getData().id);
		resp.answerTimeout = noRoomFound;
		resp.hasGameBegun = false;
		resp.players;
		resp.questionCount = noRoomFound;
		res.response = this->serializer->serializeGetRoomStateResponse(resp);
		res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, this->m_user);
		return res;
	}
	Room::GetRoomStateResponse temp = this->m_RoomManager->getRoomState(this->m_room->getData().id);
	if (temp.hasGameBegun) {
		resp.status = gameStarted;
		resp.answerTimeout = temp.answerTimeout;
		resp.hasGameBegun = temp.hasGameBegun;
		resp.players = temp.players;
		resp.questionCount = temp.questionCount;
		res.response = this->serializer->serializeGetRoomStateResponse(resp);
		res.newHandler = this->m_handlerFactory->createGameRequestHandler(this->m_handlerFactory, this->m_user, this->m_room, this->m_handlerFactory->getGameManager()->getLastGame());
		return res;
	}
	resp.answerTimeout = temp.answerTimeout;
	resp.hasGameBegun = temp.hasGameBegun;
	resp.players = temp.players;
	resp.questionCount = temp.questionCount;
	resp.status = temp.status;
	res.response = this->serializer->serializeGetRoomStateResponse(resp);
	res.newHandler = this;
	return res;
}

IRequestHandler::requestResult RoomMemberRequestHandler::signout(requestInfo info)
{
	JsonResponsePacketSerializer::LogoutResponse resp;
	requestResult res;
	int code = this->m_handlerFactory->getLoginManager()->logout(this->m_user->getName());
	resp.status = code;
	if (resp.status == success)
	{
		res.newHandler = this->m_handlerFactory->createLoginRequestHandler(this->m_handlerFactory);
	}
	vector<unsigned char> buffer = this->serializer->serializeLogoutResponse(resp);
	res.response = buffer;
	return res;
}
