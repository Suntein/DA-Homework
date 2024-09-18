# Makefile for building the hello program

# Compiler settings - Can change to clang if preferred
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Build target executable:
TARGET = hello

all: $(TARGET)

$(TARGET): hello.cpp
	$(CC) $(CFLAGS) hello.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
