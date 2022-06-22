#include "JsonRequestPacketDeserializer.h"

JsonRequestPacketDeserializer::LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const char* log)
{
	LoginRequest req;
	const string output(log);
	string name = "";
	string pass = "";
	//parse string in json format to json object
	auto j = json::parse(output);
	cout << j.dump(4) << endl;
	name = j["username"].dump();
	pass = j["password"].dump();
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] != '"')
		{
			req.username = req.username + name[i];
		}
	}
	for (int i = 0; i < pass.length(); i++)
	{
		if (pass[i] != '"')
		{
			req.password = req.password + pass[i];
		}
	}
	return req;
}

JsonRequestPacketDeserializer::SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const char* sign)
{
	SignupRequest req;
	const string output(sign);
	string name = "";
	string pass = "";
	string mail = "";
	string phone = "";
	string addr = "";
	auto j = json::parse(output);
	cout << j.dump(4) << endl;
	//fill request fields with the json values
	name = j["username"].dump();
	pass = j["password"].dump();
	mail = j["email"].dump();
	phone = j["phone"].dump();
	addr = j["addr"].dump();
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] != '"')
		{
			req.username = req.username + name[i];
		}
	}
	for (int i = 0; i < pass.length(); i++)
	{
		if (pass[i] != '"')
		{
			req.password = req.password + pass[i];
		}
	}
	for (int i = 0; i < mail.length(); i++)
	{
		if (mail[i] != '"')
		{
			req.email = req.email + mail[i];
		}
	}
	for (int i = 0; i < phone.length(); i++)
	{
		if (phone[i] != '"')
		{
			req.phone = req.phone + phone[i];
		}
	}
	for (int i = 0; i < addr.length(); i++)
	{
		if (addr[i] != '"')
		{
			req.addr = req.addr + addr[i];
		}
	}
	return req;
}

JsonRequestPacketDeserializer::GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const char* sign)
{
	GetPlayersInRoomRequest req;
	const string output(sign);
	unsigned int room_id;
	//parse string in json format to json object
	auto j = json::parse(output);
	room_id = j["room_id"];
	req.room_id = room_id;
	return req;
}


JsonRequestPacketDeserializer::JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const char* sign)
{
	JoinRoomRequest req;
	const string output(sign);
	unsigned int room_id;
	//parse string in json format to json object
	auto j = json::parse(output);
	room_id = j["room_id"];
	req.room_id = room_id;
	return req;
}

JsonRequestPacketDeserializer::CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const char* sign)
{
	CreateRoomRequest req;
	const string output(sign);
	string room_name;
	unsigned int max_users;
	unsigned int question_count;
	unsigned int answer_timeout;
	//parse string in json format to json object
	auto j = json::parse(output);
	room_name = j["room_name"].dump();
	max_users = j["max_users"];
	question_count = j["question_count"];
	answer_timeout = j["answer_timeout"];
	
	for (int i = 0; i < room_name.length(); i++)
	{
		if (room_name[i] != '"')
		{
			req.room_name = req.room_name + room_name[i];
		}
	}
	req.max_users = max_users;
	req.question_count = question_count;
	req.answer_timeout = answer_timeout;
	return req;

}

JsonRequestPacketDeserializer::AddQuestionRequest JsonRequestPacketDeserializer::deserializeAddQuestionRequest(const char* add)
{
	AddQuestionRequest req;
	const string output(add);
	string question = "";
	string corr = "";
	string answer1 = "";
	string answer2 = "";
	string answer3 = "";
	auto j = json::parse(output);
	cout << j.dump(4) << endl;
	//fill request fields with the json values
	question = j["question"].dump();
	corr = j["correct"].dump();
	answer1 = j["ans1"].dump();
	answer2 = j["ans2"].dump();
	answer3 = j["ans3"].dump();
	for (int i = 0; i < question.length(); i++)
	{
		if (question[i] != '"')
		{
			req.question = req.question + question[i];
		}
	}
	for (int i = 0; i < corr.length(); i++)
	{
		if (corr[i] != '"')
		{
			req.correct = req.correct + corr[i];
		}
	}
	for (int i = 0; i < answer1.length(); i++)
	{
		if (answer1[i] != '"')
		{
			req.ans1 = req.ans1 + answer1[i];
		}
	}
	for (int i = 0; i < answer2.length(); i++)
	{
		if (answer2[i] != '"')
		{
			req.ans2 = req.ans2 + answer2[i];
		}
	}
	for (int i = 0; i < answer3.length(); i++)
	{
		if (answer3[i] != '"')
		{
			req.ans3 = req.ans3 + answer3[i];
		}
	}
	return req;
}

JsonRequestPacketDeserializer::SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const char* submit)
{
	SubmitAnswerRequest req;
	const string output(submit);
	auto j = json::parse(output);
	unsigned int answerID;
	answerID = j["answerID"];
	req.answerID = answerID;
	return req;
}
