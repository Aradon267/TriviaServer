#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"
#include "responseCodes.h"
#include "requestsCodes.h"
#include <vector>
#include <iostream>

class RequestHandlerFactory;
class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory* handler);
	virtual bool isRequestRelevent(requestInfo info);
	virtual requestResult handleRequest(requestInfo info);
private:
	RequestHandlerFactory* m_handlerFactory;
	LoginManager* m_loginManager;
	requestResult login(requestInfo info);
	requestResult signup(requestInfo info);
};