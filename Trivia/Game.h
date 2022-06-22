#pragma once
#include <vector>
#include "LoggedUser.h"
#include "Question.h"
#include <map>
using namespace std;


class Game
{
public:
	typedef struct GameData {
		GameData();
		GameData(Question q, unsigned int correct, unsigned int wrong, unsigned int count);
		Question current;
		unsigned int correctAnswerCount;
		unsigned int wrongAnswerCount;
		unsigned int questionCount;
	};
	Game(vector<string> users, vector<Question> questions);
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, unsigned int answerID);
	GameData getGameData(LoggedUser user);
	const map<LoggedUser, GameData> &getPlayersData() const;
private:
	vector<Question> questions;
	map<LoggedUser, GameData> players;
};

