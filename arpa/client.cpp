#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

#define SIZE_BUF 1024
#define PORT 50000


int main()
{
	int socket_file_descriptor (socket(AF_INET, SOCK_STREAM, 0));
	if (socket_file_descriptor == -1)
	{
		cout << "Создание сокета польностью провалилось\n";
		return 0;
	}

	sockaddr_in server_address, client;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(PORT);
	server_address.sin_family = AF_INET;

	int connection(connect(socket_file_descriptor, (struct sockaddr*)&server_address, sizeof(server_address)));
	
	if(connection == -1)
	{
		cout << "Неудалось соедениться с сервером\n";
		return 0;
	}
	
	char message[SIZE_BUF];

	while(1)
	{
		bzero(message, SIZE_BUF);
		cout << "Сообщение для сервера: ";
		cin >> message;
		cout << endl;

		ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
		if (bytes >= 0) cout << "Успешная отправка\n";

		bzero(message, sizeof(message));
		read(socket_file_descriptor, message, sizeof(message));
		cout << "Сообщение от сервера: " << message << endl;
	}

	close(socket_file_descriptor);

	return 0;
}
