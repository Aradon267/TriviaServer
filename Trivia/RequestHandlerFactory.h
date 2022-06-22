#pragma once

#include "LoginManager.h"
#include "IDataBase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"
#include "GameManager.h"

class MenuRequestHandler;
class LoginRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class GameRequestHandler;
class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler(RequestHandlerFactory* handler);
	MenuRequestHandler* createMenuRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(RequestHandlerFactory* handler, LoggedUser* user, Room* room);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(RequestHandlerFactory* handler, LoggedUser* user, Room* room);
	GameRequestHandler* createGameRequestHandler(RequestHandlerFactory* handler, LoggedUser* user, Room* room, Game* game);
	LoginManager* getLoginManager();
	StatisticsManager* getStatisticsManager();
	RoomManager* getRoomManager();
	GameManager* getGameManager();

	
private:
	StatisticsManager* m_StatisticsManager;
	GameManager* m_GameManager;
	RoomManager* m_RoomManager;
	LoginManager* m_loginManager;
	IDataBase* m_database;
};