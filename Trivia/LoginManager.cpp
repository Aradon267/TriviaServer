#include "LoginManager.h"

LoginManager::LoginManager()
{
	this->m_database = new SqliteDataBase();
}

int LoginManager::signup(string name, string password, string email, string phone, string addr)
{
	bool upper_case = false;
	bool lower_case = false;
	bool number_case = false;
	bool special_char = false;
	regex upper_case_expression{ "[A-Z]+" };
	regex lower_case_expression{ "[a-z]+" };
	regex number_expression{ "[0-9]+" };
	regex special_char_expression{ "[*&^%$#@!]+" };
	if (m_database->doesUserExists(name))
	{
		return nameExsits;
	}
	if (password.length() != 8)
	{
		return badPassword;
	}
	upper_case = regex_search(password, upper_case_expression);
	lower_case = regex_search(password, lower_case_expression);
	number_case = regex_search(password, number_expression);
	special_char = regex_search(password, special_char_expression);
	int sum_of_positive_results = upper_case + lower_case + number_case + special_char;
	if (sum_of_positive_results != 4)
	{
		return badPassword;
	}
	regex emailPattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	if (regex_match(email, emailPattern) == false)
	{
		return badEmail;
	}
	regex phonePattern("((0\\d{1,2})[-](\\d{3})(\\d{4}))");
	if (regex_match(phone, phonePattern) == false)
	{
		return badPhone;
	}
	regex addrPattern("([a-zA-z]+\\s\\d+\\s[a-zA-Z]+)");
	if (regex_match(addr, addrPattern) == false)
	{
		return badAddr;
	}
	m_database->addNewUser(name, password, email, phone, addr);
	return success;
	//check date of birth regex ^([0-2][0-9]|(3)[0-1])(\/|\.)(((0)[0-9])|((1)[0-2]))(\/|\.)\d{4}$
}

int LoginManager::login(string name, string password)
{
	vector<LoggedUser>::iterator it = this->m_loggedUser.begin();

	if (m_database->doesUserExists(name))
	{
		if (m_database->doesPasswordMatch(password, name))
		{
			it = this->m_loggedUser.begin();
			for (it; it != this->m_loggedUser.end(); it++)
			{
				if (it->getName() == name)
				{
					return alreadyConnected;
				}
			}
			LoggedUser newUser = LoggedUser(name);
			m_loggedUser.push_back(newUser);
			return success;
		}
		return wrongPassword;
	}
	return invalidName;
}

int LoginManager::logout(string name)
{
	vector<LoggedUser>::iterator it = m_loggedUser.begin();
	for (it; it != m_loggedUser.end(); it++)
	{
		if (it->getName() == name)
		{
			m_loggedUser.erase(it);
			return success;
		}
	}
	return userNotConnected;
}

IDataBase* LoginManager::getDataBase()
{
	return this->m_database;
}
