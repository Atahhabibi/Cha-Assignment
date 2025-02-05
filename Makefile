CC = g++
CFLAGS = -Wall -Wextra -std=c++11
TARGET = xed

all: $(TARGET)

$(TARGET): xed.cpp
	$(CC) $(CFLAGS) -o $(TARGET) xed.cpp

clean:
	rm -f $(TARGET)
