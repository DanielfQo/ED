# Makefile for building the project

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g

# Target executable
TARGET = programa

# Source files
SRCS = main.cpp Disco.h Bloque.h Pagina.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
