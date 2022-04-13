#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

//#include "Bag.h"
#include "Tile.h"
#include "LinkedList.h"
#include <string>



class Player {
  private:
    std::string name;
    int score;
    LinkedList* hand;
  public:
    Player(std::string name);
    ~Player();

    std::string getName();


    int getScore();

    //sets the total score
    void setScore(int i);



    // adds to the current points
    void addPoints(int i);

    void subtractPoints(int i);

    //gets current size of hand
    int getHandSize();

    //gets a linked list of the current hand
    LinkedList* getHand();

    //prints a list of the current hand
    void printHand();

    //adds a tile to hand
    void drawTile(Bag* bag);

    // removes a tile for the hand by index of the tile in the linked list
    bool removeTile(Tile* i);

    bool hasTile(Tile* t);

    //this is used when loading a file to set the hand
    void setHand(LinkedList* list);

};




#endif // ASSIGN2_PLAYER_H
