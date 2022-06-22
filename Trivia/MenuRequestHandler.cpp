#include "MenuRequestHandler.h"

unsigned int MenuRequestHandler::roomId = 0;

unsigned int MenuRequestHandler::getRoomId()
{
	return MenuRequestHandler::roomId;
}

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser)
{
	this->m_RequestHandlerFactory = m_RequestHandlerFactory;
	this->m_LoggedUser = m_LoggedUser;
	this->m_LoginManager = m_RequestHandlerFactory->getLoginManager();
	this->m_RoomManager = m_RequestHandlerFactory->getRoomManager();
	this->m_StatisticsManager = m_RequestHandlerFactory->getStatisticsManager();
}

bool MenuRequestHandler::isRequestRelevent(requestInfo info)
{
	if ((info.code >= CreateRoomRequestCode && info.code <= GetPersonalStatsCode) || info.code == logoutCode)
	{
		return true;
	}
	return false;
}

IRequestHandler::requestResult MenuRequestHandler::handleRequest(requestInfo info)
{
	requestResult res;

	switch (info.code)
	{
	case CreateRoomRequestCode:
		res = this->createRoom(info);
		break;

	case GetRoomsRequestCode:
		res = this->getRooms(info);
		break;

	case GetPlayersInRoomRequestCode:
		res = this->getPlayersInRoom(info);
		break;

	case JoinRoomRequestCode:
		res = this->joinRoom(info);
		break;

	case GetStatisticsRequestCode:
		res = this->getHighScore(info);
		break;

	case logoutCode:
		res = this->signout(info);
		break;
		
	case GetPersonalStatsCode:
		res = this->getPersonalStats(info);
		break;

	case AddQuestionCode:
		res = this->addQuestion(info);
		break;

	default:
		break;
	}
	return res;
}

IRequestHandler::requestResult MenuRequestHandler::createRoom(requestInfo info)
{
	JsonResponsePacketSerializer::CreateRoomResponse resp;
	requestResult res;
	JsonRequestPacketDeserializer::CreateRoomRequest req = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
	unsigned int id = this->getRoomId();
	this->roomId++;
	Room::RoomData data = {id,req.room_name,req.max_users,req.answer_timeout,false,req.question_count};
	Room* room = new Room(data);
	this->m_RoomManager->createRoom(*this->m_LoggedUser, *room);
	this->m_RoomManager->addUser(id, *this->m_LoggedUser);
	resp.room_id = id;
	resp.status = success;
	res.response = this->serializer->serializeCreateRoomResponse(resp);
	res.newHandler = this->m_RequestHandlerFactory->createRoomAdminRequestHandler(this->m_RequestHandlerFactory,this->m_LoggedUser,room);
	return res;
}

IRequestHandler::requestResult MenuRequestHandler::getRooms(requestInfo info)
{
	JsonResponsePacketSerializer::GetRoomsResponse resp;
	requestResult res;
	resp.rooms = this->m_RoomManager->getRooms();
	resp.status = success;
	if (resp.rooms.size() == 0)
	{
		resp.status = noRooms;
	}
	res.newHandler = this;
	res.response = this->serializer->serializeGetRoomsResponse(resp);
	return res;
}

IRequestHandler::requestResult MenuRequestHandler::getPlayersInRoom(requestInfo info)
{
	JsonResponsePacketSerializer::GetPlayersInRoomResponse resp;
	requestResult res;
	JsonRequestPacketDeserializer::GetPlayersInRoomRequest req = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(info.buffer);
	map<int, Room> rooms = this->m_RoomManager->getRoomsMap();
	resp.players = rooms[req.room_id].getAllUsers();
	res.response = this->serializer->serializeGetPlayersInRoomResponse(resp);
	res.newHandler = this;
	return res;
}

IRequestHandler::requestResult MenuRequestHandler::getPersonalStats(requestInfo info)
{
	JsonResponsePacketSerializer::GetPersonalStatsResponse resp;
	requestResult res;
	vector<string> stats = this->m_StatisticsManager->getUserStatistics(this->m_LoggedUser->getName());
	resp.statistics = stats;
	resp.status = success;
	res.newHandler = this;
	res.response = this->serializer->serializeGetPersonalScoreResponse(resp);
	return res;
}

IRequestHandler::requestResult MenuRequestHandler::getHighScore(requestInfo info)
{
	JsonResponsePacketSerializer::GetHighScoreResponse resp;
	requestResult res;
	vector<string> stats = this->m_StatisticsManager->getHighScore(this->m_LoggedUser->getName());
	resp.statistics = stats;
	resp.status = success;
	res.newHandler = this;
	res.response = this->serializer->serializeGetHighScoreResponse(resp);
	return res;
}

IRequestHandler::requestResult MenuRequestHandler::joinRoom(requestInfo info)
{
	JsonResponsePacketSerializer::JoinRoomResponse resp;
	requestResult res;
	JsonRequestPacketDeserializer::JoinRoomRequest req = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
	resp.status = this->m_RoomManager->addUser(req.room_id, *(this->m_LoggedUser));
	if (resp.status == success) {
		resp.room_id = req.room_id;
		res.response = this->serializer->serializeJoinRoomResponse(resp);
		vector<Room::RoomData> rooms = this->m_RoomManager->getRooms();
		Room* room = new Room();
		for (Room::RoomData& r : rooms)
		{
			if (r.id == req.room_id)
			{
				*room = r;
			}
		}
		res.newHandler = this->m_RequestHandlerFactory->createRoomMemberRequestHandler(this->m_RequestHandlerFactory, this->m_LoggedUser, room);
		return res;
	}
	else {
		resp.room_id = req.room_id;
		res.response = this->serializer->serializeJoinRoomResponse(resp);
		res.newHandler = this;
		return res;
	}
}

IRequestHandler::requestResult MenuRequestHandler::signout(requestInfo info)
{
	JsonResponsePacketSerializer::LogoutResponse resp;
	requestResult res;
	int code = this->m_LoginManager->logout(this->m_LoggedUser->getName());
	resp.status = code;
	if (resp.status == success)
	{
		res.newHandler = this->m_RequestHandlerFactory->createLoginRequestHandler(this->m_RequestHandlerFactory);
	}
	vector<unsigned char> buffer = this->serializer->serializeLogoutResponse(resp);
	res.response = buffer;
	return res;
}

IRequestHandler::requestResult MenuRequestHandler::addQuestion(requestInfo info)
{
	JsonResponsePacketSerializer::AddQuestionResponse resp;
	requestResult res;
	JsonRequestPacketDeserializer::AddQuestionRequest req = JsonRequestPacketDeserializer::deserializeAddQuestionRequest(info.buffer);
	IDataBase* hold = this->m_LoginManager->getDataBase();
	hold->addNewQuestion(req.question, req.ans1, req.ans2, req.ans3, req.correct);
	resp.status = success;
	res.newHandler = this;
	res.response = this->serializer->serializeAddQuestion(resp);
	return res;
}
