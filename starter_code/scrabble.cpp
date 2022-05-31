
#include "LinkedList.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

#define EXIT_SUCCESS             0
#define LETTER_A                 65 // A in ASCII is 65(dec)
#define LETTER_O                 79 // O in ASCII is 79(dec)
#define LETTER_Z                 90 // Z in ASCII is 90(dec)
#define X_VAL_FIRST              0
#define X_VAL_LAST               14
#define SAVEGAME_LINES           9
#define SAVEGAME_LINES_MYFORMAT  10

#define NEW_GAME        "1"
#define LOAD_GAME       "2"
#define PRINT_CREDITS   "3"
#define QUIT_GAME       "4"
#define ENHANCE_GAME    "5"     // TOUSE

#define HAND_AMOUNT     7
#define BOARD_SIZE      15
#define BINGO           50
#define NOMOVE_MSG      "The board was empty, players did not make a move."

#define MEMBER_1_NAME   "Weixi Guan"
#define MEMBER_1_ID     3830776
#define MEMBER_1_EMAIL  "s3830776@student.rmit.edu.au"

#define MEMBER_2_NAME   "Pak Yin Lai"
#define MEMBER_2_ID     3827212
#define MEMBER_2_EMAIL  "s3827212@student.rmit.edu.au"

std::string menu(bool enhance_status);
void new_game(bool enhance_status);
void save_game(std::string file_name, std::vector<std::vector<Tile*>> board, LinkedList* tile_pack,Player* currentTurnPlayer, Player* player1, Player* player2, bool enhance_status);
void load_game(bool enhance_status);
bool enhancement_status();
void print_credits();
void quit_game();
bool isOnlyUpperLetter(const std::string& user_name);
void start_gameplay(Player* player_1, Player* player_2, LinkedList* tile_pack, std::vector<std::vector<Tile*>> board, std::string currentPlayerName, bool enhance_status);
void print_board(std::vector<std::vector<Tile*>> board, bool enhance_status);
std::vector<std::vector<Tile*>> tile_move(Player* player1, Player* player2, LinkedList* tile_pack, std::vector<std::vector<Tile*>> board, Player* currentTurnPlayer, bool enhance_status);
int calculate_pos_score(bool isYmove, std::vector<std::vector<Tile*>> board, int position_x, int position_y);
int calculate_neg_score(bool isYmove, std::vector<std::vector<Tile*>> board, int position_x, int position_y);
bool isHandFormatCorrect(std::string texts);
bool isTileFormatCorrect(std::string texts);
void print_help();

int main(void) {
   // LinkedList* list = new LinkedList();
   // delete list;
   std::string user_num;
   bool enhance_status = false;

   // 2.1 Launch
   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;
   user_num = PRINT_CREDITS; // Set the user number as 3 to enter the first loop

   // Only No.3 Credits will run this loop again as the assignment has mentioned
   while (user_num == PRINT_CREDITS || user_num == ENHANCE_GAME) {
      user_num = menu(enhance_status);
      if (user_num == NEW_GAME) {
         new_game(enhance_status);  
      } else if (user_num == LOAD_GAME) { 
         load_game(enhance_status);
      } else if (user_num == PRINT_CREDITS) { 
         print_credits();
      } else if (user_num == QUIT_GAME) { 
         quit_game();
      } else if (user_num == ENHANCE_GAME) {
         enhance_status = enhancement_status();
      }
   }

   if (user_num != QUIT_GAME) {
      quit_game();
   }

   return EXIT_SUCCESS;
}

// 2.2 Main Menu
std::string menu(bool enhance_status) {
   std::string user_num;

   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;
   std::cout << "5. Configure Enhancement(Type off/on)" << std::endl;
   std::cout << "Enhancement Status: ";
   if (!enhance_status) {
      std::cout << "\e[31mOFF\033[0m" << std::endl;
      std::cout << std::endl;
      std::cout << "> ";
   } else {
      std::cout << "\e[32mON\033[0m" << std::endl;
      std::cout << std::endl;
      std::cout << "\e[33m>\033[0m ";
   }

   std::cin >> user_num;
   std::cout << std::endl;

   if (!enhance_status) {
      // If the input is not a integer number, type again
      // If the input value is less than 1 and more than 4, type again
      while (!std::cin.eof() && user_num != NEW_GAME && user_num != QUIT_GAME && user_num != LOAD_GAME && user_num != PRINT_CREDITS && user_num != ENHANCE_GAME) {
         std::cout << "Try again!" << std::endl;
         std::cout << "> ";
         std::cin >> user_num;
         std::cout << std::endl;
      }

      if (std::cin.eof()) {
         // End the program
         user_num = QUIT_GAME;
      }
   } else {
      // Enhancement
      while (!std::cin.eof() && user_num != NEW_GAME && user_num != QUIT_GAME && user_num != LOAD_GAME && user_num != PRINT_CREDITS && user_num != ENHANCE_GAME) {
         if (user_num.compare("help") == 0) {
            // Print help messages
            print_help();
         } else if (user_num.compare("exit") == 0 || user_num.compare("quit") == 0) {
            // End the program
            quit_game();
         } else {
            std::cout << "\e[34mThe input is not number 1, 2, 3, 4 or 5. Try again!\033[0m" << std::endl;
            std::cout << "Want help? Just type \e[33m\"help\"\033[0m in the command line." << std::endl;
         }
         std::cout << "\e[33m>\033[0m ";
         std::cin >> user_num;
         std::cout << std::endl;
      }

      if (std::cin.eof()) {
         // End the program
         user_num = QUIT_GAME;
      }
   }

   return user_num;
}

// 2.2.1 New Game
void new_game(bool enhance_status) {
   std::string player_1;
   std::string player_2;
   
   std::cout << "Starting a New Game\n" << std::endl;
   if (!enhance_status) {
      // M2 - Original Gameplay
      std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
      std::cout << "> ";
   } else {
      // M3 - Enhanced Gameplay
      std::cout << "Enter a name for \e[36mplayer 1\033[0m (uppercase characters only)" << std::endl;
      std::cout << "\e[33m>\033[0m ";
   }
   std::cin >> player_1;
   std::cout << std::endl;

   while (!std::cin.eof() && !isOnlyUpperLetter(player_1)) {
      if (!enhance_status) {
         // M2 - Original Gameplay
         std::cout << "Enter a name again for player 1 (uppercase characters only)" << std::endl;
         std::cout << "> ";
      } else {
         // M3 - Enhanced Gameplay
         if (player_1.compare("help") == 0) {
            print_help();
            std::cout << "\e[33m>\033[0m ";
         } else if (player_1.compare("exit") == 0 || player_1.compare("quit") == 0) {
            quit_game();
         } else {
            std::cout << "Enter a name again for \e[36mplayer 1\033[0m (uppercase characters only)" << std::endl;
            std::cout << "\e[33m>\033[0m ";
         }
      }
      std::cin >> player_1;
      std::cout << std::endl;
   }

   if (std::cin.eof()) {
      quit_game();
   }

   if (!enhance_status) {
      // M2 - Original Gameplay
      std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
      std::cout << "> ";
   } else {
      // M3 - Enhanced Gameplay
      std::cout << "Enter a name for \e[35mplayer 2\033[0m (uppercase characters only)" << std::endl;
      std::cout << "\e[33m>\033[0m ";
   }
   std::cin >> player_2;
   std::cout << std::endl;

   while (!std::cin.eof() && !isOnlyUpperLetter(player_2)) {
      if (!enhance_status) {
         // M2 - Original Gameplay
         std::cout << "Enter a name again for player 2 (uppercase characters only)" << std::endl;
         std::cout << "> ";
      } else {
         // M3 - Enhanced Gameplay
         if (player_2.compare("help") == 0) {
            print_help();
            std::cout << "\e[33m>\033[0m ";
         } else if (player_2.compare("exit") == 0 || player_2.compare("quit") == 0) {
            quit_game();
         } else {
            std::cout << "Enter a name again for \e[35mplayer 2\033[0m (uppercase characters only)" << std::endl;
            std::cout << "\e[33m>\033[0m ";
         }
      }
      std::cin >> player_2;
      std::cout << std::endl;
   }

   if (std::cin.eof()) {
      quit_game();
   }

   Player* player1 = new Player(player_1);
   Player* player2 = new Player(player_2);
   
   // Create a list
   LinkedList* tile_pack = new LinkedList();

   // Create a board
   // 2D vector for the type of Tile pointer
   std::vector<std::vector<Tile*>> board;

   // Read ScrabbleTiles.txt file
   std::ifstream scrabbleTiles("ScrabbleTiles.txt");

   // Create a temporary string for getting texts from the file
   std::string tempTexts;

   // Create a temporary tile pointer
   Tile* tempTile;

   // Create a temporary letter and value for storing texts to the tile from the file
   Letter tempLetter;
   Value tempValue;

   // Creat a temporary vector
   std::vector<Tile*> tempTiles;
   
   while (!scrabbleTiles.eof()) {
      std::getline(scrabbleTiles, tempTexts);
      
      if (!tempTexts.empty()) {
         tempLetter = tempTexts.front();
         tempValue = std::stoi(tempTexts.substr(2, tempTexts.size()-1));
         tempTile = new Tile(tempLetter, tempValue);
         tempTiles.push_back(tempTile);
      }
   }

   // Shuff the tile card
   while (!tempTiles.empty()) {
      srand(time(nullptr));
      int randIndex = rand() % tempTiles.size();
      tile_pack->append(tempTiles[randIndex]);
      tempTiles.erase(tempTiles.begin() + randIndex);
   }

   // Give the random 7 tiles to the players
   for (int i = 0; i < HAND_AMOUNT; ++i) {
      player1->player_hand->append(tile_pack->moveTile(0));
      player2->player_hand->append(tile_pack->moveTile(0));
   }
   
   // Game start!
   if (!enhance_status) {
      // M2 - Original Gameplay
      std::cout << "Let's Play!" << std::endl;
      std::cout << std::endl;
   } else {
      // M3 - Enhanced Gameplay
      std::cout << "\e[41mLet's Play!\033[0m" << std::endl;
      std::cout << std::endl;
   }

   // <Normal gameplay continues from here>
   start_gameplay(player1, player2, tile_pack, board, "", enhance_status);
   delete player1;
   delete player2;
}

// 2.2.2 Load Game
void load_game(bool enhance_status) {
   std::ifstream load_game_file;
   std::string load_game_file_name;

   std::cout << "Enter the filename from which load a game" << std::endl;
   if (!enhance_status) {
      std::cout << "> ";
   } else {
      std::cout << "\e[33m>\033[0m ";
   }
   std::cin >> load_game_file_name;
   std::cout << std::endl;

   // Create a boolean value to identify whether the file contents have correct formats
   bool isCorrectFormat = false;

   // Create a vector to store all the contents from the file
   std::vector<std::string> file_contents;

   // Create a vector to store 'T' or 'F' for checking the format of the load game file
   std::vector<char> t_f_vector;

   // For reading every lines from the file
   std::string line;

   // Open the file with the given file name
   load_game_file.open(load_game_file_name);

   // If the given file name does not exist, will enter this loop
   while (!std::cin.eof() && !load_game_file) {
      if (!enhance_status) {
         std::cout << "The file <" << load_game_file_name << "> does not exist." << std::endl;
         std::cout << std::endl;
         std::cout << "Enter the filename from which load a game" << std::endl;
         std::cout << "> ";
      } else {
         std::cout << "\e[41mThe file <" << load_game_file_name << "> does not exist.\033[0m" << std::endl;
         std::cout << std::endl;
         std::cout << "Enter the filename from which load a game" << std::endl;
         std::cout << "\e[33m>\033[0m ";
      }
      
      std::cin >> load_game_file_name;
      std::cout << std::endl;

      load_game_file.open(load_game_file_name);
   }

   if (std::cin.eof()) {
      quit_game();
   }

   // Read file contents and store to the vector that we have created
   while (std::getline(load_game_file, line)) {
      file_contents.push_back(line);
   }

   // Close the file
   load_game_file.close();

   // If the lines if the load game file is not equal to 9, format is not correct
   if ((int)file_contents.size() == SAVEGAME_LINES || (int)file_contents.size() == SAVEGAME_LINES_MYFORMAT) {
      int num = 0;
      if ((int)file_contents.size() == SAVEGAME_LINES_MYFORMAT) {
         num = 1;
      }
      // Access the vector contents one by one
      for (int i = num; i < (int)file_contents.size(); ++i) {
         if (i == num && isOnlyUpperLetter(file_contents.at(i))) { // Line 1 checking
            t_f_vector.push_back('T');
         } else if (i == num+1 && std::stoi(file_contents.at(i)) >= 0) { // Line 2 checking
            t_f_vector.push_back('T');
         } else if (i == num+2 && isHandFormatCorrect(file_contents.at(i))) { // Line 3 checking
            t_f_vector.push_back('T');
         } else if (i == num+3 && isOnlyUpperLetter(file_contents.at(i))) { // Line 4 checking
            t_f_vector.push_back('T');
         } else if (i == num+4 && std::stoi(file_contents.at(i)) >= 0) { // Line 5 checking
            t_f_vector.push_back('T');
         } else if (i == num+5 && isHandFormatCorrect(file_contents.at(i))) { // Line 6 checking
            t_f_vector.push_back('T');
         } else if (i == num+6 && (isTileFormatCorrect(file_contents.at(i)) || file_contents.at(i) == NOMOVE_MSG)) { // Line 7 checking
            t_f_vector.push_back('T');
         } else if (i == num+7 && isHandFormatCorrect(file_contents.at(i))) { // Line 8 checking
            t_f_vector.push_back('T');
         } else if (i == num+8 && isOnlyUpperLetter(file_contents.at(i))) { // Line 9 checking
            t_f_vector.push_back('T');
         }
      }

      // To check whether the t_f_vector has 9 'T' values
      // If the size is equal to 9, it means that the formats are all correct
      if ((int)t_f_vector.size() == SAVEGAME_LINES) {
         isCorrectFormat = true;
      } 
   }

   // When the format of the load game file is not correct, print the fail message and quit the program
   if (!isCorrectFormat) {
      if (!enhance_status) {
         std::cout << "Scrabble game failed to be loaded" << std::endl;
      } else {
         std::cout << "\e[41mScrabble game failed to be loaded\033[0m" << std::endl;
      }
      std::cout << std::endl;
   } else {
      if (!enhance_status) {
         std::cout << "Scrabble game successfully loaded" << std::endl;
      } else {
         std::cout << "\e[42mScrabble game successfully loaded\033[0m" << std::endl;
      }
      std::cout << std::endl;

      std::vector<std::string> str_vector;

      // Create a board
      std::vector<std::vector<Tile*>> board;

      Tile* tempTile;
      int num = 0;
      if ((int)file_contents.size() == SAVEGAME_LINES_MYFORMAT) {
         num = 1;
      }
      
      /*
      Set player name
      */
      Player* player1 = new Player(file_contents.at(num+0));
      Player* player2 = new Player(file_contents.at(num+3));

      /*
      Store players' hand
      */
      std::string texts;
      texts = file_contents.at(num+2);
      while ((int)texts.find(",") != -1) {
         str_vector.push_back(texts.substr(0, texts.find(",")));
         texts = texts.substr(texts.find(",") + 2, texts.length());
      }
      str_vector.push_back(texts);

      for (int i = 0; i < (int)str_vector.size(); ++i) {
         tempTile = new Tile(str_vector[i][0], (int)str_vector[i][2] - '0');
         player1->player_hand->append(tempTile);
      }
      str_vector.clear();

      texts = file_contents.at(num+5);
      while ((int)texts.find(",") != -1) {
         str_vector.push_back(texts.substr(0, texts.find(",")));
         texts = texts.substr(texts.find(",") + 2, texts.length());
      }
      str_vector.push_back(texts);

      for (int i = 0; i < (int)str_vector.size(); ++i) {
         tempTile = new Tile(str_vector[i][0], (int)str_vector[i][2] - '0');
         player2->player_hand->append(tempTile);
      }
      str_vector.clear();

      // Set the players' scores
      player1->setScores(std::stoi(file_contents.at(num+1)));
      player2->setScores(std::stoi(file_contents.at(num+4)));

      // Store the board contents
      if (file_contents.at(num+6) != NOMOVE_MSG) {

         // Resize the board to 15*15
         board.resize(BOARD_SIZE);
         for (int i = 0; i < BOARD_SIZE; ++i) {
            board[i].resize(BOARD_SIZE);
         }

         texts = file_contents.at(num+6);

         while ((int)texts.find(" ") != -1) {
            str_vector.push_back(texts.substr(0, texts.find(" ")));
            texts = texts.substr(texts.find(" ") + 1, texts.length());
         }
         str_vector.push_back(texts);

         // To store letter
         std::vector<char> tile_letter;

         // To store Y value
         std::vector<int> y_val;

         // To store X value
         std::vector<int> x_val;

         for (int i = 0; i < (int)str_vector.size(); ++i) {
            tile_letter.push_back(str_vector[i][0]);
            y_val.push_back((int)str_vector[i][2] - LETTER_A);
            x_val.push_back((int)str_vector[i][3] - '0');
         }
         
         LinkedList* tempList = new LinkedList();
         Tile* tile_board;

         for (int i = 0; i < (int)y_val.size(); ++i) {
            tile_board = new Tile(tile_letter[i], 0);
            tempList->append(tile_board);
         }
         
         int count = 0;
         while (count != (int)y_val.size()) {
            for (int i = 0; i < BOARD_SIZE; ++i) {
               for (int j = 0; j < BOARD_SIZE; ++j) {
                  if (j == x_val[count] && i == y_val[count]) {
                     Tile* tempTile2 = tempList->getTile(tile_letter[count]);
                     board[i][j] = tempTile2;
                  }
               } 
            }
            ++count;
         }
         str_vector.clear();
      }

      /* 
      Store hand to tile bag 
      */

      // Create a linked list to store hand into tile bag
      LinkedList* tile_pack = new LinkedList();

      texts = file_contents.at(7);
      while ((int)texts.find(",") != -1) {
            str_vector.push_back(texts.substr(0, texts.find(",")));
            texts = texts.substr(texts.find(",") + 2, texts.length());
      }
      str_vector.push_back(texts);
      Tile* temp_Tile;

      for (int i = 0; i < (int)str_vector.size(); ++i) {
         temp_Tile = new Tile(str_vector[i][0], (int)str_vector[i][2] - '0');
         tile_pack->append(temp_Tile);
      }
      str_vector.clear();

      /* 
      Start the gameplay
      */
      start_gameplay(player1, player2, tile_pack, board, file_contents.at(8), enhance_status);
   }
}

// 2.2.3 Credits (Show student information)
void print_credits() {
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Name: " << MEMBER_1_NAME << std::endl;
   std::cout << "Student ID: " << MEMBER_1_ID << std::endl;
   std::cout << "Email: " << MEMBER_1_EMAIL << std::endl;
   std::cout << std::endl;
   
   std::cout << "Name: " << MEMBER_2_NAME << std::endl;
   std::cout << "Student ID: " << MEMBER_2_ID << std::endl;
   std::cout << "Email: " << MEMBER_2_EMAIL << std::endl;
   std::cout << "----------------------------------" << std::endl;
   std::cout << std::endl;
}

// 2.2.4 Quit
void quit_game() {
   std::cout << "Goodbye!" << std::endl;
   exit(EXIT_SUCCESS);
}

// Check player's name ONLY contains captial letters
// According to ASCII table, letter 'A' is 65(dec) and 'Z' is 90(dec)
// By checking ASCII Dec number of each letter is between 65 and 90(Included)
// If not, this function will return false as a bool value
bool isOnlyUpperLetter(const std::string& user_name) {
   for (char const &c : user_name) {
      if (int(c) < LETTER_A || int(c) > LETTER_Z) {
         return false;
      }
   }
   return true;
}

// Gameplay function
void start_gameplay(Player* player1, Player* player2, LinkedList* tile_pack, std::vector<std::vector<Tile*>> board, std::string currentPlayerName, bool enhance_status) {
   Player* currentTurnPlayer;
   Player* nextTurnPlayer;
   
   if (currentPlayerName.length() > 0) {
      if (currentPlayerName == player1->getName()) {
         currentTurnPlayer = player1;
         nextTurnPlayer = player2;
      } else {
         currentTurnPlayer = player2;
         nextTurnPlayer = player1;
      }
   } else {
      currentTurnPlayer = player1;
      nextTurnPlayer = player2;
   }

   std::cin.ignore();
   while (player1->player_hand->size() > 0 && player2->player_hand->size() > 0 && tile_pack->size() > 0 && currentTurnPlayer->countPass < 3) {

      // The current player's turn
      if (!enhance_status) {
         std::cout << currentTurnPlayer->getName() << ", it's your turn" << std::endl;
         std::cout << "Score for " << player1->getName() << ": " << player1->getScores() << std::endl;
         std::cout << "Score for " << player2->getName() << ": " << player2->getScores() << std::endl;
      } else {
         if (currentTurnPlayer->getName().compare(player1->getName()) == 0) {
            std::cout << "\e[36m" << currentTurnPlayer->getName() << "\033[0m, it's your turn" << std::endl;
         } else {
            std::cout << "\e[35m" << currentTurnPlayer->getName() << "\033[0m, it's your turn" << std::endl;
         }
         std::cout << "Score for \e[36m" << player1->getName() << "\033[0m: " << player1->getScores() << std::endl;
         std::cout << "Score for \e[35m" << player2->getName() << "\033[0m: " << player2->getScores() << std::endl;
      }
      
      print_board(board, enhance_status);

      currentTurnPlayer->player_hand->print_hand(enhance_status);
      std::cout << std::endl;

      board = tile_move(player1, player2, tile_pack, board, currentTurnPlayer, enhance_status);
      
      // If the player places all the seven tiles in the hand
      // Print BINGO message and give 50 points
      if (currentTurnPlayer->player_hand->size() == 0) {
         currentTurnPlayer->sumUpScores(BINGO);
         std::cout << std::endl;
         if (!enhance_status) {
            std::cout << "BINGO!!!" << std::endl;
         } else {
            std::cout << "\e[43mBINGO!!!\033[0m" << std::endl;
         }
         std::cout << std::endl;
         std::cout << currentTurnPlayer->getName() << std::endl;
         std::cout << std::endl;
      }

      for (int i = 0; i < HAND_AMOUNT - currentTurnPlayer->player_hand->size(); ++i) {
         if (tile_pack->size() > 0) {
            currentTurnPlayer->player_hand->append(tile_pack->moveTile(0));
         }
      }

      std::cout << std::endl;
      // Create a temporary player pointer to make a swap betweeen current and next turn player
      Player* tempP = currentTurnPlayer;
      currentTurnPlayer = nextTurnPlayer;
      nextTurnPlayer = tempP;
   }

   // Game over session
   if (!enhance_status) {
      std::cout << "Game over" << std::endl;
      std::cout << "Score for " << player1->getName() << ": " << player1->getScores() << std::endl;
      std::cout << "Score for " << player2->getName() << ": " << player2->getScores() << std::endl;

      // Compare player's scores to print the winner out
      if (player1->getScores() > player2->getScores()) {
         std::cout << "Player " << player1->getName() << " won!" << std::endl;
      } else {
         std::cout << "Player " << player2->getName() << " won!" << std::endl;
      }
   } else {
      std::cout << "\e[41mGame over\033[0m" << std::endl;
      std::cout << "Score for \e[36m" << player1->getName() << "\033[0m: " << player1->getScores() << std::endl;
      std::cout << "Score for \e[35m" << player2->getName() << "\033[0m: " << player2->getScores() << std::endl;

      // Compare player's scores to print the winner out
      if (player1->getScores() > player2->getScores()) {
         std::cout << "Player \e[36m" << player1->getName() << "\033[0m won!" << std::endl;
      } else {
         std::cout << "Player \e[35m" << player2->getName() << "\033[0m won!" << std::endl;
      }
   }
   std::cout << std::endl;
   // Quit the game
   quit_game();
}

// Print the game board
void print_board(std::vector<std::vector<Tile*>> board, bool enhance_status) {
   if (!enhance_status) {
      std::cout << "    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14" << std::endl;
      std::cout << "  -------------------------------------------------------------" << std::endl;
   } else {
      std::cout << "\e[104m    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  \033[0m" << std::endl;
      std::cout << "\e[104m  -------------------------------------------------------------\033[0m" << std::endl;
   }
   
   for (int i = 0; i < BOARD_SIZE; ++i) {
      if (!enhance_status) {
         std::cout << char(LETTER_A + i);
      } else {
         std::cout << "\e[104m" << char(LETTER_A + i) << "\033[0m";
      }
      
      for (int j = 0; j < BOARD_SIZE; ++j) {
         if (!enhance_status) {
            std::cout << " | ";
         } else {
            std::cout << " \e[94m|\033[0m ";
         }

         if (!board.empty()) {
            if (board[i][j] != 0) {
               if (!enhance_status) {
                  std::cout << board[i][j]->getLetter();
               } else {
                  std::cout << "\e[94m" << board[i][j]->getLetter() << "\033[0m";
               }
            } else {
               std::cout << " ";
            }
         } else {
            std::cout << " ";
         }
      }

      if (!enhance_status) {
         std::cout << " |";
      } else {
         std::cout << " \e[94m|\033[0m";
      }
      std::cout << std::endl;
   }
   std::cout << std::endl;
}

std::vector<std::vector<Tile*>> tile_move(Player* player1, Player* player2, LinkedList* tile_pack, std::vector<std::vector<Tile*>> board, Player* currentTurnPlayer, bool enhance_status) {
   // To check if the movement is vertical or horizontal
   // To check the input is valid
   // To check if the input needs to exit the loop
   bool isYmove = false;
   bool isValidInput = false;
   bool game_exit = false;

   // To track the amount of card that player uses
   int hand_amount = 0;

   // To track input nearby the word after first loop
   int x_head = 0;
   int y_head = 0;
   int x_tail = 0;
   int y_tail = 0;

   // Using vector for accessing the split of input string
   std::vector<std::string> player_move_input;

   // Using vector to gather the position of all tiles
   std::vector<int> x_vector;
   std::vector<int> y_vector;

   std::string player_move;

   if (!enhance_status) {
      std::cout << "> ";
   } else {
      std::cout << "\e[33m>\033[0m ";
   }
   // Get the whole line of the string from input
   std::getline(std::cin, player_move);

   if (!std::cin.eof()) {
      while (!game_exit && hand_amount != HAND_AMOUNT) {
         // Split the string by space
         std::istringstream iss(player_move);

         // Store each word in the string to vector
         while (iss) {
            std::string tempString;
            iss >> tempString;
            player_move_input.push_back(tempString);
         }

         // Saving the game when user inputs save
         if (player_move_input[0].compare("save") == 0) {
            isValidInput = true;
            // Save the current gameplay
            save_game(player_move_input[1], board, tile_pack, currentTurnPlayer, player1, player2, enhance_status);
         } else if (player_move_input[0].compare("pass") == 0) {
            isValidInput = true;
            game_exit = true;
            // Count the times of pass
            ++currentTurnPlayer->countPass;
         }

         if (enhance_status) {
            if (player_move_input[0].compare("quit") == 0 || player_move_input[0].compare("exit") == 0) {
               quit_game();
            } else if (player_move_input[0].compare("help") == 0) {
               isValidInput = true;
               print_help();
            }
         }
         
         if (player_move_input.size() > 1 && player_move_input[0] != "save") {
            // 'place Done' command
            if (player_move_input[0].compare("place") == 0 && player_move_input[1].compare("Done") == 0) {
               isValidInput = true;
               game_exit = true;
            } else if (player_move_input[0] == "replace" && player_move_input[1].size() == 1) { // Replace tile
               // Using ASCII to check whether it is a letter and a capital letter
               if (int(player_move_input[1][0]) >= LETTER_A && int(player_move_input[1][0]) <= LETTER_Z) {
                  // Check whether the player has this letter on hand
                  if (currentTurnPlayer->player_hand->searchTile(player_move_input[1][0])) {
                     isValidInput = true;
                     Tile* tempTile = currentTurnPlayer->player_hand->moveTile(player_move_input[1][0]);
                     tile_pack->append(tempTile);
                     currentTurnPlayer->player_hand->append(tile_pack->get(0));
                  }
               }
            } else if (player_move_input.size() > 3) {
               if (player_move_input[0].compare("place") == 0 && player_move_input[2].compare("at") == 0) { // Place ... at ... command
                  Letter hand_letter = player_move_input[1][0]; // Get the character of the index 1 string
                  Letter position_y_char = player_move_input[3][0]; // Get the first character of index 3 string
                  Value position_x = std::stoi(player_move_input[3].substr(1, player_move_input.size()-1)); // Convert last character to integer

                  // Check if letter in index 1 is one of the letters in player's hand
                  // And, the first character of index 3 is between A and O using ASCII number
                  // And, the letter in index 1 is capital letter only from A to Z
                  // And, position is between 0 and 14
                  if (currentTurnPlayer->player_hand->searchTile(hand_letter) && position_y_char >= 'A' && 
                     position_y_char <= 'O' && hand_letter >= LETTER_A && hand_letter <= LETTER_Z && position_x >= X_VAL_FIRST && position_x <= X_VAL_LAST) {
                     // To convert the y value to number as 0, 1, 2...
                     int position_y = int(position_y_char) - LETTER_A;

                     // From start, the board is empty to go
                     if (hand_amount == 0 && board.empty()) {
                        isValidInput = true;

                        // Add 1 for every turn
                        ++hand_amount;
                        // Resize the board to 15*15
                        board.resize(BOARD_SIZE);
                        for (int i = 0; i < BOARD_SIZE; ++i) {
                           board[i].resize(BOARD_SIZE);
                        }

                        // Let the position of head and tail are the current word position
                        x_head = position_x;
                        x_tail = position_x;
                        y_head = position_y;
                        y_tail = position_y;

                        Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                        
                        board[position_y][position_x] = tempTile;
                        
                        currentTurnPlayer->player_hand->remove(hand_letter);
                        x_vector.push_back(position_x);
                        y_vector.push_back(position_y);
                     } else if (hand_amount == 0 && !board.empty()) { // If the board is not empty but it is the first tile
                        // If the next tile is being placed next to the head
                        if (!board[position_y][position_x] &&
                              (board[position_y][position_x+1] || board[position_y+1][position_x] || board[position_y][position_x-1] || board[position_y-1][position_x])) {
                           
                           // Set it is a valid input first
                           isValidInput = true;

                           // Add 1 for every turn
                           ++hand_amount;

                           // Let the position of head and tail are the current word position
                           x_head = position_x;
                           x_tail = position_x;
                           y_head = position_y;
                           y_tail = position_y;

                           Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                           board[position_y][position_x] = tempTile;
                           currentTurnPlayer->player_hand->remove(hand_letter);
                           x_vector.push_back(position_x);
                           y_vector.push_back(position_y);
                        }
                     } else if (hand_amount == 1) { // The player uses 1 tile
                        // If the next tile is being placed next to the head
                        if (!board[position_y][position_x] && (x_head - position_x >= -1 && x_head - position_x <= 1) && (y_head - position_y >= -1 && y_head - position_y <= 1)) {
                           // Set it is a valid input first
                           isValidInput = true;
                           
                           Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                           board[position_y][position_x] = tempTile;
                           currentTurnPlayer->player_hand->remove(hand_letter);
                           x_vector.push_back(position_x);
                           y_vector.push_back(position_y);
                           ++hand_amount;

                           x_head = position_x;
                           y_head = position_y;

                           // Check the position x value of head and tile is 0
                           // If it is, then the word is vertical
                           // If not, then the word is horizontally
                           if (x_head - position_x == 0 && x_tail - position_x == 0) {
                              isYmove = true;
                           }
                        } else if (!board[position_y][position_x] && x_head - position_x == 0 && y_head - position_y == 0) { // (Vertical)Check the direction of next tile is same as head
                           int temp_position_Y = y_head;
                           Tile* tempTile = board[y_head][x_head];

                           if (y_head < position_y) {
                              while (tempTile) {
                                 ++temp_position_Y;
                                 tempTile = board[temp_position_Y][x_head];
                              }
                           } else {
                              while (tempTile) {
                                 --temp_position_Y;
                                 tempTile = board[temp_position_Y][x_head];
                              }
                           }

                           if (temp_position_Y == position_y) {
                              // Set it is a valid input first
                              isValidInput = true;

                              Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                              board[position_y][position_x] = tempTile;
                              currentTurnPlayer->player_hand->remove(hand_letter);
                           }
                        } else if (!board[position_y][position_x] && y_head - position_y == 0 && y_tail - position_y == 0) { // (Horizontal)Check the direction of next tile is same as head
                           int temp_position_X = x_head;
                           Tile* tempTile = board[y_head][x_head];

                           if (x_head < position_x) {
                              while (tempTile) {
                                 ++temp_position_X;
                                 tempTile = board[y_head][temp_position_X];
                              }
                           } else {
                              while (tempTile) {
                                 --temp_position_X;
                                 tempTile = board[y_head][temp_position_X];
                              }
                           }

                           if (temp_position_X == position_x) {
                              // Set it is a valid input first
                              isValidInput = true;

                              Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                              board[position_y][position_x] = tempTile;
                              currentTurnPlayer->player_hand->remove(hand_letter);
                              x_vector.push_back(position_x);
                              y_vector.push_back(position_y);
                           }
                        }
                     } else if (isYmove) {
                        // Vertical move part
                        if (!board[position_y][position_x] && (y_head - position_y >= -1 && y_head - position_y <= 1) && x_head - position_x == 0) {
                           // Set it is a valid input first
                           // Hand amount +1
                           isValidInput = true;
                           ++hand_amount;

                           Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                           board[position_y][position_x] = tempTile;
                           currentTurnPlayer->player_hand->remove(hand_letter);
                           x_vector.push_back(position_x);
                           y_vector.push_back(position_y);

                           x_head = position_x;
                           y_head = position_y;
                        } else if (!board[position_y][position_x] && (y_tail - position_y >= -1 && y_tail - position_y <= 1) && x_tail - position_x == 0) {
                           // Set it is a valid input first
                           // Hand amount +1
                           isValidInput = true;
                           ++hand_amount;

                           Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                           board[position_y][position_x] = tempTile;
                           currentTurnPlayer->player_hand->remove(hand_letter);
                           x_vector.push_back(position_x);
                           y_vector.push_back(position_y);

                           x_tail = position_x;
                           y_tail = position_y;
                        }
                     } else {
                        // Horizontal move part
                        if (!board[position_y][position_x] && (x_head - position_x >= -1 && x_head - position_x <= 1) && y_head - position_y == 0) {
                           // Set it is a valid input first
                           // Hand amount +1
                           isValidInput = true;
                           ++hand_amount;

                           Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                           board[position_y][position_x] = tempTile;
                           currentTurnPlayer->player_hand->remove(hand_letter);
                           x_vector.push_back(position_x);
                           y_vector.push_back(position_y);

                           x_head = position_x;
                           y_head = position_y;
                        } else if (!board[position_y][position_x] && (x_tail - position_x >= -1 && x_tail - position_x <= 1) && y_tail - position_y == 0) {
                           // Set it is a valid input first
                           // Hand amount +1
                           isValidInput = true;
                           ++hand_amount;

                           Tile* tempTile = currentTurnPlayer->player_hand->getTile(hand_letter);
                           board[position_y][position_x] = tempTile;
                           currentTurnPlayer->player_hand->remove(hand_letter);
                           x_vector.push_back(position_x);
                           y_vector.push_back(position_y);

                           x_tail = position_x;
                           y_tail = position_y;
                        }
                     }
                  }
               }
            }
         }

         // If the input is not correct and EOF
         if (!isValidInput && !std::cin.eof()) {
            if (!enhance_status) {
               std::cout << "Invalid Input" << std::endl;
            } else {
               std::cout << "\e[33mInvalid Input\033[0m" << std::endl;
            }
         }
         player_move_input.clear();

         // If input is 'place Done', will not run this code
         if (!game_exit) {
            if (!enhance_status) {
               std::cout << "> ";
            } else {
               std::cout << "\e[33m>\033[0m ";
            }
            // Get the whole line of the string from input
            std::getline(std::cin, player_move);
         }

         // If the previous input is EOF, program end
         if (std::cin.eof()) {
            quit_game();
         }
      }
   
      int toAddScore = 0;
      int y_size_int = (int)y_vector.size();
      int posScore = 0;
      int negScore = 0;
      int temp_position_x = x_head;
      int temp_position_y = y_head;

      if (y_size_int == 1) {
         if (board[y_vector[0] + 1][x_vector[0]] || board[y_vector[0] - 1][x_vector[0]]) {
            isYmove = true;
         } else {
            isYmove = false;
         }
      }
   
      for (int i = 0; i < (y_size_int); ++i) {
         temp_position_x = x_vector[i];
         temp_position_y = y_vector[i];
         posScore = calculate_pos_score(isYmove, board, temp_position_x, temp_position_y);
         negScore = calculate_neg_score(isYmove, board, temp_position_x, temp_position_y);

         if (posScore > 0 || negScore > 0) {
            toAddScore += board[temp_position_y][temp_position_x]->getValue() + posScore + negScore;
         }
      }

      toAddScore += calculate_pos_score(!isYmove, board, x_vector[0], y_vector[0]);
      toAddScore += calculate_neg_score(!isYmove, board, x_vector[0], y_vector[0]);
      toAddScore += board[y_vector[0]][x_vector[0]]->getValue();
      currentTurnPlayer->sumUpScores(toAddScore);
   } else {
      quit_game();
   }

   return board;
}

// Calculate the total points of a word at the given position in positive direction
int calculate_pos_score(bool isYmove, std::vector<std::vector<Tile*>> board, int position_x, int position_y) {
   if (isYmove) {
      ++position_x;
   } else {
      ++position_y;
   }

   Tile* tempTile = board[position_y][position_x];
   if (tempTile) {
      return tempTile->getValue() + calculate_pos_score(isYmove, board, position_x, position_y);
   } else {
      return 0;
   }
}

// Calculate the total points of a word at the given position in negative direction
int calculate_neg_score(bool isYmove, std::vector<std::vector<Tile*>> board, int position_x, int position_y) {
   if (isYmove) {
      --position_x;
   } else {
      --position_y;
   }

   Tile* tempTile = board[position_y][position_x];
   if (tempTile) {
      return tempTile->getValue() + calculate_pos_score(isYmove, board, position_x, position_y);
   } else {
      return 0;
   }
}

// Save the gameplay
void save_game(std::string file_name, std::vector<std::vector<Tile*>> board, LinkedList* tile_pack,Player* currentTurnPlayer, Player* player1, Player* player2, bool enhance_status) {
   Tile* tempTile;
   file_name += ".txt"; // Add .txt suffix to the file name
   
   std::ofstream gameSave;
   gameSave.open(file_name);

   if (enhance_status) {
      gameSave << "#myformat" << std::endl; // M3 Enhancement
   }

   // Player 1 details
   gameSave << player1->getName() << std::endl;
   gameSave << player1->getScores() << std::endl;
   
   for (int i = 0; i < player1->player_hand->size(); ++i) {
      tempTile = player1->player_hand->get(i);
      if (i != player1->player_hand->size() - 1) {
         gameSave << tempTile->getLetter() << "-" << tempTile->getValue() << ", ";
      } else {
         gameSave << tempTile->getLetter() << "-" << tempTile->getValue() << std::endl;
      }
   }

   // Player 2 details
   gameSave << player2->getName() << "\n";
   gameSave << player2->getScores() << "\n";

   for (int i = 0; i < player2->player_hand->size(); ++i) {
      tempTile = player2->player_hand->get(i);
      if (i != player2->player_hand->size() - 1) {
         gameSave << tempTile->getLetter() << "-" << tempTile->getValue() << ", ";
      } else {
         gameSave << tempTile->getLetter() << "-" << tempTile->getValue() << std::endl;
      }
   }

   // Current gameplay board
   if (!board.empty()) {
      std::string tile_position;
      for (int i = 0; i < BOARD_SIZE; ++i) {
         for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != 0) {
               int x = j + LETTER_A;
               int y = i;
               
               tile_position.push_back(board[i][j]->getLetter());
               tile_position += "@";
               tile_position.push_back((char)x);
               tile_position += std::to_string(y) + " ";
            }
         }
      }
      // Delete the last whitespace
      tile_position.pop_back();
      gameSave << tile_position << std::endl;;
   } else {
      gameSave << NOMOVE_MSG << std::endl;
   }

   // Tile bag contents
   for (int i = 0; i < tile_pack->size(); ++i) {
      tempTile = tile_pack->get(i);
      if (i != tile_pack->size() - 1) {
         gameSave << tempTile->getLetter() << "-" << tempTile->getValue() << ", ";
      } else {
         gameSave << tempTile->getLetter() << "-" << tempTile->getValue() << std::endl;
      }
   }

   // Current player name
   gameSave << currentTurnPlayer->getName() << std::endl;

   // File close
   gameSave.close();
}

// To check if the hand format is correct, for example, E-1 is correct
bool isHandFormatCorrect(std::string texts) {
   // To return a boolean value
   bool retVal = false;

   std::vector<int> tileValue = {1, 2, 3, 4, 5, 8, 10};
   std::vector<std::string> str_vector;
   while ((int)texts.find(",") != -1) {
      str_vector.push_back(texts.substr(0, texts.find(",")));
      texts = texts.substr(texts.find(",")+2, texts.length());
   }
   str_vector.push_back(texts);

   for (int i = 0; i < (int)str_vector.size(); ++i) {
      if (int(str_vector[i][0]) >= 65 && int(str_vector[i][0]) <= 90) {
         if (str_vector[i][1] == '-') {
            for (int j = 0; j < (int)str_vector.size(); ++j) {
               if ((int)str_vector[i][2] - '0' == tileValue[j]) {
                  retVal = true;
               }
            }
         }
      }
   }

   return retVal;
}

// To check if the tile format is correct, for example, N@H7 is correct
bool isTileFormatCorrect(std::string texts) {
   // To return a boolean value
   bool retVal = false;

   std::vector<std::string> str_vector;
   while ((int)texts.find(" ") != -1) {
      str_vector.push_back(texts.substr(0, texts.find(" ")));
      texts = texts.substr(texts.find(" ")+1, texts.length());
   }
   str_vector.push_back(texts);

   for (int i = 0; i < (int)str_vector.size(); ++i) {
      if (int(str_vector[i][0]) >= LETTER_A && int(str_vector[i][0]) <= LETTER_Z) {
         if (str_vector[i][1] == '@' && int(str_vector[i][2]) >= LETTER_A && int(str_vector[i][2]) <= LETTER_O && (int)str_vector[i][3] - '0' >= X_VAL_FIRST && (int)str_vector[i][3] - '0' <= X_VAL_LAST) {
            retVal = true;
         }
      }
   }

   return retVal;
}

bool enhancement_status() {
   std::string type_status;
   std::cout << "Do you want to turn off/on configuration? (off/on)" << std::endl;
   std::cout << "> ";
   std::cin >> type_status;


   while (!std::cin.eof() && type_status.compare("off") != 0 && type_status.compare("on") != 0) {
      if (type_status.compare("help") == 0) {
         print_help();
      } else {
         std::cout << "Invalid input! Want help? Just type \e[33m\"help\"\033[0m in the command line." << std::endl;
      }
      std::cout << "> ";
      std::cin >> type_status;
   }

   if (std::cin.eof()) {
      quit_game();
      exit(EXIT_SUCCESS);
   }
   std::cout << std::endl;

   if (type_status.compare("off") == 0) {
      return false;
   } else {
      return true;
   }
}

// TO IMPLEMENT
void print_help() {
   std::cout << "----------------------------" << std::endl;
   std::cout << "Menu session" << std::endl;
   std::cout << "   INPUT   |  EXPLAINATION  " << std::endl;
   std::cout << std::endl;
}

void eof_program() {
   quit_game();
   exit(EXIT_SUCCESS);
}