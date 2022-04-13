
#include "Game.h"
#include "TileCodes.h"

#include <iostream>

#include <string>


//defineing constant scores

#define TWO_LINE_SCORE 2
#define ONE_LINE_SCORE 1
#define QWIRKLE_SCORE 6
#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4



Game::Game(Player* player1, Player* player2): player1(player1), player2(player2){
  tileBag= new Bag();
  board= new Board(26,26);
  currentPlayer= player1->getName();
  player1->drawTile(tileBag);
  player2->drawTile(tileBag);
}

Game::Game(Player* player1, Player* player2, Bag* bag, Board* board, Player* currentPlayer): player1(player1), player2(player2), tileBag(bag), board(board){
  this->currentPlayer=currentPlayer->getName();
  player1->drawTile(tileBag);
  player2->drawTile(tileBag);
  }
Game::~Game(){

}

Board* Game::getBoard(){
  return this->board;
}
Player* Game::getPlayer1(){
  return this->player1;
}
Player* Game::getPlayer2(){
  return this->player2;
}
Bag* Game::getTileBag(){
  return this->tileBag;
}

Player* Game::getOtherPlayer(){
  Player* player;
  if(currentPlayer.compare(this->player1->getName())==0){
    player=this->player2;
  } else{
    player=this->player1;
  }

  return player;
}


bool Game::replaceTile(std::string tile){
  std::cout<<"Game replaing tile: "<<tile<<std::endl;
  int removed=false;

  // gets the colour and shape of the current input
  char colour =tile[0];
  int shape=tile[1]-'0';
  //if it's a valid tile
  if((colour==RED || colour==ORANGE || colour==YELLOW || colour==GREEN|| colour==BLUE|| colour==PURPLE) &&
    (shape==CIRCLE || shape==STAR_4 || shape==DIAMOND || shape ==SQUARE || shape== STAR_6 || shape== CLOVER)){
      Tile* tile= new Tile(colour, shape);

      //checks if the tile is in the places hand
      removed= getCurrentPlayer()->removeTile(tile);

      //if the tile is removed the player has to get their hand up to six tiles
      if(removed){
        getCurrentPlayer()->drawTile(tileBag);

      }
    }
  return removed;
}

// changes the who the current player is
void Game::changeCurrentPlayer(){
  if(currentPlayer.compare(this->player1->getName())==0){
    currentPlayer=player2->getName();
  } else{
    currentPlayer=player1->getName();
  }

}


//gets who the current player is
Player* Game::getCurrentPlayer(){
  Player* player;
  if(currentPlayer.compare(this->player1->getName())==0){
    player=this->player1;
  } else{
    player=this->player2;
  }

  return player;
}

bool Game::addTileToBoard(std::string tile, int tileRow, int tileCol){
  bool tileAdded=false;




  //converts the char shape into a int shape
  int shape = tile[1]-'0';
  //if this tile is a valid tile
  if ((tile[0]==RED || tile[0]==ORANGE || tile[0]==YELLOW || tile[0]==GREEN || tile[0]==BLUE || tile[0]==PURPLE) &&
  (shape==CIRCLE || shape==STAR_4 ||  shape==DIAMOND ||  shape==SQUARE ||  shape==STAR_6 ||  shape==CLOVER)){

    //creates the tile and sees if the current player has this piece in their hand
    Tile* tilePiece = new Tile(tile[0], shape);
    if(getCurrentPlayer()->hasTile(tilePiece)){

    // gets a pointer to the board and it's dimensions
    Tile*** tileBoard = this->board->getBoard();

    int maxRow =this->board->getMaxRow();
    int maxCol=this->board->getMaxCol();



  //checks to see if the row and column are validate on the board
  if(tileRow>=0 && tileRow<maxRow && tileCol>=0 && tileCol<maxCol && tileBoard[tileRow][tileCol]==nullptr){


    //are the tiles in these cells compatable with the current tile
    bool north=false;
    bool east=false;
    bool west=false;
    bool south=false;

    //counts the number of tiles
    //can not add over 6 tiles in a row
    int numNorth=0;
    int numEast=0;
    int numWest=0;
    int numSouth=0;

    //if the tile is not against the north border
    if(tileRow>0){

      //if a compatable tile exists in the north
      if(tileBoard[tileRow-1][tileCol]!=nullptr){
        if (tileBoard[tileRow-1][tileCol]->colour ==tilePiece->colour
          || tileBoard[tileRow-1][tileCol]->shape ==tilePiece->shape){

            north=true;

          //checks if there is 6 tiles in this direction
          numNorth= numOfTiles(tileRow-1, tileCol, NORTH);

          //there is a qwirkle in north direction so a piece can be placed there
          if(numNorth>=6){
            north=false;
          }

        }

      //there is a nullptr, so the tile is empty
      }else{
        north=true;
      }
      // the tile is against a board border
    } else{
      north=true;
    }



    //if the tile is not against the south border
    if(tileRow<maxRow){

      // if there is a comptable tile in the south direction
      if(tileBoard[tileRow+1][tileCol]!=nullptr){
        if (tileBoard[tileRow+1][tileCol]->colour ==tilePiece->colour
          || tileBoard[tileRow+1][tileCol]->shape ==tilePiece->shape){
             //adjcent tile is compatable with current tile
             south=true;

             //checks if there is 6 tiles in this direction
             numSouth= numOfTiles(tileRow+1, tileCol, SOUTH);

             //there is a qwirkle in south direction so a piece can be placed there
             if(numSouth>=6){
               south=false;
             }
           }

         //if there is a nullptr
       } else{
         south=true;
       }
       // tile is against the south border
    } else{
      south=true;
    }

    //if this tile is not against the east border
    if(tileCol<maxCol ){
      //if tile is compatable with the adjcent east tile
      if(tileBoard[tileRow][tileCol+1]!=nullptr){
        if (tileBoard[tileRow][tileCol+1]->colour ==tilePiece->colour
          || tileBoard[tileRow][tileCol+1]->shape ==tilePiece->shape){
             // //adjcent tile is compatable with current tile
             east=true;

             //checks if there is 6 tiles in this direction
              numEast= numOfTiles(tileRow, tileCol+1, EAST);

             //there is a qwirkle in east direction so a piece can't be placed there
             if(numEast>=6){
               east=false;
         }
       }

      //if there is a nullptr
    } else{
      east=true;
    }

    // the tile is against the east border
  } else{
    east=true;
  }

    //if piece is not against the west border
    if(tileCol>0){
        //if piece is compatable with the adjcent west tile
        if(tileBoard[tileRow][tileCol-1]!=nullptr){
          if (tileBoard[tileRow][tileCol-1]->colour ==tilePiece->colour
            || tileBoard[tileRow][tileCol-1]->shape ==tilePiece->shape){
              west=true;

               //checks if there is 6 tiles in this direction
               numWest= numOfTiles(tileRow, tileCol-1, WEST);

               //there is a qwirkle in west direction so a piece can't be placed there
               if(numWest>=6){
                 west=false;
           }
        }

        //if there is a nullptr
      } else{
        west=true;
      }
      // the tile is againstt he west border
    } else{
      west=true;
    }


    //if all adjcent tiles are compatable then the piece is added
    // and there are no qwirkles in any direction
    if(north && east && south && west && (numNorth+numSouth)<6 && (numEast+numWest)<6){


      //finds the total score for this move
      int score= findScore(numNorth, numSouth, numEast, numWest);

      //adds the score the current player
      getCurrentPlayer()->addPoints(score);


      //add tile to the board
      this->board->add(tileRow,tileCol, tilePiece);
      tileAdded=true;


      getCurrentPlayer()->removeTile(tilePiece);
      getCurrentPlayer()->drawTile(this->tileBag);
    } else{
      std::cout<< "Invalid Input: Can't place tile there"<<std::endl;
    }

  } else{
    std::cout<<"Invalid Input: That cell isn't avaliable"<<std::endl;
  }
} else{
  std::cout<<"Player doesn't have this piece"<<std::endl;
}
  } else{
    std::cout<<"Invalid Input: Tile doesn't exist"<<std::endl;
  }

  return tileAdded;
}

// finds the number of tiles in a given direction
int Game::numOfTiles(int tileRow, int tileCol, int direction){
  int numTiles=0;

  Tile*** tileBoard = this->board->getBoard();

  int maxRow =this->board->getMaxRow();
  int maxCol=this->board->getMaxCol();

  int currRow=tileRow;
  int currCol=tileCol;


  //adds the number of tiles in a given direction
  while(tileBoard[currRow][currCol]!=nullptr && currRow>=0 && currCol>=0 && currRow<maxRow && currCol<maxCol){

    numTiles++;
    if(direction==NORTH){
      currRow--;
    } else if (direction==EAST){
      currCol++;

    } else if (direction==SOUTH){
      currRow++;

    } else if (direction ==WEST){
      currCol--;
    }

  }
  return numTiles;
}

// finds the points to be added the players score
int Game::findScore(int numNorth, int numSouth, int numEast, int numWest){
  int addToScore=0;

  //if there are tiles in some direction
  if(numNorth>0 || numSouth>0 || numEast>0 || numWest>0){

      // if by adding a piece there will be a qwirkle, in the north/south direction
      if((numNorth+numSouth)==5){
        std::cout<<"QWIRKLE!!"<<std::endl;

        addToScore+=QWIRKLE_SCORE;

      }

      // if by adding a piece there will be qwirkle in the west/east direction
    if((numWest+numEast==5)){
      std::cout<<"QWIRKLE!!"<<std::endl;
      addToScore+=QWIRKLE_SCORE;

    }

    //  finds if the tile is next two lines

    //finds the number of actual adjcent tiles
    int numAdj=0;
    if(numNorth>0){
      numAdj++;
    }
    if (numSouth>0){
      numAdj++;
    }
    if(numEast>0){
      numAdj++;
    }

    if(numWest>0){
      numAdj++;
    }

    // if the player is adding a piece in a direction, and completing two or more lines
    if( numAdj>=2){
      addToScore+=TWO_LINE_SCORE;
      // else the player just gets a standard score
    } else{
      addToScore+=ONE_LINE_SCORE;
    }
  }

    return addToScore;
}

// decides if the game has ended
bool Game::hasGameEnded(){

  bool gameEnd= false;

  //ends if the tile bag is zero and the player hand sizes are also zero
  if(tileBag->size()==0 && player1->getHandSize()==0 && player2->getHandSize()==0){
    gameEnd=true;
  }
  return gameEnd;

}
