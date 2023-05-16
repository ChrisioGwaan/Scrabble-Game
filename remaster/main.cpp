#include "iostream"
#include "string"
#include "stdlib.h"

#include "help_info.cpp"

#define EXIT_SUCCESS 0
#define YES_EOF true
#define NO_EOF false

void eof_program(const bool& isEOF);
void show_help();
std::string toLowerCase(const std::string& str);

int main(void) {
    std::string username;

    bool isValidName = false;
    while (!isValidName) {
        std::cout << "Please enter a name below." << std::endl;
        std::getline(std::cin, username);

        if (std::cin.eof())
        {
            eof_program(YES_EOF);
        }
        else if (toLowerCase(username) == "exit" || toLowerCase(username) == "quit")
        {
            eof_program(NO_EOF);
        }
        

        if (username.empty())
        {
            std::cout << "Username cannot be empty!\n" << std::endl;
        }
        else if (username.length() > 15)
        {
            std::cout << "Username is too long! (Up to 15 letters)\n" << std::endl;
        }
        else if (username.find_first_not_of(' ') == std::string::npos)
        {
            std::cout << "Wooah! Whitespaces now, still NOT ALLOWED!\n" << std::endl;
        }
        else if (toLowerCase(username) == "help")
        {
            show_help();
        }
        else
        {
            isValidName = true;
        }
    }

    std::cout << "Welcome to Scrabble!" << std::endl;
    std::cout << "-------------------" << std::endl;


    return EXIT_SUCCESS;
}

void eof_program(const bool& isEOF) {
    if (isEOF)
    {
        std::cout << "Program terminated by end-of-input signal." << std::endl;
    }
    else
    {
        std::cout << "Program terminated by exit or quit input." << std::endl;
    }
    
    exit(EXIT_SUCCESS);
}

std::string toLowerCase(const std::string& str) {
    std::string result;
    result.reserve(str.length()); // Allocate memory based on upcoming string, for better performance

    for (char c : str) {
        result += std::tolower(c);
    }

    return result;
}