#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()//build sql
{
	string dbFileName = "triviaDB.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &this->db);
	if (res != SQLITE_OK)
	{
		this->db = nullptr;
	}
	if (doesFileExist == 0)
	{
		try
		{
			string sqlStatement = "CREATE TABLE IF NOT EXISTS USERS(NAME TEXT NOT NULL,PASSWORD TEXT NOT NULL,EMAIL TEXT NOT NULL,PHONE TEXT NOT NULL, ADDR TEXT NOT NULL, PRIMARY KEY(NAME)); ";
			char* errMessage = nullptr;
			res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw exception("Problem creating users table");
			sqlStatement = "CREATE TABLE IF NOT EXISTS QUESTIONS(QUESTION TEXT NOT NULL,ANSWER1 TEXT NOT NULL,ANSWER2 TEXT NOT NULL,ANSWER3 TEXT NOT NULL,CORRECT TEXT NOT NULL, PRIMARY KEY(QUESTION)); ";
			errMessage = nullptr;
			res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw exception("Problem creating questions table");
			vector<vector<string>> questions{{"You're 3rd place right now in a race. What place are you in when you pass the person in 2nd place?","2nd","3rd","None","1st"},
				{"How many months have 28 days?","1","2","Depends if there's a leap year or not","All of them"},
				{"How many 0.5cm slices of bread can you cut from a whole bread that's 25cm long?","25","39","None","1"},
				{"The answer is really big.","An elephant.","Really big.","The data given is insufficient.","THE ANSWER."},
				{"Divide 30 by half and add ten.","40.5","50","Trick question so none","70"},
				{"There are two clocks of different colors: The red clock is broken and doesn't run at all, but the blue clock loses one second every 24 hours. Which clock is more accurate?","Both.","Neither.","The blue clock.","The red clock."},
				{"A farmer has 17 sheep, all of them but 8 die. How many sheep are still standing?","35","25","9","8"},
				{"If a leaf falls to the ground in a forest and no one hears it, does it make a sound?","No","Depends on how heavy the leaf was","Depends on where it landed","Yes"},
				{"There are 45 apples in your basket. You take three apples out of the basket. How many apples are left?","3","42","0","45"},
				{"Who is the best teacher?","Teacher1","Teacher2","Teacher3","Raz Tibi"}};

			vector<vector<string>>::iterator it = questions.begin();
			for (it; it != questions.end(); it++)
			{
				addNewQuestion((*it)[0], (*it)[1], (*it)[2], (*it)[3], (*it)[4]);
			}
			sqlStatement = "CREATE TABLE IF NOT EXISTS STATISTICS(NAME TEXT NOT NULL,ROOM_ID INT NOT NULL,GAMES_PLAYED INT,ANSWERS_COUNT INT,CORRECT_COUNT INT,AVG_TIME FLOAT,HIGH_SCORE TEXT, FOREIGN KEY(NAME) REFERENCES USERS(NAME));";
			errMessage = nullptr;
			res = sqlite3_exec(this->db, sqlStatement.c_str(), nullptr, nullptr, &errMessage);
			if (res != SQLITE_OK)
				throw exception("Problem creating statistics table");
		}
		catch (exception e)
		{
			cout << e.what() << endl;
		}
	}
}

bool SqliteDataBase::doesUserExists(string name)
{
	int exists = 0;
	char* errMessage = nullptr;
	string sqlStatement = "SELECT COUNT(*) FROM USERS WHERE NAME = \"" + name + "\";";
	sqlite3_exec(this->db, sqlStatement.c_str(), countCallBack, &exists, &errMessage);
	if (exists >= 1)
	{
		return true;
	}
	return false;
}

bool SqliteDataBase::doesPasswordMatch(string password, string name)
{
	int match = 0;
	char* errMessage = nullptr;
	string sqlStatement = "SELECT COUNT(*) FROM USERS WHERE NAME = \"" + name + "\" AND PASSWORD = \"" + password + "\";";
	sqlite3_exec(this->db, sqlStatement.c_str(), countCallBack, &match, &errMessage);
	if (match >= 1)
	{
		return true;
	}
	return false;
}

void SqliteDataBase::addNewUser(string name, string password, string email, string phone, string addr)
{
	string msg = "INSERT INTO USERS (NAME,PASSWORD,EMAIL,PHONE,ADDR) VALUES (\"" + name + "\",\"" + password + "\",\"" + email + "\",\"" + phone + "\",\""+ addr + "\");";
	const char* sqlStatement = msg.c_str();
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
}

void SqliteDataBase::addNewQuestion(string question, string answer1, string answer2, string answer3, string correct)
{
	string msg = "INSERT INTO QUESTIONS (QUESTION,ANSWER1,ANSWER2,ANSWER3,CORRECT) VALUES (\"" + question + "\",\"" + answer1 + "\",\"" + answer2 + "\",\"" + answer3 + "\",\"" + correct + "\");";
	const char* sqlStatement = msg.c_str();
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
}

float SqliteDataBase::getPlayerAverageAnswerTime(string name)
{
	char* errMessage = nullptr;
	float avg = 0;
	string msg = "SELECT AVG_TIME FROM STATISTICS WHERE NAME = \"" +  name + "\";";
	const char* sqlStatement = msg.c_str();
	int res = sqlite3_exec(this->db, sqlStatement, NumberCallBack, &avg, &errMessage);
	return avg;
}

int SqliteDataBase::getNumOfCorrectAnswers(string name)
{
	char* errMessage = nullptr;
	int correct = 0;
	string msg = "SELECT CORRECT_COUNT FROM STATISTICS WHERE NAME = \"" + name + "\";";
	const char* sqlStatement = msg.c_str();
	int res = sqlite3_exec(this->db, sqlStatement, NumberCallBack, &correct, &errMessage);
	return correct;
}

int SqliteDataBase::getNumOfTotalAnswers(string name)
{
	char* errMessage = nullptr;
	int total = 0;
	string msg = "SELECT ANSWERS_COUNT FROM STATISTICS WHERE NAME = \"" + name + "\";";
	const char* sqlStatement = msg.c_str();
	int res = sqlite3_exec(this->db, sqlStatement, NumberCallBack, &total, &errMessage);
	return total;
}

int SqliteDataBase::getNumOfPlayerGames(string name)
{
	char* errMessage = nullptr;
	int amount = 0;
	string msg = "SELECT GAMES_PLAYED FROM STATISTICS WHERE NAME = \"" + name + "\";";
	const char* sqlStatement = msg.c_str();
	int res = sqlite3_exec(this->db, sqlStatement, NumberCallBack, &amount, &errMessage);
	return amount;
}

string SqliteDataBase::getHighScore(string name)
{
	char* errMessage = nullptr;
	string score = 0;
	string msg = "SELECT HIGH_SCORE FROM STATISTICS WHERE NAME = \"" + name + "\";";
	const char* sqlStatement = msg.c_str();
	int res = sqlite3_exec(this->db, sqlStatement, ScoreCallBack, &score, &errMessage);
	return score;
}

vector<Question> SqliteDataBase::getQuestions()
{
	vector<Question> questions;
	char* errMessage = nullptr;
	string msg = "SELECT * FROM QUESTIONS;";
	const char* sqlStatement = msg.c_str();
	int res = sqlite3_exec(this->db, sqlStatement, QuestionsCallBack, &questions, &errMessage);
	return questions;
}


int countCallBack(void* data, int argc, char** argv, char** azColName)
{
	int* number = (int*)data;
	(*number) += stoi(string(argv[0]));
	return 0;
}


int ScoreCallBack(void* data, int argc, char** argv, char** azColName)
{
	string* score = (string*)data;
	(*score) += string(argv[0]);
	return 0;
}

int QuestionsCallBack(void* data, int argc, char** argv, char** azColName)
{
	vector<Question>* questions = reinterpret_cast<vector<Question>*>(data);
	string question;
	vector<string> answers;
	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "QUESTION") {
			question = argv[i];
		}
		else {
			answers.push_back(argv[i]);
		}
	}
	questions->emplace_back(question, answers);
	return 0;
}

int NumberCallBack(void* data, int argc, char** argv, char** azColName)
{
	float* retVal = (float*)data;
	for (int i = 0; i < argc; i++)
	{
		(*retVal) += stof(string(argv[i]));
	}
	return 0;
}