#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {


  public:

    LinkedList();
    ~LinkedList();

    int size();
    void clear();
    Tile* get(int i);

    void addFront(Tile* data);
    void addBack(Tile* data);

    void deleteFront();
    void deleteBack();

    void addAt(int i, Tile* data);
    void deleteAt(int i);

    bool contains(Tile* data);

    bool deleteData(Tile* data);




  private:
    Node* head;


};

#endif // ASSIGN2_LINKEDLIST_H
