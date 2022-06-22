#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
#include <thread>
using namespace std;

void callServe();
int main()
{
	string command = "";
	try
	{
		WSAInitializer wsaInit;
		thread t1(callServe);
		cin >> command;
		if (command == "EXIT")//exit command
		{
			_exit(1);
		}
		t1.join();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}

void callServe()
{
	Server myServer;

	myServer.serve(8826);
}