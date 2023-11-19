#запускаеться с помощью команды: make all
client: client.o
	g++ -o client client.o -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

client.o: client.cpp
	g++ -I/usr/include/include -c client.cpp

server: server.o
	g++ -o server server.o db.o -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lmysqlclient

server.o: server.cpp
	g++ -I/usr/include/include -c server.cpp

db.o:	db.cpp
	g++ -w -c db.cpp
	
all:	db.o	client	server clean

clean:
	rm *.o
