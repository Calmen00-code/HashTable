CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g
OBJ = HashTest.o Hash.o Math.o
EXEC = hash

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

HashTest.o : HashTest.c Hash.h header.h
	$(CC) $(CFLAGS) -c HashTest.c

Hash.o : Hash.c Hash.h header.h
	$(CC) $(CFLAGS) -c Hash.c

Math.o : Math.c Math.h header.h
	$(CC) $(CFLAGS) -c Math.c

clean:
	rm -f $(OBJ) $(EXEC)
