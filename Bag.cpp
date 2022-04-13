
#include "TileCodes.h"
#include "Bag.h"


#include <iostream>
#include <string>
#include <random>

Bag::Bag() {
  this->tiles=new LinkedList();

  createBag();

}

Tile* Bag::takeTile(){

  //returns nullptr if the tile bag is emty
  Tile* tile =nullptr;


  if(this->bagSize!=0){

  this->bagSize--;

  //get the tile at the start of the linked list
  tile = this->tiles->get(0);

  //then removes the tile at the start of the list
  this->tiles->deleteFront();

  }


  return tile;
}

int Bag::size() {
  return this->bagSize;
}

// sets the bag size, used for loading in files
void Bag::setBag(LinkedList* tiles){
  this->tiles=tiles;
}

// shuffles the current game
void Bag::shuffle(){

  int min =0;
  int max = this->bagSize-1;
  std::random_device engine;
  std::uniform_int_distribution<int> uniform_dist(min, max);

  //shuffles the bag for the size of bag times 2, to ensure that the bag is completely shuffled
  for(int i =0; i<(this->bagSize*2); i++) {

    int index=uniform_dist(engine);

    //gets a random tile from the bag
    Tile* tile = this->tiles->get(index);
    //deletes the tile from the bag
    this->tiles->deleteAt(index);

    //then adds the tile at the add of the bag
    this->tiles->addBack(tile);

  }
}

// creates the inital bag
void Bag::createBag(){

  this->bagSize=0;

  // defines all the possible colours and shapes, that a tile can have
  Colour colours [6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  Shape shapes [6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

  // a nested foor loop pairs up each shape and colour combination
  for(Colour colour: colours){
    for(Shape shape: shapes){

      //each tile exists twice in the Bag
      this->tiles->addBack(new Tile(colour, shape));
      this->tiles->addBack(new Tile(colour, shape));
      this->bagSize+=2;

    }
  }

  //after creating the bag it is shuffled
  shuffle();
}


//prints the bag to the screen
void Bag::printBag(){
  int index=0;
  while(index<this->bagSize){
    Tile* tile = this->tiles->get(index);
    std::cout <<tile->colour<< tile->shape<<",";
    index++;
  }
  std::cout<<std::endl;
}
