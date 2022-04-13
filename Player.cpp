#include <iostream>
#include <string>
#include "Player.h"


Player::Player(std::string name) {
  this->name = name;
  this->hand= new LinkedList();
  score = 0;

}

//returns the player's score
int Player::getScore() {
  return score;
}

std::string Player::getName(){
  return name;
}

//sets the player's score to a specified number
void Player::setScore(int i) {
  score=i;
}

//adds points to the player's score
void Player::addPoints(int i) {
  score+=i;
}

//subtracts points from the player's score
void Player::subtractPoints(int i) {
  score-=i;
}

//returns the player's hand
LinkedList* Player::getHand() {
  return hand;
}

//returns the size of the player's hand
int Player::getHandSize() {
  return hand->size();
}

//removes a specified tile from the player's hand
bool Player::removeTile(Tile* i) {
  bool deleted = false;

  //only deletes if the hand size is greater than zero
  if(hand->size()!=0) {
    // can only delete data that is in the bag
    if(hand->contains( i)){
      hand->deleteData(i);
      deleted=true;
    }
    else {
      std::cout << "Error: Hand does not contain tile" << std::endl;
    }
  }
  else {
    std::cout << "Error: Hand is empty" << std::endl;
  }
  return deleted;
}

//draws tiles from the bag until the player's hand is full
void Player::drawTile(Bag* bag) {
  while (hand->size()<6 && bag->size()>0) {
    hand->addBack(bag->takeTile());
  }
}

//boolean to check if the player has a specified tile in their hand
bool Player::hasTile(Tile* t) {
  return hand->contains(t);
}

//sets tha player's hand used for loading in files
void Player::setHand(LinkedList* list){
  this->hand=list;
}
