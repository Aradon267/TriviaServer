#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
using namespace std;
class IRequestHandler
{
public:
	struct requestInfo
	{
		int code;
		string recieve;
		const char* buffer;
	};

	struct requestResult
	{
		vector<unsigned char> response;
		IRequestHandler* newHandler;
	};

	JsonResponsePacketSerializer* serializer;
	JsonRequestPacketDeserializer* deSerializer;
	virtual bool isRequestRelevent(requestInfo info) = 0;
	virtual requestResult handleRequest(requestInfo info) = 0;

};