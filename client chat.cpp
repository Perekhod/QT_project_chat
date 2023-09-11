#include <iostream>
#include <string>
#include "message.h"
#include <SFML/Network.hpp>
#include <thread>
#include <mutex>

void Registration (sf::TcpSocket& sock, sf::Packet& pack, Message& mess, std::string& log, std::string& pas)
{
    std::cout << "Your login: ";
    std::cin >> log;

    std::cout << "\nYour password: ";
    std::cin >> pas;
    std::cout << std::endl;

    mess._sender = log;

    pack << log << pas;
    sock.send(pack);
    pack.clear();
    mess.clear();
}

void receiveMessages(sf::TcpSocket& socket)
{
    sf::Packet packet;
    Message message;

    while (true)
    {
        if (socket.receive(packet) == sf::Socket::Done)
        {
            packet >> message;
           
            std::cout << "\nReceived message from " << message._sender << ": " << message._text_message;
            packet.clear();
            message.clear();
        }
    }
}

int main()
{
    sf::TcpSocket socket;
    socket.setBlocking(false);
    socket.connect("192.168.0.149", 55001); // Заменить на IP адрес сервера

    Message message;
    sf::Packet packet;

    std::string login(""), pass("");
    

    Registration(socket, packet, message, login, pass);

    // Создал поток для получения сообщений
    std::thread messageReceiver(receiveMessages, std::ref(socket));
    messageReceiver.detach();
    
    
    while (true)
    {
        char select('0');
        std::cout << "\n";
        std::cout << "Выберите опцию:"
            << "\n1) Получить список пользователей"
            << "\n2) Отправить личное сообщение"
            << "\n3) Отправить сообщение всем"
            << "\n4) Выйти\n";

        while (true)
        {
        	
            std::cout << "Enter the number from the menu: ";
            std::cin >> select;
            std::cout << std::endl;
            if (select >= '1' && select <= '4') break;
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
					
					std::cout << "\nКому отправим(ник)?: ";
					std::cin >> message._recipient;
					
					std::cout << "\nВаше послание?: ";
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
					
					std::cout << "\nВаше послание?: ";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::getline(std::cin, message._text_message);
					
					packet << message;
					socket.send(packet);
					break;
				}
			
            case '4':
            {
                packet.clear();
                message.clear();

                message._sender = login;
                message._text_message = "delete";
                message._recipient = "Server";

                packet << message;
                socket.send(packet);

                packet.clear();
                message.clear();
				
                socket.disconnect();
                
                return 0;
            }

            default:
                std::cout << "Нет такого номера\n";
                break;
        }
    }

    return 0;
}
