CC = gcc
CFLAGS = -Wall -Wextra -I./src
SRC = src/monitor.c src/cpu.c src/utils.c
TARGET = monitor

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
