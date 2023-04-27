# Specifies the compiler to be used
CC = g++

# Specifies the compiler flags, including the include directory, library directory,
# compiler warnings, and debugging information
CFLAGS = -I src/include -L src/lib -Wall -g

# Specifies the libraries to be linked, including the SDL2 libraries
LIBS = -lmingw32 -lSDL2main -lSDL2

# Specifies the name of the executable file to be generated
EXECUTABLE = main

# Declares phony targets, which are targets that are not actually files, but rather
# are just names for convenience
.PHONY: all clean check

# Default target that builds the executable
all: $(EXECUTABLE)

# Target that builds the executable by linking the object files
$(EXECUTABLE):  game.c main.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE)  game.c main.c $(LIBS)

# Target that removes the executable file
clean:
	rm -f $(EXECUTABLE)

# Target that runs the executable through valgrind to check for memory leaks
check: $(EXECUTABLE)
	valgrind --leak-check=full ./$(EXECUTABLE)
