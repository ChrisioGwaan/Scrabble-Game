
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include <string>

class Player {
public:
   Player(std::string player_name);
   Player(Player &other);
   ~Player();

   std::string getName();
   int getScores();
   void sumUpScores(int point);
   void setScores(int score);
   LinkedList* player_hand;
   int countPass;

private:
   int player_score;
   std::string player_name;
   
};

#endif // ASSIGN2_PLAYER_H