#include "JsonResponsePacketSerializer.h"

vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse err)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["message"] = err.message;

    buffer = buildMsg(messageData, 0);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse log)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = log.status;

    buffer = buildMsg(messageData, LoginCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse sign)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = sign.status;

    buffer = buildMsg(messageData, SignupCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse logout)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = logout.status;

    buffer = buildMsg(messageData, logoutCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomsResponse(GetRoomsResponse getRooms)
{
    vector<unsigned char> buffer;
    json messageData;
    json messageDataRooms;
    string rooms_vec;
    messageData["status"] = getRooms.status;
    for (int i = 0; i < getRooms.rooms.size(); i++)
    {
        to_json_room(messageDataRooms, getRooms.rooms[i]);
        messageData["rooms"].push_back(messageDataRooms);
    }

    buffer = buildMsg(messageData, GetRoomsRequestCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse getPlayers)
{
    vector<unsigned char> buffer;
    json messageData;
    string roomStr = "";

    messageData["status"] = getPlayers.status;
    messageData["PlayersInRoom"] = getPlayers.players;

    buffer = buildMsg(messageData, GetPlayersInRoomRequestCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeJoinRoomResponse(JoinRoomResponse joinRoom)
{
    vector<unsigned char> buffer;
    json messageData;
    messageData["room_id"] = joinRoom.room_id;
    messageData["status"] = joinRoom.status;

    buffer = buildMsg(messageData, JoinRoomRequestCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeCreateRoomResponse(CreateRoomResponse createRoom)
{
    vector<unsigned char> buffer;
    json messageData;
    messageData["room_id"] = createRoom.room_id;
    messageData["status"] = createRoom.status;

    buffer = buildMsg(messageData, CreateRoomRequestCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetHighScoreResponse(GetHighScoreResponse highScore)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = highScore.status;
    messageData["statistics"] = highScore.statistics;

    buffer = buildMsg(messageData, GetStatisticsRequestCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetPersonalScoreResponse(GetPersonalStatsResponse personalScore)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = personalScore.status;
    messageData["statistics"] = personalScore.statistics;

    buffer = buildMsg(messageData, GetPersonalStatsCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeLeaveRoomResponse(LeaveRoomResponse leaveRoom)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = leaveRoom.status;

    buffer = buildMsg(messageData, LeaveRoomCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomStateResponse(GetRoomStateResponse roomState)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = roomState.status;
    messageData["answerTimeout"] = roomState.answerTimeout;
    messageData["hasGameBegun"] = roomState.hasGameBegun;
    messageData["players"] = roomState.players;
    messageData["questionCount"] = roomState.questionCount;

    buffer = buildMsg(messageData, GetRoomStateCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeCloseRoomResponse(CloseRoomResponse closeRoom)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = closeRoom.status;

    buffer = buildMsg(messageData, CloseRoomCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeStartGameResponse(StartGameResponse startGame)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = startGame.status;

    buffer = buildMsg(messageData, CloseRoomCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeLeaveGameResponse(LeaveGameResponse leaveGame)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = leaveGame.status;

    buffer = buildMsg(messageData, LeaveGameCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetQuestionResponse(GetQuestionResponse question)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = question.status;
    messageData["question"] = question.question;
    messageData["answers"] = question.answers;

    buffer = buildMsg(messageData, GetQuestionCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeSubmitAnswerResponse(SubmitAnswerResponse submit)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = submit.status;
    messageData["correctAnswerID"] = submit.correctAnswerID;

    buffer = buildMsg(messageData, SubmitAnswerCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetGameResultsResponse(GetGameResultsResponse results)
{
    vector<unsigned char> buffer;
    json messageData;
    json messageDataResults;
    string rooms_vec;
    messageData["status"] = results.status;
    for (int i = 0; i < results.results.size(); i++)
    {
        to_json_results(messageDataResults, results.results[i]);
        messageData["results"].push_back(messageDataResults);
    }

    buffer = buildMsg(messageData, GetGameResultCode);
    return buffer;
}

vector<unsigned char> JsonResponsePacketSerializer::serializeAddQuestion(AddQuestionResponse addQuestion)
{
    vector<unsigned char> buffer;
    json messageData;

    messageData["status"] = addQuestion.status;

    buffer = buildMsg(messageData, AddQuestionCode);
    return buffer;
}



vector<unsigned char> JsonResponsePacketSerializer::buildMsg(json messageData, int code)
{
    vector<unsigned char> resp;
    int len = 0;
    string temp;
    unsigned char lenBytes[4] = { 0 };
    unsigned char msgCode = (unsigned char)code;
    unsigned char* msgBytes;
    temp = messageData.dump();
    len = temp.length();
    msgBytes = new unsigned char[temp.length() + 1];
    strcpy((char*)msgBytes, temp.c_str());

    //>> means left/(2^right)
    lenBytes[0] = (len >> 24) & 0xFF;
    lenBytes[1] = (len >> 16) & 0xFF;
    lenBytes[2] = (len >> 8) & 0xFF;
    lenBytes[3] = len & 0xFF;

    resp.push_back(msgCode);

    for (int i = 0; i < 4; i++)
    {
        resp.push_back(lenBytes[i]);
    }

    for (int i = 0; i < len; i++)
    {
        resp.push_back(msgBytes[i]);
    }

    return resp;
}

void JsonResponsePacketSerializer::to_json_room(json& j, const Room::RoomData& p)
{
    j["id"] = p.id;
    j["name"] = p.name;
    j["maxPlayers"] = p.maxPlayers;
    j["questionsCount"] = p.questionsCount;
    j["timePerQuestion"] = p.timePerQuestion;
    j["isActive"] = p.isActive;
}

void JsonResponsePacketSerializer::to_json_results(json& j, const PlayerResults& p)
{
    j["username"] = p.username;
    j["correctAnswerCount"] = p.correctAnswerCount;
    j["wrongAnswerCount"] = p.wrongAnswerCount;
}

JsonResponsePacketSerializer::PlayerResults::PlayerResults(LoggedUser name, unsigned int correct, unsigned int wrong)
{
    this->correctAnswerCount = correct;
    this->wrongAnswerCount = wrong;
    this->username = name.getName();
}
