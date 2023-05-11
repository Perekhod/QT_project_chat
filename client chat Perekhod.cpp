//	client side 
//	SFML Side Library Used

#include <iostream>
#include <string>
#include "message.h"
#include <SFML/Network.hpp>

void Registration(sf::TcpSocket& sock, sf::Packet& pack, Message& mess, std::string& login, std::string& password)
{
	std::cout << "Your login: ";
	std::cin  >> login;

	std::cout << "Your password: ";
	std::cin  >> password;
	std::cout << std::endl;

	mess._sender = login;

	pack << login << password;
	sock.send(pack);
	//pack.clear();
	//mess.clear();
}

int main()
{
	sf::TcpSocket socket;
	socket.setBlocking(false);
	socket.connect("192.168.0.3", 666);		//	Specify the ip that the server shows

	Message message;
	sf::Packet packet;

	std::string login(""), pass("");

	Registration(socket, packet, message, login, pass);

	while (true)
	{
		socket.receive(packet);
		packet >> message;

		if (message._text_message == "Exist")
		{
			std::cout << "\nA user with such an online login now. Invent a new login and password\n";
			packet.	clear();
			message.clear();
			socket.disconnect();
			socket.connect("192.168.0.3", 666);					//	Here too you need to write ip and port
			Registration(socket, packet, message, login, pass);
		}

		else if (message._text_message == "good")
		{
			std::cout << "\nYou are registered!\n";
			break;
		}
	}

	while (true)
	{
		char select('0');

		std::cout << "	To answer a query or check your input - select Option 4\n"
			<< "1)		Get a list of online users\n"
			<< "2)		Send a private message\n"
			<< "3)		Send a message to all\n"
			<< "4)		Check incoming messages\n"
			<< "5)		Close Application\n";

		while (true)
		{								//	Validation of menu entry
			std::cout << "Enter the number from the menu: ";
			std::cin  >> select;
			std::cout << std::endl;
			if(select >= '1' && select <= '5') break;
			else continue;
		}

		switch (select)
		{
		case '1':
		{
			packet.clear();
			message._sender = login;
			message._text_message = "list_of_users";
			message._recipient = "Server";

			packet << message;
			socket.send(packet);
			break;
		}
		case '2':
		{
			packet.clear();
			message._sender = login;

			std::cout << "Who do we send it to?: ";
			std::cin  >> message._recipient;

			std::cout << "Your message: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, message._text_message);

			packet << message;
			socket.send(packet);
			break;
		}
		case '3':
		{
			packet.clear();

			message._sender = login;

			message._recipient = "all";

			std::cout << "Your message: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, message._text_message);

			packet << message;
			socket.send(packet);
			break;
		}
		case '4':
		{
			if (socket.receive(packet) == sf::Socket::Done)
			{
				packet	  >> message;
				std::cout << "\nMessage from " << message << "\n\n";
				packet.	clear();
				message.clear();
			}
			else std::cout << "\nIncomers haven’t been in yet\n\n";
			break;
		}
		case '5':
		{
			packet.	clear();
			message.clear();

			message._sender = login;
			message._text_message = "delete";
			message._recipient = "Server";

			packet << message;
			socket.send(packet);

			packet.	clear();
			message.clear();
			socket.disconnect();

			return 0;
		}
		default:
			std::cout << "There is no such option\n";
			break;
		}
	}
	return 0;
}