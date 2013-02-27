all: server

server: server.o chat_command.o dame_command.o basic_command.o frame.o
	gcc -o server server.o chat_command.o dame_command.o basic_command.o include/frame.o -lpthread

server.o: server.c server.h basic_command.h include/command.h
	gcc -o server.o -c server.c

frame.o: include/frame.c include/frame.h
	gcc -o include/frame.o -c include/frame.c

chat_command.o: chat_command.c chat_command.h basic_command.h
	gcc -o chat_command.o -c chat_command.c
	
dame_command.o: dame_command.c dame_command.h basic_command.h
	gcc -o dame_command.o -c dame_command.c

basic_command.o: basic_command.c basic_command.h include/frame.h include/structures.h
	gcc -o basic_command.o -c basic_command.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf server
