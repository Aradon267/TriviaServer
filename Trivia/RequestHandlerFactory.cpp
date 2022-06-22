#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler(RequestHandlerFactory* handler)
{
    LoginRequestHandler* logHandler = new LoginRequestHandler(handler);
    return logHandler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser)
{
    return new MenuRequestHandler(m_RequestHandlerFactory, m_LoggedUser);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser, Room* m_room)
{
    RoomMemberRequestHandler* handler = new RoomMemberRequestHandler(m_RequestHandlerFactory, m_LoggedUser, m_room);
    return handler;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser, Room* m_room)
{
    RoomAdminRequestHandler* handler = new RoomAdminRequestHandler(m_RequestHandlerFactory, m_LoggedUser, m_room);
    return handler;
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(RequestHandlerFactory* handler, LoggedUser* user, Room* room, Game* game)
{
    return new GameRequestHandler(handler, user, room, game);
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
    if (this->m_loginManager == nullptr)
    {
        this->m_loginManager = new LoginManager();
    }
    return this->m_loginManager;
}

StatisticsManager* RequestHandlerFactory::getStatisticsManager()
{
    if (this->m_StatisticsManager == nullptr)
    {
        this->m_StatisticsManager = new StatisticsManager();
    }
    return this->m_StatisticsManager;
}

RoomManager* RequestHandlerFactory::getRoomManager()
{
    if (this->m_RoomManager == nullptr)
    {
        this->m_RoomManager = new RoomManager();
    }
    return this->m_RoomManager;
}

GameManager* RequestHandlerFactory::getGameManager()
{
    if (this->m_GameManager == nullptr)
    {
        this->m_GameManager = new GameManager(new SqliteDataBase());
    }
    return this->m_GameManager;
}
