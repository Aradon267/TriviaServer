#pragma once
#include <iostream>
#include "Question.h"

using namespace std;
class IDataBase
{
public:
	virtual bool doesUserExists(string name) = 0;
	virtual bool doesPasswordMatch(string password, string name) = 0;
	virtual void addNewUser(string name, string password, string email, string phone, string addr) = 0;
	virtual void addNewQuestion(string question, string answer1, string answer2, string answer3, string correct) = 0;
	virtual float getPlayerAverageAnswerTime(string name) = 0;
	virtual int getNumOfCorrectAnswers(string name) = 0;
	virtual int getNumOfTotalAnswers(string name) = 0;
	virtual int getNumOfPlayerGames(string name) = 0;
	virtual string getHighScore(string name) = 0;
	virtual vector<Question> getQuestions() = 0;

};