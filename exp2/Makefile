# Makefile:
# make all C files and generate executable

# Define the compiler
CC = gcc-8


# Compiler flags
CFLAGS = -g -Wall 

# Build target executable
TARGET = vim-bbn

# C source files
SRCS = main.c stack.c


# Default entry
all: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -rf vim-bbn vim-bbn.dYSM