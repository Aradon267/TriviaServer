#pragma once
#include "IDataBase.h"
#include <map>
#include "Game.h"
#include <vector>
#include "Room.h"
using namespace std;

class GameManager
{
public:
	GameManager(IDataBase* db);
	Game* getLastGame();
	Game* createGame(Room room);
	void deleteGame(Game* game);
private:
	IDataBase* db;
	vector<Game*> games;
};

