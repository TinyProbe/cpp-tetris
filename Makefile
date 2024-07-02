TARGET=tetris.exe
CC=c++
FLAGS=-std=c++20 -g2 -Wall -Wextra -Werror -o $(TARGET) $(INCPATH)
INCPATH=-I C:/Users/137ad/Projects/desktop/tetris/

INC=$(wildcard inc/*.h)
INC+=$(wildcard inc/*.hpp)

SRC=$(wildcard src/*.cc)
SRC+=$(wildcard src/*.cpp)

$(TARGET): Makefile $(INC) $(SRC)
	$(CC) $(FLAGS) $(SRC)

all: $(TARGET)

re: clean all

clean:
	del $(TARGET)

.PHONY: all re clean
