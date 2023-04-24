CC = g++
CFLAGS = -I src/include -L src/lib -Wall -g
LIBS = -lmingw32 -lSDL2main -lSDL2
EXECUTABLE = main

.PHONY: all clean check

all: $(EXECUTABLE)

$(EXECUTABLE):  game.c main.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)  game.c main.c $(LIBS)

clean:
	rm -f $(EXECUTABLE)

check: $(EXECUTABLE)
	valgrind --leak-check=full ./$(EXECUTABLE)