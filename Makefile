# CC=g++
# PROJECT=spacewar
# SRC=src/main.cpp src/game.cpp src/player.cpp
# OBJ=$(SRC:.cpp=.o)
# SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system

# .PHONY: all

# all: $(SRC) $(PROJECT)
# 	rm src/*.o

# $(PROJECT): $(OBJ)
# 	$(CC) $(OBJ) -o $(PROJECT) $(SFML_FLAGS)

# .cpp.o:
# 	$(CC) -c -Wall $< -o $@

# clean:
# 	rm $(PROJECT)

all: compile link

compile:
	g++ -Isrc/include -c main.cpp game.cpp player.cpp

link: 
	g++ main.o game.o player.o -o game -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system