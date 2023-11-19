#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

#define SIZE_BUF 1024
#define PORT 50000

int main()
{
	int socket_file_descriptor(socket(AF_INET, SOCK_STREAM, 0));
	char message[SIZE_BUF];
	
	if(socket_file_descriptor == -1)
	{
		cout << "\nНеудалось создать сокет\n";
		return 0;
	}
	
	sockaddr_in server_address;

	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(PORT);
	server_address.sin_family = AF_INET;

	int bind_status = bind(socket_file_descriptor, (struct sockaddr*) &server_address,sizeof(server_address));

	if (bind_status == -1)
	{
		cout << "\nПривязать сокет не удалось\n";
		return 0;
	}

	int connection_status = listen(socket_file_descriptor, 2);

	if(connection_status == -1)
	{
		cout << "\nСокет не может прослушивать новые соединения\n";
		return 0;
	}
	else cout << "Сервер слушает входящие соединения\n";

	sockaddr_in client;
	socklen_t length = sizeof(client);

	int connection = accept(socket_file_descriptor, (struct sockaddr*) &client, &length);
	if(connection == -1)
	{
		cout << "\nСервер не может принять данные от клиента\n";
		return 0;
	}

	while(1)
	{
		bzero(message, SIZE_BUF);//заполнили нулями массив
		read(connection, message, sizeof(message));
		cout << "Сообщение от клиента: " << message;
		cout << endl;

		cout << "Сообщение для отправки клиенту: ";
		cin >> message;

		cout << endl;
		ssize_t bytes = write(connection, message, sizeof(message));
		
		if(bytes >= 0) cout << "Сообщение клиенту отправлено удачно\n";
	}
	
	close(socket_file_descriptor);

	return 0;
}
