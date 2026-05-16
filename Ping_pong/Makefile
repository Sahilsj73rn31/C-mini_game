CC = gcc
CFLAGS = -Wall
LIBS = -lncursesw

all: game.exe

game.exe: game.c
	$(CC) $(CFLAGS) game.c -o game.exe $(LIBS)

clean:
	rm -f game.exe