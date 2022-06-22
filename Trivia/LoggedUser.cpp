#include "LoggedUser.h"

LoggedUser::LoggedUser(string _name)
{
	this->name = _name;
}

string LoggedUser::getName()
{
	return this->name;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	if (this->name == other.name)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LoggedUser::operator<(const LoggedUser& other) const
{
	if (this->name < other.name) {
		return true;
	}
	else {
		return false;
	}
}
