#include "Game.h"

Game::GameData::GameData(){
}

Game::GameData::GameData(Question q, unsigned int correct, unsigned int wrong, unsigned int count)
{
	this->current = q;
	this->correctAnswerCount = correct;
	this->questionCount = count;
	this->wrongAnswerCount = wrong;
}


Game::Game(vector<string> users, vector<Question> questions)
{
	GameData data = { questions[0],0,0,0 };
	for (int i = 0; i < users.size(); i++) {
		this->players.insert(std::pair<LoggedUser, GameData>(LoggedUser(users[i]), data));
	}
	for (int i = 0; i < questions.size(); i++) {
		this->questions.push_back(questions[i]);
	}
}

Question Game::getQuestionForUser(LoggedUser user)
{
	Question q = Question(this->questions[this->players[user].questionCount]);
	this->players[user].current = q;
	this->players[user].questionCount++;
	return q;
}

void Game::submitAnswer(LoggedUser user, unsigned int answerID)
{
	if (answerID == 3) {
		this->players[user].correctAnswerCount++;
	}
	else {
		this->players[user].wrongAnswerCount++;
	}
}

Game::GameData Game::getGameData(LoggedUser user)
{
	return this->players.at(user);
}

//map<LoggedUser, Game::GameData> Game::getPlayersData()
//{
//	return this->players;
//}

const map<LoggedUser, Game::GameData>& Game::getPlayersData() const
{
	return this->players;
}