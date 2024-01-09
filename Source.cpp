#include<iostream>

#include<winsock2.h>
#include<Windows.h>
#include<string>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

SOCKET Connection;
void print() {
	return 0;
}

void ClientH() {
	char msg[256];
	while (true) {
		recv(Connection, msg, sizeof(msg), 0);
		std::cout << msg << std::endl;
	}
}
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

	Connection = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Eror conect to server" << WSAGetLastError() << std::endl;
		closesocket(Connection);
		WSACleanup();
		return 1;
	}
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ClientH, 0, 0, 0);

	char msg1[256];
	while (true) {
		std::cin.getline(msg1, sizeof (msg1));
		send(Connection, msg1, sizeof(msg1), 0);
		Sleep(10);
	}
	recv(Connection, msg1, sizeof(msg1), 0);
	std::cout << msg1 << std::endl;
	closesocket(Connection);
	WSACleanup();

	system("pause");
	return 0;
}