CC = gcc

# Flags for compilation
CFLAGS = -Wall -O2

# Name of the output binary
TARGET = comp

# Source file 
SRC = $(wildcard *.c)

# Object file 
OBJ = $(SRC:.c=.o)

# Default target: compile the program
all: $(TARGET)

# Compile the program
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up: remove object files and the binary
clean:
	rm -f $(OBJ) $(TARGET)
