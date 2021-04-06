/*
 * Project: Connect4
 * 
 * File: Connect4.cpp
 * Author: Anthony Mesa
 * Date: 03-26-21
 *
 * This is the entry point for Connect4.
 * 
 * HOW TO PLAY:
 *
 * Red always goes first. Choose which column
 * index you want to 'drop your piece' in and then
 * hit enter (i.e. type 3 to drop piece in third column).
 * Repeat, alternating turns until either Red
 * or Yellow wins.
 */

#include "Board.hpp"
#include <iostream>
#include <limits>

/**
 * Prompt the player to input a number and return the input as int.
 *
 * @param current_player Printable string value representing current player
 * @return Int representing desired column for move.
 */
int GetPlayerMove(std::string current_player)
{
    std::string msg = "Choose a column (1 - 7):";
    int column;
    do
    {
        std::cout << current_player << " " << msg << " ";
        std::cin >> column;

        if(std::cin.good()){

            // Using prefix decrement so that column chosen can be
            // normalized to an array index

            return --column;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nERROR: Input must be a number. Try again\n" << std::endl;
        }
    } while (true);    
}

/**
 * Prompt the player to restart the game.
 *
 * @return Whether program should restart
 */
bool PromptRestart()
{
    while(true)
    {
        char input;
        std::cout << "\nWould you like to play again (y/n)? ";
        std::cin >> input;

        if(input == 'y')
        {
            std::cout << "\nStarting a new game...\n" << std::endl;
            return true;
        } else if (input == 'n'){
            std::cout << "\nBok bok boOOK, CHICKEN!\n" << std::endl;
            return false;
        } else {
            std::cout << "\nERROR: Not a valid choice, try again." << std::endl;
        }
    }
}

int main(){

    std::cout << "\nWelcome to Connect4!\n" << std::endl;

    Board* connect4 = new Board(7, 6);

    // Begin game loop

    while(!connect4->GetWin()){

        std::string current_player = connect4->GetCurrentPlayer();

        int column = GetPlayerMove(current_player);

        connect4->MakeMove(column);

        // If GetError isn't empty then that means one of the functions above
        // created an error state that needs to be printed out

        if(connect4->GetError() != "")
        {
            std::cout << connect4->GetError() << std:: endl;
        } else
        {
            connect4->PrintBoard();
            connect4->SetWin(connect4->CheckWin());

            if(connect4->GetWin())
            {
                std::cout << current_player << " player won!" << std::endl;
            
                if(PromptRestart())
                {
                    connect4->ResetBoard();
                }
            } else
            {
                connect4->NextTurn();
            }
        }
    }

    delete connect4;
}