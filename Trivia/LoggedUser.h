#pragma once
#include <iostream>
using namespace std;
class LoggedUser
{
private:
	string name;
public:
	LoggedUser(string _name);
	string getName();
	bool operator==(const LoggedUser& other) const;
	bool operator<(const LoggedUser& other) const;
};