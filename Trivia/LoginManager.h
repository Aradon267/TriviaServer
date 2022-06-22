#pragma once
#include "IDataBase.h"
#include "SqliteDataBase.h"
#include "responseCodes.h"
#include <stdio.h>
#include <vector>
#include "LoggedUser.h"
#include <regex>
#include <algorithm>
using namespace std;

class LoginManager
{
private:
	IDataBase* m_database;
	vector<LoggedUser> m_loggedUser;
public:
	LoginManager();
	int signup(string name, string password, string email, string phone, string addr);
	int login(string name, string password);
	int logout(string name);
	IDataBase* getDataBase();

};