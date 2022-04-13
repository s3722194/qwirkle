.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.o LinkedList.o Board.o Player.o Bag.o qwirkle.o Game.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^ -g

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^ -g
