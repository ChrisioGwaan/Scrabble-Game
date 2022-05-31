
#include "LinkedList.h"
#include <iostream>
#include <limits>
#include <stdexcept>

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
}

// Deconstruct
// Remove all the values from the Linked List
LinkedList::~LinkedList() {
   clear();
}

// Return the current size of the Linked List
int LinkedList::size() {
   int count = 0;
   Node* current = head;

   // If list is empty, the loop will not be run and return the size of 0
   while (current != nullptr) {
      ++count;
      current = current->next;
   }

   // Return the size of the Linked List
   return count;
}

// Get the pointer at the given index
Tile* LinkedList::get(int index) {
   int count = 0;
   Node* current = head;
   Tile* retVal = nullptr;

   // Make sure the value of the index is valid
   if (index >= 0 && index < size()) {
      while (count < index) {
         ++count;
         current = current->next;
      }
      retVal = current->tile;
   }

   return retVal;
}

// Return a copy of the given letter node
Tile* LinkedList::getTile(Letter Letter) {
   Node* temp = head;
   Node* current = nullptr;
   Tile* retVal = nullptr;

   while (temp != nullptr) {
      if (temp->tile->letter == Letter) {
         current = temp;
         temp = nullptr;
      } else {
         temp = temp->next;
      }
   }

   // If the letter node is found, return a copy of it
   if (current != nullptr) {
      retVal = new Tile(*(current->tile));
   }

   // Otherwise, return null pointer
   return retVal;
}

// If the letter node does not exist, return false
// Otherwise, return true
bool LinkedList::searchTile(Letter letter) {
   Node* temp = head;
   Node* current = nullptr;

   while (temp != nullptr) {
      if (temp->tile->getLetter() == letter) {
         current = temp;
         temp = nullptr;
      } else {
         temp = temp->next;
      }
   }

   // If the letter node is found, return true
   // Otherwise, return false
   if (current != nullptr) {
      return true;
   }
   return false;
}

// Return a copy of the given index of tile pointer
Tile* LinkedList::moveTile(int index) {
   Tile* retVal = nullptr;

   // If index is between 0 and the size of the list
   // Return copy of the tile pointer at the given index
   if (index < size()) {
      Node* current = head;

      for (int i = 0; i < index; ++i) {
         current = current->next;
      }
      retVal = new Tile(*(current->tile));
      remove(retVal->getLetter());
   }

   // Otherwise, return null pointer
   return retVal;
}

// Add the value to the back of the Linked List
void LinkedList::append(Tile* data) {
   Node* toAdd = new Node(data, nullptr);

   if (head == nullptr) {
      head = toAdd;
   } else {
      Node* current = head;
      while (current->next != nullptr) {
         current = current->next;
      }
      current->next = toAdd;
   }
}

// Remove the value at the back of the Linked List
// If remove successfully, return true
bool LinkedList::remove(Letter letter) {
   bool retVal = false;
   Node* current = head;
   Node* prev = nullptr;

   while (current != nullptr) {
      if (current->tile->getLetter() == letter) {
         if (current == head) {
            head = current->next;
            delete current;
         } else if (current->next == nullptr){
            prev->next = nullptr;
            delete current;
         } else {
            prev->next = current->next;
            delete current;
         }
         current = nullptr;
         retVal = true;
      } else {
         prev = current;
         current = current->next;
      }
   }
   delete current;

   // If the given letter node does not exist, return false
   return retVal;
}

// Remove the value at the front of the Linked List
void LinkedList::removeFront() {
   if (head != nullptr) {
      Node* toDelete = head;
      head = head->next;

      delete toDelete;
   } else {
      throw std::runtime_error("List is empty, nothing to be deleted.");
   }
}

// Print out all the cards that the player has on their hand
void LinkedList::print_hand(bool enhance_status) {
   Node* temp = head;
   std::cout << "Your hand is" << std::endl;

   while (temp != nullptr) {
      if (!enhance_status) {
         std::cout << temp->tile->getLetter() << "-" << temp->tile->getValue();
      } else {
         std::cout << "\e[33m" << temp->tile->getLetter() << "-" << temp->tile->getValue() << "\033[0m";
      }

      if (temp->next != nullptr) {
         if (!enhance_status) {
            std::cout << ", ";
         } else {
            std::cout << "\e[33m,\033[0m ";
         }
      } else {
         std::cout << std::endl;
      }
      temp = temp->next;
   }
}

// Remove all the values from the Linked List
void LinkedList::clear() {
   while (head != nullptr) {
      removeFront();
   }
}
