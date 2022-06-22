#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "requestsCodes.h"
#include "LoggedUser.h"
#include "Game.h"
#include "GameManager.h"
using namespace std;


class RequestHandlerFactory;
class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser, Room* room, Game* game);
	virtual bool isRequestRelevent(requestInfo info);
	virtual requestResult handleRequest(requestInfo info);
private:
	LoggedUser* m_LoggedUser;
	Room* m_room;
	Game* m_game;
	GameManager* m_GameManager;
	RequestHandlerFactory* m_RequestHandlerFactory;
	requestResult getQuestion(requestInfo info);
	requestResult submitAnswer(requestInfo info);
	requestResult getGameResults(requestInfo info);
	requestResult leaveGame(requestInfo info);
	requestResult signout(requestInfo info);

};

