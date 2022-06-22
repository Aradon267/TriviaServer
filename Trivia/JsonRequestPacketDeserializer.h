#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

class JsonRequestPacketDeserializer
{
public:

	typedef struct LoginRequest
	{
		string username;
		string password;
	}LoginRequest;

	typedef struct SignupRequest
	{
		string username;
		string password;
		string email;
		string phone;
		string addr;
	}SignupRequest;

	typedef struct GetPlayersInRoomRequest
	{
		unsigned int room_id;
	}GetPlayersInRoomRequest;

	typedef struct JoinRoomRequest
	{
		unsigned int room_id;
	}JoinRoomRequest;

	typedef struct CreateRoomRequest
	{
		string room_name;
		unsigned int max_users;
		unsigned int question_count;
		unsigned int answer_timeout;
	}CreateRoomRequest;

	typedef struct SubmitAnswerRequest
	{
		unsigned int answerID;
	}SubmitAnswerRequest;

	typedef struct AddQuestionRequest
	{
		string question;
		string correct;
		string ans1;
		string ans2;
		string ans3;
	}AddQuestionRequest;

	static LoginRequest deserializeLoginRequest(const char* log);
	static SignupRequest deserializeSignupRequest(const char* sign);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const char* sign);
	static JoinRoomRequest deserializeJoinRoomRequest(const char* sign);
	static CreateRoomRequest deserializeCreateRoomRequest(const char* sign);
	static AddQuestionRequest deserializeAddQuestionRequest(const char* add);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const char* submit);
};
