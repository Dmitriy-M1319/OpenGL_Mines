CC = gcc
CFLAGS = -g -Wall
OPENGLFLAGS = -lglut -lGL -lGLU

all: mines

mines: main.c mine.o
	$(CC) $(CFLAGS) main.c mine.o $(OPENGLFLAGS) -o mines

mine.o: ./lib/mine.c
	$(CC) $(CFLAGS) -c ./lib/mine.c

clean: mine.o
	rm mine.o mines
