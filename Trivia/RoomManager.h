#pragma once
#include <map>
#include "Room.h"
#include "LoggedUser.h"
#include "responseCodes.h"
#include "JsonResponsePacketSerializer.h"
using namespace std;
class JsonResponsePacketSerializer;
class RoomManager
{
public:
	struct GetRoomStateResponse
	{
		unsigned int status;
		bool hasGameBegun;
		vector<string> players;
		unsigned int questionCount;
		unsigned int answerTimeout;
	};
	RoomManager();
	void createRoom(LoggedUser user, Room room);
	void deleteRoom(int id);
	int addUser(int id, LoggedUser user);
	void removeUser(int id, LoggedUser user);
	void startGame(int id);
	Room::GetRoomStateResponse getRoomState(int id);
	vector<Room::RoomData> getRooms();
	map<int, Room> getRoomsMap();
private:
	map<int, Room> m_rooms;
};