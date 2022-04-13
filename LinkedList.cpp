
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
   this->head = nullptr;


   // TODO
}

LinkedList::~LinkedList() {
  clear();
}

void LinkedList::deleteFront()
{
  //create node pointing to head
  Node* toDelete = head;
  //point head to next element
  head = head->next;
  //deletes the node at the front
  delete toDelete;
}

void LinkedList::deleteAt(int i){
  Node* current=head;
  Node* previous = nullptr;
  int index=0;
  if(i==0){
    head = current->next;
    delete current;
  } else{
    while(current!=nullptr && index<i){
      previous=current;

      current=current->next;
      index++;

    }
    if(current->next == nullptr){
      previous->next=nullptr;
      delete current;

    } else{
      previous->next=current->next;



      delete current;
    }
  }
}

//finds if the list contains a file
bool LinkedList::contains(Tile* data){
  bool containsTile=false;

  if(this->head!=nullptr){
    Node* current =this->head;
    while(current!=nullptr && !containsTile){

      //if the tiles are the same
      if(current->tile->colour==data->colour && current->tile->shape==data->shape){
        containsTile=true;
      }
      current=current->next;
    }
  }
  return containsTile;
}

//deletes a certain tile from the linked list
bool LinkedList::deleteData(Tile* data){
  bool deleted = false;

  if(head !=nullptr && contains(data)){
    Node* current=head;
    Node* previous = nullptr;

    if(current->tile->colour==data->colour && current->tile->shape==data->shape){
      delete current;
      head=nullptr;
    } else{
      bool found = false;
      while(current!=nullptr && !found){
        if(current->tile->colour==data->colour && current->tile->shape==data->shape){
          found=true;
        } else{
          previous=current;
          current=current->next;
        }
      }
      if(current->next == nullptr){
        previous->next=nullptr;
        delete current;
        deleted=true;

      } else{
        previous->next=current->next;
        delete current;
        deleted=true;
      }
    }
  }
  return deleted;
}


void LinkedList::deleteBack()
{
  Node* newNode = head;
  Node* prevNode = nullptr;
    if(head->next==nullptr)
    {
      newNode=head;
      delete(newNode);
    }
    else
    {
      newNode=head;
      while(newNode->next!=nullptr)
      {
        prevNode = newNode;
        prevNode = newNode->next;
      }
      prevNode->next=nullptr;
      delete(newNode);
  }
}





void LinkedList::addFront(Tile* tile){
  Node* newNode = new Node(tile, this->head);
  this->head = newNode;

}

void LinkedList::addBack(Tile* tile){
  Node* newNode = new Node(tile, nullptr);


  //if statement to check if head points to nullptr
  if(this->head==nullptr)
  {
    this->head = newNode;
  }
  else
  {
    //list not Empty
    //create temporary node to point to the head
    Node* tempNode = this->head;

    while(tempNode->next!=nullptr)
    {

      //iterate through linkedlist until next is nullptr
      tempNode=tempNode->next;
    //  std::cout<< "tempNode colour: "<< tempNode->tile->colour << " shape: "<< tempNode->tile->shape<< std::endl;
    }
    //assign the temporary node to the next node called newNode
    tempNode->next=newNode;
  }
}

//gets data at an index
Tile* LinkedList::get(int i){

  int index=0;
  Node* current=head;
  if(i!=0){

    while(current->next!=nullptr && index<i){
      index++;
      current=current->next;
    }
  }


  return current->tile;
}

//add a node at an index
void LinkedList::addAt(int i, Tile* data){
  Node* current=head;
  int index=0;
  while(current!=nullptr && index+1<i){
    current= current->next;
    index++;
  }

  Node* newNode = new Node(data, current->next);
  current->next= newNode;

}

int LinkedList::size()
{
  //assign counter to 0
  int counter =0;
  //create node and point to the head which points to nullptr
  if(this->head!=nullptr){
    Node* node = head;
    //a while loop to check if note is not equal to nullptr
    while(node!=nullptr)
    {
      //iterating through the nodes with a counter from 0
      ++counter;
      //assign node to the next node
      node = node->next;
    }
  }

  //returns counter which is the number of elements in the LinkedList
  return counter;
}

void LinkedList::clear()
{
  //creating the node and pointing it to the head
  Node* node = head;

  //a while loop to test if node is not pointing to nullptr
  while(node!=nullptr)
  {
    //save the node pointing to the next
    Node* saveNode = node->next;
    //delete the node
    delete node;
    //node is equal to saveNode
    node = saveNode;
  }
  //after deleting the node the head will need to point to nullptr
  head = nullptr;
}
