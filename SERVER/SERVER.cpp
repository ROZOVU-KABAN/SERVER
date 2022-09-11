#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include<iostream>
#include<fstream>
#include<WinSock2.h> // библиотека сокетов
#include<Windows.h>
#include<cstring>
#pragma warning(disable: 4996)

// осуществление множественного подключения:

SOCKET Connections[30];
int Index = 0;


//void Wr	iter();

int main()
{
	// WSASStartup - загрузка библиотеки для сетевого подключения
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2,1); // запрашиваемая версия библиотеки
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "ERROR\n";
		exit(1);

	}

	//ЗАполнение информации об адресе сокета:

	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
	





	int sizeOfAddr = sizeof(addr);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr,sizeof(addr));

	listen(sListen, SOMAXCONN);

	for (int i = 0; i < 30; i++)
	{
		SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeOfAddr);
		if (newConnection == 0)
		{
			std::cout << "ERROR2\n";
		}
		else
		{
			std::cout << "Connect\n";
		}
		char msg[256];
		recv(newConnection, msg, sizeof(msg), NULL);
		std::cout << msg;
		Connections[i] = newConnection;
		Index++;

		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Writer, (LPVOID)(i), NULL, NULL);


	}



	system("pause");
	return 0;
}
