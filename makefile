CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g
OBJ = HashTest.o Hash.o Math.o print.o
EXEC = hash

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

HashTest.o : HashTest.c Hash.h header.h Math.h
	$(CC) $(CFLAGS) -c HashTest.c

Hash.o : Hash.c Hash.h header.h print.h
	$(CC) $(CFLAGS) -c Hash.c

Math.o : Math.c Math.h header.h
	$(CC) $(CFLAGS) -c Math.c

print.o : print.c print.h
	$(CC) $(CFLAGS) -c print.c

clean:
	rm -f $(OBJ) $(EXEC)
