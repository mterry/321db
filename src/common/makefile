#variable declarations
CFLAGS = -g -c
INCLUDE = -I../../include/common
CC = gcc

all: trim.o crel.o

trim.o: trim.c
	$(CC) $(CFLAGS) trim.c $(INCLUDE)

crel.o: crel.c
	$(CC) $(CFLAGS) crel.c $(INCLUDE)

clean:
	rm -f *~ *.o
