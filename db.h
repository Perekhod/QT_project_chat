#pragma once

#include <string>
#include <iostream>
#include "/usr/include/mysql/mysql.h"

class DB
{
	private:
		MYSQL mysql;
		MYSQL_RES* res;
		MYSQL_ROW row;
		
	public:
		DB();//или Создаем базу или подключаемся к ней
		~DB();//Отключаемся от бд
		
		void add_user(const std::string &, const std::string &);
		void del_user(const std::string &);
		void add_mess(const std::string &, const std::string &, const std::string &);
		std::string list_of_users(const std::string &);
};
