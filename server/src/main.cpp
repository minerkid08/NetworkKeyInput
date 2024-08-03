#include <iostream>
#include <winsock2.h>

#include <windows.h>
int main(int argc, const char** argv)
{
	/*INPUT inputs[2] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_LWIN;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = VK_LWIN;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));*/
	SOCKET wsocket;
	SOCKET newWsocket;
	WSADATA data;
	struct sockaddr_in server;
	int serverLen;
	int BUFFERSIZE = 3;
	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		std::cout << "could not create server\n";
		return 1;
	}

	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET)
	{
		std::cout << "could not create socket\n";
		return 1;
	}

	server.sin_family = AF_INET;
	if (argc > 1)
	{
		server.sin_addr.s_addr = inet_addr(argv[1]);
	}
	else
	{
		server.sin_addr.s_addr = inet_addr("0.0.0.0");
	}
	server.sin_port = htons(69420);
	serverLen = sizeof(server);

	if (bind(wsocket, (SOCKADDR*)&server, serverLen))
	{
		std::cout << "could not bind socket\n";
	}

	if (listen(wsocket, 20))
	{
		std::cout << "could not start listening\n";
	}

	std::cout << "server started\n";

	int bytes = 0;
	newWsocket = accept(wsocket, (SOCKADDR*)&server, &serverLen);
	if (wsocket == INVALID_SOCKET)
	{
		std::cout << "could not accept\n";
	}
	while (true)
	{
		char buffer[3] = {0};
		bytes = recv(newWsocket, buffer, BUFFERSIZE, 0);
		if (bytes < 0)
		{
			std::cout << "could not read request\n";
			continue;
		}

		std::cout << buffer << '\n';
	}
	std::cout << "exit :(";
	closesocket(newWsocket);
	closesocket(wsocket);
	return 0;
}
