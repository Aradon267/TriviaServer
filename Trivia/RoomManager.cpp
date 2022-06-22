#include "RoomManager.h"

RoomManager::RoomManager()
{
}

void RoomManager::createRoom(LoggedUser user, Room room)
{
	//this->m_rooms.insert(pair<int, Room>(room.getData().id, room));
	if (!this->m_rooms.insert(std::make_pair(room.getData().id, room)).second) {

	}
}

void RoomManager::deleteRoom(int id)
{
	this->m_rooms.erase(id);
}

int RoomManager::addUser(int id, LoggedUser user)
{
	if (this->m_rooms.find(id) == this->m_rooms.end()) {
		return noRoomFound;
	}
	else {
		if (this->m_rooms[id].getData().maxPlayers == this->m_rooms[id].getAllUsers().size())
		{
			return roomFull;
		}
		if (this->m_rooms[id].getData().isActive) {
			return gameStarted;
		}
		this->m_rooms[id].addUser(user);
		return success;
	}
}

void RoomManager::removeUser(int id, LoggedUser user)
{
	this->m_rooms[id].removeUser(user);
}

void RoomManager::startGame(int id)
{
	this->m_rooms.at(id).startGame();
}

Room::GetRoomStateResponse RoomManager::getRoomState(int id)
{
	return this->m_rooms.at(id).getRoomState();
}

vector<Room::RoomData> RoomManager::getRooms()
{
	vector<Room::RoomData> temp;
	for (auto room : this->m_rooms)
	{
		temp.push_back(room.second.getData());
	}
	return temp;
}

map<int, Room> RoomManager::getRoomsMap()
{
	return this->m_rooms;
}
