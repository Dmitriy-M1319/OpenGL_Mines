CC = gcc
CFLAGS = -g -Wall
OPENGLFLAGS = -lglut -lGL -lGLU

all: mines

mines: main.c mine.o drawning.o
	$(CC) $(CFLAGS) main.c mine.o drawning.o $(OPENGLFLAGS) -o mines

mine.o: ./lib/mine.c
	$(CC) $(CFLAGS) -c ./lib/mine.c

drawning.o: ./lib/drawning.c
	$(CC) $(CFLAGS) -c ./lib/drawning.c -lGL

clean: mine.o
	rm mine.o mines
