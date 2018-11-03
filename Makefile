# Makefile:
# make all C files and generate executable

# Define the compiler
CC = gcc-8

# Define include path
SRC = src

# Compiler flags
CFLAGS = -g -Wall -Iinclude

# Build target executable
TARGET = calculator

# C source files
SRCS = $(SRC)/*.c

# Object files
OBJS = $(SRCS: .c = .o)

# Default entry
all: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(HEADERS) -o $(TARGET) $(SRCS)

clean:
	rm -rf calculator*