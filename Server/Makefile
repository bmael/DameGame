all: server

server: server.o
	gcc -o server server.o -lpthread
	
server.o: server.c structures.h
	gcc -o server.o -c server.c 


	
clean:
	rm -rf *.o

mrproper: clean
	rm -rf server