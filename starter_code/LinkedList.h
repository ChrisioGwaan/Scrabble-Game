
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   // Return the current size of the Linked List
   int size();

   // Return the pointer of tile at the given index
   Tile* get(int index);

   Tile* getTile(Letter Letter);

   bool searchTile(Letter letter);

   Tile* moveTile(int index);

   // Add the value to the back of the Linked List
   void append(Tile* data);

   // Remove noed at the given letter from the Linked List
   bool remove(Letter letter);

   // Remove the value at the front of the Linked List
   void removeFront();

   void print_hand();

   // Remove all the values from the Linked List
   void clear();

private:
   Node* head;
   Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H
