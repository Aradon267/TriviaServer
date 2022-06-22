#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "LoggedUser.h"
class Room 
{
public:
	typedef struct RoomData
	{
		RoomData();
		RoomData(unsigned int id, string name, unsigned int maxPlayers, unsigned int timePerQuestion, bool isActive, unsigned int questionsCount);
		unsigned int id;
		string name;
		unsigned int maxPlayers;
		unsigned int timePerQuestion;
		unsigned int questionsCount;
		bool isActive;
	}RoomData;
	struct GetRoomStateResponse
	{
		unsigned int status;
		bool hasGameBegun;
		vector<string> players;
		unsigned int questionCount;
		unsigned int answerTimeout;
	};
	Room();
	Room(RoomData data);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	vector<string> getAllUsers();
	RoomData getData();
	GetRoomStateResponse getRoomState();
	void startGame();
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};