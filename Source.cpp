#include<iostream>

#include<winsock2.h>
#include<Windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
int main() {
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofFader = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Eror conect to server" << WSAGetLastError() << std::endl;
		closesocket(Connection);
		WSACleanup();
		return 1;
	}
	char msg[256];
	recv(Connection, msg, sizeof(msg), 0);
	std::cout << msg << std::endl;
	closesocket(Connection);
	WSACleanup();

	system("pause");
	return 0;
}