#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include "json.hpp"
#include "Room.h"
#include "requestsCodes.h"
using nlohmann::json;
using namespace std;

class JsonResponsePacketSerializer
{
public:
	struct ErrorResponse
	{
		string message;
	};
	struct LoginResponse
	{
		unsigned int status;
	};
	struct SignupResponse
	{
		unsigned int status;
	};

	struct LogoutResponse
	{
		unsigned int status;
	};
	struct GetRoomsResponse
	{
		unsigned int status;
		vector<Room::RoomData> rooms;
	};
	struct GetPlayersInRoomResponse
	{
		unsigned int status;
		vector<string> players;
	};
	struct JoinRoomResponse
	{
		unsigned int room_id;
		unsigned int status;
	};
	struct CreateRoomResponse
	{
		unsigned int room_id;
		unsigned int status;
	};
	struct GetHighScoreResponse
	{
		unsigned int status;
		vector<string> statistics;
	};
	struct GetPersonalStatsResponse
	{
		unsigned int status;
		vector<string> statistics;
	};
	struct AddQuestionResponse
	{
		unsigned int status;
	};
	struct LeaveRoomResponse
	{
		unsigned int status;
	};
	struct GetRoomStateResponse
	{
		unsigned int status;
		bool hasGameBegun;
		vector<string> players;
		unsigned int questionCount;
		unsigned int answerTimeout;
	};
	struct CloseRoomResponse
	{
		unsigned int status;
	};
	struct StartGameResponse
	{
		unsigned int status;
	};
	struct LeaveGameResponse
	{
		unsigned int status;
	};
	struct GetQuestionResponse
	{
		unsigned int status;
		string question;
		map<string, string> answers;
	};
	struct SubmitAnswerResponse
	{
		unsigned int status;
		unsigned int correctAnswerID;
	};

	struct PlayerResults {
		PlayerResults(LoggedUser name, unsigned int correct, unsigned int wrong);
		string username;
		unsigned int correctAnswerCount;
		unsigned int wrongAnswerCount;
	};

	struct GetGameResultsResponse
	{
		unsigned int status;
		vector<PlayerResults> results;
	};
	
	vector<unsigned char> serializeErrorResponse(ErrorResponse err);
	vector<unsigned char> serializeLoginResponse(LoginResponse log);
	vector<unsigned char> serializeSignupResponse(SignupResponse log);
	vector<unsigned char> serializeLogoutResponse(LogoutResponse logout);
	vector<unsigned char> serializeGetRoomsResponse(GetRoomsResponse getRooms);
	vector<unsigned char> serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse getPlayers);
	vector<unsigned char> serializeJoinRoomResponse(JoinRoomResponse joinRoom);
	vector<unsigned char> serializeCreateRoomResponse(CreateRoomResponse createRoom);
	vector<unsigned char> serializeGetHighScoreResponse(GetHighScoreResponse highScore);
	vector<unsigned char> serializeGetPersonalScoreResponse(GetPersonalStatsResponse personalScore);
	vector<unsigned char> serializeLeaveRoomResponse(LeaveRoomResponse leaveRoom);
	vector<unsigned char> serializeGetRoomStateResponse(GetRoomStateResponse roomState);
	vector<unsigned char> serializeCloseRoomResponse(CloseRoomResponse closeRoom);
	vector<unsigned char> serializeStartGameResponse(StartGameResponse startGame);
	vector<unsigned char> serializeLeaveGameResponse(LeaveGameResponse leaveGame);
	vector<unsigned char> serializeGetQuestionResponse(GetQuestionResponse question);
	vector<unsigned char> serializeSubmitAnswerResponse(SubmitAnswerResponse submit);
	vector<unsigned char> serializeGetGameResultsResponse(GetGameResultsResponse results);

	vector<unsigned char> serializeAddQuestion(AddQuestionResponse addQuestion);

	vector<unsigned char> buildMsg(json messageData, int code);

	void to_json_room(json& j, const Room::RoomData& p);
	void to_json_results(json& j, const PlayerResults& p);
};
