#include "Room.h"

Room::RoomData::RoomData()
{
}

Room::RoomData::RoomData(unsigned int id, string name, unsigned int maxPlayers, unsigned int timePerQuestion, bool isActive, unsigned int questionsCount)
{
	this->id = id;
	this->name = name;
	this->maxPlayers = maxPlayers;
	this->timePerQuestion = timePerQuestion;
	this->isActive = isActive;
	this->questionsCount = questionsCount;
}

Room::Room()
{

}

Room::Room(RoomData data)
{
	this->m_metadata = data;
}

void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	vector<LoggedUser>::iterator it = this->m_users.begin();
	for (; it != this->m_users.end(); )
	{
		if ((*it)==user) 
		{
			it = this->m_users.erase(it);
		}
		else 
		{
			++it;
		}
	}
}

vector<string> Room::getAllUsers()
{
	vector<string> retUsers;
	for (LoggedUser user : this->m_users)
	{
		retUsers.push_back(user.getName());
	}
	return retUsers;
}

Room::RoomData Room::getData()
{
	return this->m_metadata;
}

Room::GetRoomStateResponse Room::getRoomState()
{
	Room::GetRoomStateResponse resp;
	vector<string> players;
	for (LoggedUser user : this->m_users)
	{
		players.push_back(user.getName());
	}
	resp.players = players;
	resp.answerTimeout = this->m_metadata.timePerQuestion;
	resp.hasGameBegun = this->m_metadata.isActive;
	resp.status = 1;
	resp.questionCount = this->m_metadata.questionsCount;
	return resp;
}

void Room::startGame()
{
	this->m_metadata.isActive = true;
}

