#pragma once
#include "IDataBase.h"
#include "SqliteDataBase.h"
#include <vector>
#include <string>

class StatisticsManager
{
public:
	StatisticsManager();
	vector<string> getHighScore(string username);
	vector<string> getUserStatistics(string username);

private:
	IDataBase *m_database;
};


