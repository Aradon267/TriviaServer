#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


class Question
{
public:
	Question(string question, vector<string> answers);
	Question();
	string getQuestion();
	map<string, string> getPossibleAnswers();
	string getCorrectAnswer();
private:
	string question;
	vector<string> possibleAnswers;
};

