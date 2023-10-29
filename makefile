CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o fileHandler.o map.o player.o terminal.o 
EXEC = traffic

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c fileHandler.h game.h terminal.h
	$(CC) $(CFLAGS) main.c -c

fileHandler.o : fileHandler.c fileHandler.h 
	$(CC) $(CFLAGS) fileHandler.c -c 

map.o : map.c game.h
	$(CC) $(CFLAGS) map.c -c 

player.o : player.c game.h 
	$(CC) $(CFLAGS) player.c -c 

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) terminal.c -c

clean :
	rm -f $(EXEC) $(OBJ)