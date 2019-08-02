CC=gcc

CFLAGS=-c -Wall

all: trab

trab: main.o grafos.o
	$(CC) main.o grafos.o -o trab

main.o: main.c
	$(CC) $(CFLAGS) main.c

grafos.o: grafos.c
	$(CC) $(CFLAGS) grafos.c

