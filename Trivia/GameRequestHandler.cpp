#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory* m_RequestHandlerFactory, LoggedUser* m_LoggedUser, Room* room, Game* game)
{
	this->m_RequestHandlerFactory = m_RequestHandlerFactory;
	this->m_LoggedUser = m_LoggedUser;
	this->m_game = game;
	this->m_room = room;
	this->m_GameManager = m_RequestHandlerFactory->getGameManager();
}

bool GameRequestHandler::isRequestRelevent(requestInfo info)
{
	return false;
}

IRequestHandler::requestResult GameRequestHandler::handleRequest(requestInfo info)
{
	requestResult res;
	switch (info.code)
	{
	case LeaveGameCode:
		res = this->leaveGame(info);
		break;
	case GetQuestionCode:
		res = this->getQuestion(info);
		break;
	case SubmitAnswerCode:
		res = this->submitAnswer(info);
		break;
	case GetGameResultCode:
		res = this->getGameResults(info);
		break;
	case logoutCode:
		res = this->signout(info);
		break;
	default:
		break;
	}
	return res;
}

IRequestHandler::requestResult GameRequestHandler::getQuestion(requestInfo info)
{
	requestResult res;
	JsonResponsePacketSerializer::GetQuestionResponse resp;
	if ((this->m_room->getData().questionsCount) == this->m_game->getGameData(*this->m_LoggedUser).questionCount) {
		resp.status = noMoreQuestions;
		resp.question = "PLACEHOLDER";
		resp.answers;
		res.response = this->serializer->serializeGetQuestionResponse(resp);
		res.newHandler = this;
		return res;
	}
	Question q = this->m_game->getQuestionForUser(*this->m_LoggedUser);
	resp.answers = q.getPossibleAnswers();
	resp.question = q.getQuestion();
	resp.status = success;
	res.newHandler = this;
	res.response = this->serializer->serializeGetQuestionResponse(resp);
	return res;
}

IRequestHandler::requestResult GameRequestHandler::submitAnswer(requestInfo info)
{
	requestResult res;
	JsonRequestPacketDeserializer::SubmitAnswerRequest req;
	JsonResponsePacketSerializer::SubmitAnswerResponse resp;
	req = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
	this->m_game->submitAnswer(*this->m_LoggedUser, req.answerID);
	resp.correctAnswerID = 3;
	resp.status = success;
	res.response = this->serializer->serializeSubmitAnswerResponse(resp);
	res.newHandler = this;
	return res;
}

IRequestHandler::requestResult GameRequestHandler::getGameResults(requestInfo info)
{
	requestResult res;
	JsonResponsePacketSerializer::GetGameResultsResponse resp;
	resp.status = success;
	//map<LoggedUser, Game::GameData>::iterator it;
	for (auto it = this->m_game->getPlayersData().begin(); it != this->m_game->getPlayersData().end(); it++) {
		if (it->second.questionCount != (this->m_room->getData().questionsCount)) {
			resp.status = gameNotFinished;
		}
		else {
			resp.results.push_back(JsonResponsePacketSerializer::PlayerResults(it->first, it->second.correctAnswerCount, it->second.wrongAnswerCount));
		}
	}
	res.response = this->serializer->serializeGetGameResultsResponse(resp);
	res.newHandler = this;
	return res;
}

IRequestHandler::requestResult GameRequestHandler::leaveGame(requestInfo info)
{
	requestResult res;
	JsonResponsePacketSerializer::LeaveGameResponse resp;
	for (int i = this->m_game->getGameData(*this->m_LoggedUser).questionCount; i < this->m_room->getData().questionsCount; i++) {
		this->m_game->submitAnswer(*this->m_LoggedUser, 7);
	}
	this->m_RequestHandlerFactory->getRoomManager()->removeUser(this->m_room->getData().id, *(this->m_LoggedUser));
	resp.status = success;
	res.response = this->serializer->serializeLeaveGameResponse(resp);
	res.newHandler = this->m_RequestHandlerFactory->createMenuRequestHandler(this->m_RequestHandlerFactory, this->m_LoggedUser);
	return res;
}

IRequestHandler::requestResult GameRequestHandler::signout(requestInfo info)
{
	JsonResponsePacketSerializer::LogoutResponse resp;
	requestResult res;
	int code = this->m_RequestHandlerFactory->getLoginManager()->logout(this->m_LoggedUser->getName());
	resp.status = code;
	if (resp.status == success)
	{
		res.newHandler = this->m_RequestHandlerFactory->createLoginRequestHandler(this->m_RequestHandlerFactory);
	}
	vector<unsigned char> buffer = this->serializer->serializeLogoutResponse(resp);
	res.response = buffer;
	return res;
}
