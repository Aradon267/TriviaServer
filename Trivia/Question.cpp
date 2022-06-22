#include "Question.h"

Question::Question(string question, vector<string> answers)
{
	this->question = question;
	this->possibleAnswers = answers;
}

Question::Question()
{
}

string Question::getQuestion()
{
	return this->question;
}

map<string, string> Question::getPossibleAnswers()
{
	map<string, string> answers;
	for (int i = 0; i < this->possibleAnswers.size(); i++) {
		answers.insert(std::pair<string, string>(to_string(i), this->possibleAnswers[i]));
	}
	return answers;
}

string Question::getCorrectAnswer()
{
	return this->possibleAnswers[3];
}
