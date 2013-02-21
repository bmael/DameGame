all: server

server: server.o frame.o
	gcc -o server server.o include/frame.o -lpthread
	
server.o: server.c server.h include/frame.h include/structures.h include/command.h
	gcc -o server.o -c server.c 

frame.o: include/frame.c include/frame.h
	gcc -o include/frame.o -c include/frame.c
	
clean:
	rm -rf *.o

mrproper: clean
	rm -rf server