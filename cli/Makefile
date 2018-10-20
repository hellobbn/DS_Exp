# Makefile:
# make all C files and generate executable

# Define the compiler
CC = gcc-8

# Compiler flags
CFLAGS = -g -Wall

# Build target executable
TARGET = calculator

# C source files
SRCS = *.c

# Object files
OBJS = $(SRCS: .c = .o)

# Default entry
all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -rf calculator*