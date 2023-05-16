#include "iostream"

void show_help() {
    std::cout << "                                           \e[43mHELP!\033[0m" << std::endl;
    std::cout << "\e[33m----------------------------------------------------------------------------------------------\033[0m" << std::endl;
    std::cout << "\e[31mNotice:\033[0m" << std::endl;
    std::cout << "\e[31m      1) Users are welcome to use EOF input or\033[0m" << std::endl;
    std::cout << "\e[31m         type \e[33m\"quit\"\033[0m \e[31m or \e[33m\"exit\"\033[0m \e[31mto exit the program.\033[0m" << std::endl;
    std::cout << "\e[31m      2) If the user do not know what they can type in the command,\033[0m" << std::endl;
    std::cout << "\e[31m         type \e[33m\"help\"\033[0m \e[31mat any time.\033[0m" << std::endl;
    std::cout << "\e[31m      3) If you have typed a wrong input, no worries,\033[0m" << std::endl;
    std::cout << "\e[31m         the program will ask you to type again until you type a correct input.\033[0m" << std::endl;
    std::cout << std::endl;

    std::cout << "1. Menu" << std::endl;
    std::cout << "   \e[33m\"> \"\033[0m \e[32m<---\033[0m Ask user to type the number 1,2,3,4 or 5 in the command." << std::endl;
    std::cout << "   For \e[33m1\033[0m, create a new game." << std::endl;
    std::cout << "   For \e[33m2\033[0m, load a game by enterring the existed file name." << std::endl;
    std::cout << "   For \e[33m3\033[0m, show the credit messages of this program." << std::endl;
    std::cout << "   For \e[33m4\033[0m, end of the program." << std::endl;
    std::cout << "   For \e[33m5\033[0m, configure the enhancement." << std::endl;
    std::cout << std::endl;

    std::cout << "2. New Game" << std::endl;
    std::cout << "   Enter a name for player 1 (uppercase characters only)" << std::endl;
    std::cout << "   \e[33m\"> \"\033[0m \e[32m<---\033[0m Ask player No.1 to type the prefered name (Must be all capital letters) in the command." << std::endl;
    std::cout << "   Enter a name for player 2 (uppercase characters only)" << std::endl;
    std::cout << "   \e[33m\"> \"\033[0m \e[32m<---\033[0m Ask player No.2 to type the prefered name (Must be all capital letters) in the command." << std::endl;
    std::cout << std::endl;

    std::cout << "3. Load Game" << std::endl;
    std::cout << "   Enter the filename from which load a game" << std::endl;
    std::cout << "   \e[33m\"> \"\033[0m \e[32m<---\033[0m Ask user to type the file name, remember to include \'.txt\'." << std::endl;
    std::cout << std::endl;

    std::cout << "4. Major Gameplay" << std::endl;
    std::cout << "   For example, the first player's hand has" << std::endl;
    std::cout << "   \e[33mL-1, O-1, M-3, Q-10, T-1, I-1, C-3\033[0m" << std::endl;
    std::cout << "   \e[33m\"> \"\033[0m \e[32m<---\033[0m User can type the following commands below:" << std::endl;
    std::cout << "             \e[34msave <file_name>\033[0m                 --- Save the gameplay at the given file name" << std::endl;
    std::cout << "             \e[34mpass\033[0m                             --- Pass the current turn." << std::endl;
    std::cout << "             \e[34mquit\033[0m or \e[34mexit\033[0m                     --- Exit the program." << std::endl;
    std::cout << "             \e[34mplace <letter> at <Coordination>\033[0m --- Type the letter of the given hand. Type the coordination from the board." << std::endl;
    std::cout << "                                                  For example, place H AT H7. To place the tile on the board." << std::endl;
    std::cout << "             \e[34mplace Done\033[0m                       --- Finish placing and go to next turn." << std::endl;
    std::cout << "\e[33m----------------------------------------------------------------------------------------------\033[0m" << std::endl;
    std::cout << std::endl;
}