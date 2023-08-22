#include "db.h"

DB::DB() 
{
	mysql_init(&mysql);

	if(&mysql == NULL) {std::cout << "can't create mysql discriptor " << mysql_error(&mysql) << "\n";}


	if(mysql_real_connect(&mysql, "localhost", "root", "root", "chat", 0, NULL, 0))
	{
		std::cout << "You're connected to the chat database\n";
	}
	else
	{
		if(mysql_real_connect(&mysql, "localhost", "root", "root", NULL, 0, NULL, 0))
		{
			mysql_query(&mysql, "create database chat");
			
			mysql_query(&mysql, "use chat");
			
			mysql_query(&mysql, "create table user("
											"id smallint auto_increment,"
											"login varchar(20) not null,"
											"hash text not null,"
											"constraint pk_chat primary key (id))"
											"AUTO_INCREMENT=1" );
											
			mysql_query(&mysql, "create table message("
											"id int auto_increment PRIMARY KEY,"
											"id_sender text not null,"
											"id_recipient text not null,"
											"message_text text,"
											"date_of_sending timestamp default current_timestamp)"
											"AUTO_INCREMENT=1" );
			
			std::cout << "Succes! The chat database was created and also the needed tables\n";
		}
		
		else std::cout << "Fail! " << mysql_error(&mysql) << "\n";
	}
}




DB::~DB() 
{
	//mysql_query(&mysql,"delete from user");
	//mysql_query(&mysql,"delete from message");
	mysql_close(&mysql);
}




void DB::add_user(const std::string &log, const std::string &pass)
{
	std::string insert_query = "INSERT INTO user (login, hash) VALUES ('" + log + "'" + ", " + "'" + pass + "')";
	
	if (mysql_query(&mysql, const_cast<char*>(insert_query.c_str())) != 0 ) 
	{
        std::cerr << "mysql_query(add_user) failed: " << mysql_error(&mysql) << std::endl;
        mysql_close(&mysql);	
    }
}



void DB::del_user(const std::string &log)
{
	std::string delete_query = "delete from user where login='" + log + "'";
	mysql_query(&mysql, const_cast<char*>(delete_query.c_str()));
}


void DB::add_mess(const std::string &sender, const std::string &recipient, const std::string &text)
{
	std::string add_mess_query = "INSERT INTO message (id_sender, id_recipient, message_text) VALUES ('" + sender + "', '" + recipient + "', '" + text + "')";
	
	if(mysql_query(&mysql, const_cast<char*>(add_mess_query.c_str())))  std::cerr << "mysql_query(add_mess) failed: " << mysql_error(&mysql) << std::endl;
}



std::string DB::list_of_users(const std::string &log)
{
	std::string list_query = "select login from user where login!='" + log + "'";
	mysql_query(&mysql, const_cast<char*>(list_query.c_str()));
	
	
	
	if (res = mysql_store_result(&mysql)) {
		
		std::string str("");
	
		int k (0);//считаем количесво строк
		
		while (row = mysql_fetch_row(res)) {
			
			++k;
			
			for (int i = 0; i < mysql_num_fields(res); i++) {
				
				std::string strin(row[i]);//чтобы char* стал string
				
				str += strin + " ";
			}
			
			if((k%4) == 0) str +='\n';
		}
		str +='\n';
		
		return str;
	}
	else
		std::cout << "Ошибка MySql номер " << mysql_error(&mysql) << "\n";
}

