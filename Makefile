CXX = g++
CC = gcc
CFLAGS = -Wall -Wextra -I./src
CXXFLAGS = -Wall -Wextra -I./src

SRC_C = src/cpu.c src/mem.c src/utils.c
SRC_CPP = src/graph.cpp src/ui.cpp

OBJ_C = $(SRC_C:.c=.o)
OBJ_CPP = $(SRC_CPP:.cpp=.o)

TARGET = resmon

all: $(TARGET)

# Compile C objects
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link everything
$(TARGET): $(OBJ_C) $(OBJ_CPP)
	$(CXX) -o $(TARGET) $(OBJ_C) $(OBJ_CPP) -lncurses -pthread

clean:
	rm -f $(TARGET) $(OBJ_C) $(OBJ_CPP)
