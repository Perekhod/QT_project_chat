#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>

class Logging
{
    std::ofstream out;
    std::mutex mtx;
    const std::string filename;

public:
    Logging(const std::string& name):filename(name)
    {
        out.open(name, std::ios::app); // открыл файл в апп моде
    }

    ~Logging()
    {
        out.close();
    }

    std::string read_string()
    {
        std::string line;
    
    	out.close(); // закрыл для записи
    	std::ifstream in(filename, std::ios::in); // открыл для чтения

    	if (in.is_open())
    	{
        	if (std::getline(in, line))
        	{
         	   in.close();
           	   out.open(filename, std::ios::app); // переоткрыл в режиме апп
			   return line;
        	}
    	}
    	return "";
    }

    // записал строку в файл журнала, защитил с помощью mutex
    void write_string(const std::string& message)
    {
        std::lock_guard<std::mutex> lock(mtx);

        if (out.is_open())
        {
            out << message << std::endl;
            out.flush(); // принудительное вывели все буферизированные данные из потока
        }
    }
};

