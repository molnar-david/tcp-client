#include <iostream>
#include <chrono>
#include <string>
#include <ws2tcpip.h>

#pragma comment(lib, "WS2_32.lib")

int main()
{
	// Initialize WinSock
	WSADATA wsData{};
	WORD ver{ MAKEWORD(2, 2) };

	int ret{ WSAStartup(ver, &wsData) };
	if (ret != 0)
	{
		std::cerr << "Can't initialize WinSock! Error: " << ret << '\n';
		return 0;
	}

	// Create a socket
	SOCKET sock{ socket(AF_INET, SOCK_STREAM, 0) };
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket! Error: " << WSASetLastError << '\n';
		WSACleanup();
		return 0;
	}

	// Fill in a hint structure
	int port{ 54000 };							// Listening port # on the server
	std::string ipAddress{ "127.0.0.1" };		// IP address of the server (localhost)

	sockaddr_in hint{};
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	ret = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (ret == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server! Error: " << WSAGetLastError() << '\n';
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	// Do-while loop: send and receive data
	char buf[4096];
	std::string userInput{};

	do
	{
		// Prompt the user for some input
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput.size() != 0)
		{
			// Send the input
			int ret = send(sock, userInput.c_str(), userInput.size(), 0);
			if (ret == SOCKET_ERROR)
			{
				std::cerr << "Can't send data to server! Error: " << WSAGetLastError() << '\n';
				break;
			}

			// Wait for response
			int bytesReceived{ recv(sock, buf, 4096, 0) };
			if (bytesReceived == SOCKET_ERROR)
			{
				std::cerr << "Can't read from server! Error: " << WSAGetLastError() << '\n';
				break;
			}

			if (bytesReceived == 0)
			{
				std::cout << "Disconnected from the server\n";
				break;
			}

			// Echo response to console
			std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << '\n';
		}
	} while (userInput.size() != 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();

	return 0;
}