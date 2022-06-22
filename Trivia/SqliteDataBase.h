#pragma once
#include "IDataBase.h"
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <io.h>
#include <typeinfo>
#include <vector>

class SqliteDataBase :public IDataBase
{
public:
	SqliteDataBase();
	virtual bool doesUserExists(string name);
	virtual bool doesPasswordMatch(string password, string name);
	virtual void addNewUser(string name, string password, string email, string phone, string addr);
	virtual void addNewQuestion(string question, string answer1, string answer2, string answer3, string correct);
	virtual float getPlayerAverageAnswerTime(string name);
	virtual int getNumOfCorrectAnswers(string name);
	virtual int getNumOfTotalAnswers(string name);
	virtual int getNumOfPlayerGames(string name);
	virtual string getHighScore(string name);
	virtual vector<Question> getQuestions();

private:
	sqlite3* db;
};

int NumberCallBack(void* data, int argc, char** argv, char** azColName);
int countCallBack(void* data, int argc, char** argv, char** azColName);
int ScoreCallBack(void* data, int argc, char** argv, char** azColName);
int QuestionsCallBack(void* data, int argc, char** argv, char** azColName);