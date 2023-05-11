#include "user.h"

User::User() {}

User::User(std::string name, std::string pass) : _log_user(name), _pass_user(pass) {}

std::string User::get_name() const { return _log_user; }

sf::TcpSocket* User::get_socket() { return _socket; }

void User::set_socket(sf::TcpSocket* sock) { _socket = sock; }