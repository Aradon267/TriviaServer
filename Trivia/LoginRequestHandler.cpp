#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* handler)
{
	this->m_handlerFactory = handler;
	this->m_loginManager = handler->getLoginManager();
}

bool LoginRequestHandler::isRequestRelevent(IRequestHandler::requestInfo info)
{
	return (info.code == LoginCode || info.code == SignupCode);
}

IRequestHandler::requestResult LoginRequestHandler::handleRequest(requestInfo info)
{
	requestResult res;
	if (info.code == LoginCode)
	{
		res = this->login(info);
	}
	else if (info.code == SignupCode)
	{
		res = this->signup(info);
	}
	else
	{
		res.newHandler = this->m_handlerFactory->createLoginRequestHandler(this->m_handlerFactory);
		JsonResponsePacketSerializer::LogoutResponse resp{1};
		vector<unsigned char> buffer = serializer->serializeLogoutResponse(resp);
		res.response = buffer;
	}
	return res;
}

IRequestHandler::requestResult LoginRequestHandler::login(requestInfo info)
{
	requestResult res;
	vector<unsigned char> response;
	int code = 0;
	JsonRequestPacketDeserializer::LoginRequest req = deSerializer->deserializeLoginRequest(info.buffer);
	cout << req.username << " " << req.password << endl;
	code = this->m_loginManager->login(req.username, req.password);
	JsonResponsePacketSerializer::LoginResponse logResp{ code };
	response = serializer->serializeLoginResponse(logResp);
	if (logResp.status == success)
	{
		res.newHandler = this->m_handlerFactory->createMenuRequestHandler(this->m_handlerFactory, new LoggedUser(req.username));
	}
	else
	{
		res.newHandler = this->m_handlerFactory->createLoginRequestHandler(this->m_handlerFactory);
	}
	res.response = response;
	return res;
}

IRequestHandler::requestResult LoginRequestHandler::signup(requestInfo info)
{
	requestResult res;
	vector<unsigned char> response;
	int code = 0;
	JsonRequestPacketDeserializer::SignupRequest req = deSerializer->deserializeSignupRequest(info.buffer);
	cout << req.username << " " << req.password << endl;
	code = this->m_loginManager->signup(req.username, req.password, req.email, req.phone, req.addr);
	JsonResponsePacketSerializer::SignupResponse signResp{ code };
	response = serializer->serializeSignupResponse(signResp);
	if (signResp.status == success)
	{
		res.newHandler = this->m_handlerFactory->createLoginRequestHandler(this->m_handlerFactory);
	}
	else
	{
		res.newHandler = this->m_handlerFactory->createLoginRequestHandler(this->m_handlerFactory);
	}
	res.response = response;
	return res;
}
