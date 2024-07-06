TARGET=tetris.exe
CC=c++
FLAGS=-std=c++20 -g2 -Wall -Wextra -Werror -o $(TARGET)
INCPATH=-I./inc

INC=$(wildcard inc/*.h)
INC+=$(wildcard inc/*.hpp)

SRC=$(wildcard src/*.cc)
SRC+=$(wildcard src/*.cpp)

$(TARGET): Makefile $(INC) $(SRC)
	@$(CC) $(FLAGS) $(INCPATH) $(SRC)

all: $(TARGET)

re: clean all

clean:
	@if exist $(TARGET) del $(TARGET)

.PHONY: all re clean
