#include "GameManager.h"



GameManager::GameManager(IDataBase* db)
{
	this->db = db;
}

Game* GameManager::getLastGame()
{
	return this->games.at(this->games.size()-1);
}

Game* GameManager::createGame(Room room)
{
	Game* g = new Game(room.getAllUsers(), this->db->getQuestions());
	this->games.push_back(g);
	return g;
}

void GameManager::deleteGame(Game* game)
{
	this->games.erase(remove(this->games.begin(), this->games.end(), game), this->games.end());
	delete game;
}
