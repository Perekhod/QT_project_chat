#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "message.h"
#include "db.h"
#include "log.h"
#include <thread>
#include <mutex>

// Функция для обработки каждого клиента
void handleClient(sf::TcpSocket* socket, const std::string& log, DB& db,
                  std::vector<std::pair<std::string, sf::TcpSocket*>>& clients,
                  sf::SocketSelector& selector, std::mutex& mutex, Logging& logObj) {
    sf::Packet packet;

    while (true) {
        if (selector.isReady(*socket)) {
            sf::Packet packet;
            if (socket->receive(packet) == sf::Socket::Done) {
                Message message;
                packet >> message;

                // запись полученного сообщения
                std::string logMessage = "Received from " + log + ": " + message._text_message;
                
                logObj.write_string(logMessage);
				
                if (message._text_message == "list_of_users") {
                    packet.clear();
                    message.clear();

                    message._text_message = db.list_of_users(log);

                    message._sender = "server";
                    message._recipient = log;

                    packet << message;
                    socket->send(packet);
                } else if (message._recipient == "all") {
                    packet << message;

                    db.add_mess(message._sender, "all", message._text_message);

                    std::lock_guard<std::mutex> lock(mutex);

                    for (auto& client : clients) {
                        if (client.first != message._sender) {
                            client.second->send(packet);
                        }
                    }
                } else if (message._text_message == "delete") {
                    std::lock_guard<std::mutex> lock(mutex);

                    for (auto iter = clients.begin(); iter != clients.end(); ++iter) {
                        if (iter->first == message._sender) {
                            db.del_user(iter->first);
                            selector.remove(*iter->second);
                            delete iter->second;
                            clients.erase(iter);
                            break;
                        }
                    }
                } else {
                    std::lock_guard<std::mutex> lock(mutex);

                    for (auto& client : clients) {
                        if (message._recipient == client.first) {
                            packet.clear();
                            packet << message;

                            db.add_mess(message._sender, message._recipient, message._text_message);

                            client.second->send(packet);
                            break;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    std::cout << "Server is running on: " << sf::IpAddress::getLocalAddress() << std::endl;

    sf::TcpListener listener;
    sf::SocketSelector selector;
    DB db;
    std::vector<std::pair<std::string, sf::TcpSocket*>> clients;
    std::mutex mutex;

    Logging logObj("log"); // создание объекта для записи сообщений в журнал
    logObj.write_string("Server is running");

    listener.listen(55001);
    selector.add(listener);

    while (true) {
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                sf::TcpSocket* socket = new sf::TcpSocket;
                listener.accept(*socket);

                sf::Packet packet;
                std::string log, pas;
                socket->receive(packet);
                packet >> log >> pas;

                bool clientExists = false;

                for (const auto& client : clients) {
                    if (client.first == log) {
                        logObj.write_string("Client exists: " + log);
                        Message message;
                        message._sender = "server";
                        message._recipient = log;
                        message._text_message = "Exist";

                        packet.clear();
                        packet << message;
                        socket->send(packet);

                        packet.clear();
                        message.clear();

                        delete socket;

                        clientExists = true;
                        break;
                    }
                }

                if (!clientExists) {
                    clients.push_back(std::make_pair(log, socket));
                    selector.add(*socket);

                    db.add_user(log, pas);

                    packet.clear();

                    Message message;
                    message._sender = "server";
                    message._recipient = log;
                    message._text_message = "good";

                    packet.clear();
                    packet << message;
                    socket->send(packet);

                    packet.clear();
                    message.clear();

                    // Сделал поток для клиента и передал параметры
                    std::thread clientThread(handleClient, socket, log, std::ref(db), std::ref(clients), std::ref(selector), std::ref(mutex), std::ref(logObj));
                    clientThread.detach();  // Отсоединяем поток
                }
            }
        }
    }

    return 0;
}
