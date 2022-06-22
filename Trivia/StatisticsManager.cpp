#include "StatisticsManager.h"


StatisticsManager::StatisticsManager()
{
	this->m_database = new SqliteDataBase();
}

vector<string> StatisticsManager::getHighScore(string username)
{
	vector<string> scores;
	scores.push_back(this->m_database->getHighScore(username));
	return scores;
}

vector<string> StatisticsManager::getUserStatistics(string username)
{
	int answers = this->m_database->getNumOfTotalAnswers(username);
	int correct = this->m_database->getNumOfCorrectAnswers(username);
	vector<string> statistics;
	statistics.push_back(to_string((correct / answers) * 100));
	return statistics;
}

