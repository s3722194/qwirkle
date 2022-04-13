#ifndef ASSIGN2_GAMEPLAY_H
#define ASSIGN2_GAMEPLAY_H

#include "Tile.h"
#include "LinkedList.h"
#include "Bag.h"
#include "Board.h"
#include "Player.h"
#include <string>


class Game{
  private:
    Player* player1;
    Player* player2;
    Bag* tileBag;
    Board* board;
    std::string currentPlayer;



public:
  Game(Player* player1, Player* player2);

  //this is for loading in the game
  Game(Player* player1, Player* player2, Bag* bag, Board* board, Player* currentPlayer);
  ~Game();

  Board* getBoard();
  Player* getPlayer1();
  Player* getPlayer2();
  Bag* getTileBag();

  // replaces Tile in players hand
  bool replaceTile(std::string tile);

  //adds tile to board and then adds score to the current player
  bool addTileToBoard(std::string tile, int tileRow, int tileCol);

  //decides if the game has ended or not
  bool hasGameEnded();

  // changes who the current player is
  void changeCurrentPlayer();

  // finds the score from the current player, depending on the move
  int findScore(int numNorth, int numSouth, int numEast, int numWest);

  //gets a point to the current player
  Player* getCurrentPlayer();

  //counts the number of tiles in a given direction
  int numOfTiles(int tileRow, int tileCol, int direction);

  //gets the player which isn't the current player
  Player* getOtherPlayer();


};



#endif // ASSIGN2_GAMEPLAY_H
