#include <SFML/Network.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "message.h"
#include "db.h"

int main()
{
	std::cout << "Server is running on: " << sf::IpAddress::getLocalAddress() << std::endl;

	
	sf::TcpListener listener;
	sf::SocketSelector selector;
	
	DB db;
		
	std::vector<std::pair<std::string, sf::TcpSocket *>> clients;
	
	listener.listen(55001);
	selector.add(listener);
	
	while(true)
	{
		if(selector.wait())
		{
			if(selector.isReady(listener))
			{
				sf::TcpSocket *socket = new sf::TcpSocket;
				listener.accept(*socket);
				
				sf::Packet packet;
				std::string log, pas;
				socket -> receive(packet);
				packet >> log >> pas;
				
				for(int r = 0; r <= (clients.size() -1); r++)
				{
					if (clients.empty())
					{
						clients.push_back(std::make_pair(log, socket));
						selector.add(*socket);
						
						db.add_user(log,pas);
						
						packet.clear();
						
						Message message;
						message._sender = "server";
						message._recipient = log;
						message._text_message = "good";
						
						packet.clear();
						packet << message;
						socket -> send(packet);
						
						packet.clear();
						message.clear();
						
						socket = nullptr;
						
						break;
					}
					
					if(clients[r].first == log)
					{
						std::cout << "Client exist\n";
						Message message;
						message._sender = "server";
						message._recipient = log;
						message._text_message = "Exist";
						
						packet.clear();
						packet << message;
						socket -> send(packet);
						
						packet.clear(); 
						message.clear();

						delete socket;
						
						break;
					}
					
					if( (r == (clients.size() -1)) && ( (clients[r].first) != (log) ) )
					{
						clients.push_back(std::make_pair(log, socket));
						selector.add(*socket);
						
						db.add_user(log,pas);
						
						packet.clear();
						
						Message message;
						message._sender = "server";
						message._recipient = log;
						message._text_message = "good";
						
						packet.clear();
						packet << message;
						socket -> send(packet);
						
						packet.clear();
						message.clear();
						
						socket = nullptr;
						
						break;
					}
				}				
			}
		//конец 'создания(проверки) пользователя'
			
			//часть проверки запросов от пользователя
			else
			{
				for(int i = 0; i < clients.size(); i++)
				{
					if(selector.isReady(*(clients[i].second)))
					{
						sf::Packet packet;
						if(clients[i].second -> receive(packet) == sf::Socket::Done)
						{
							Message message;
							packet >> message;
							if (message._text_message == "list_of_users")
							{
								packet.clear();
								message.clear();

								message._text_message = db.list_of_users(clients[i].first);
								
								message._sender = "server";
								message._recipient = clients[i].first;

								packet << message;
								clients[i].second -> send(packet);
								packet.clear();
								message.clear();
							}
							
							if(message._recipient == "all")
							{
								packet << message;
								
								db.add_mess(message._sender, "all", message._text_message);
								
								for(int i = 0; i < clients.size(); i++)
								{
									if(clients[i].first != message._sender) clients[i].second -> send(packet);
								}

								packet.clear();
								message.clear();
							}
							
							if (message._text_message == "delete")
							{//очищает вектор от офлайн юзеров
								for(auto iter = clients.begin(); iter < clients.end(); iter++)
								{
									if((*iter).first == message._sender)
									{
										db.del_user((*iter).first);
										selector.remove( (*(*iter).second));
										clients.erase(std::remove(clients.begin(), clients.end(), *iter), clients.end());
										
										packet.clear();
										message.clear();
										
										break;
									}
								}
							//Конец очистки
							}
							
							else
							{
								for(int i = 0; i < clients.size(); i++)
								{
									if(message._recipient == clients[i].first)
									{
										packet.clear();
										packet << message;
										
										db.add_mess(message._sender, message._recipient, message._text_message);
										
										clients[i].second -> send(packet);
										
										packet.clear();
										message.clear();
										break;
									}
								}
							}
						}
					}
				}
			}
			//Конец проверки запросов пользователя
		}		

	}
			
	return 0;
}
