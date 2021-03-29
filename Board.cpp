#include "Board.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>

Board::Board(const int board_size_x, const int board_size_y)
{
    width = board_size_x;
    height = board_size_y;
    ResetBoard();
}

Board::~Board()
{
    delete gameboard;
}

void Board::ResetBoard()
{
    current_turn = RED;
    win = false;

    delete gameboard;

    gameboard = new Grid();

    /*
     *  Create the gameboard dynamically
     */
    for(int i = 0; i < height; i++)
    {
        std::vector<Player> temp_grid_row;
        for(int j = 0; j < width; j++)
        {
            temp_grid_row.push_back(NONE);
        }
        gameboard->push_back(temp_grid_row);
    }
}

void Board::PrintBoard()
{
    std::cout << "\n=======================\n" << std::endl;
    
    std::string line_border;
    for(int i = 0; i < width; i++)
    {
        line_border += "+-";
    }

    line_border += "+";

    std::cout << line_border << std::endl;

    for(auto each_row : *gameboard){
        std::cout << "|";
        for(auto each_column : each_row){
            std::cout << (*GetPiece(each_column)) << "|";
        }
                
        std::cout << std::endl << line_border << std::endl;
    }
    std::cout << "\n=======================\n" << std::endl;
}

const char* Board::GetPiece(const Player player_number)
{
    if(player_number == 1)
    {
        return "RED";
    }
    else if(player_number == 2)
    {
        return "YELLOW";
    } else 
    {
        return " ";
    }
}

int Board::GetPlayerMove(const std::string msg)
{
    int column;
    bool valid = false;
    do
    {
        std::cout << GetPiece(current_turn) << " " << msg << " ";
        std::cin >> column;

        if(std::cin.good()){
            valid = true;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nERROR: Input must be a number. Try again\n" << std::endl;
        }

    } while (!valid);

    return column - 1;
}

void Board::SetPlayerMove(const Player player_piece, const int column)
{
    if(ValidMove(column)){
        // check if the cell below it isnt zero, if it isnt,
        // set current cell to player piece
        for(int i = 0; i < gameboard->size(); i++)
        {
            if((i + 1) == gameboard->size())
            {
                (*gameboard)[i][column] = current_turn;
            }
            else if((*gameboard)[i + 1][column] != NONE)
            {
                (*gameboard)[i][column] = current_turn;
                return;
            }
        }
    }
}

bool Board::ValidMove(const int column)
{
    // check if move is out of bounds
    if(column >= width)
    {
        error = true;
        error_msg = "\nERROR: Move out of bounds. Try again\n";
        return false;
    }

    //check if the row is full
    if((*gameboard)[0][column] != 0)
    {
        error = true;
        error_msg = "\nERROR: Column full, move could not be made. Try again\n";
        return false;
    }

    error = false;
    return true;
}

Board::Player Board::NextTurn()
{
    if(current_turn == RED)
    {
        return YELLOW;
    } else
    {
        return RED;
    }
}

bool Board::CheckWin()
{
    // Check for a horizontal win
    for(int i = 0; i < height; i++)
    {
        int count = 1;
        Player last_check = NONE;
        for(int j = 0; j < width; j++)
        {
            if((last_check != NONE) && ((*gameboard)[i][j] == last_check))
            {
                count++;
            } else
            {
                count = 1;
                last_check = (*gameboard)[i][j];
            }

            if(count > 3)
            {
                return true;
            }
        }
    }

    // Check for a vertical win
    for(int i = 0; i < width; i++)
    {
        int count = 1;
        Player last_check = NONE;
        for(int j = 0; j < height; j++)
        {
            if((last_check != NONE) && ((*gameboard)[j][i] == last_check))
            {
                count++;
            } else
            {
                count = 1;
                last_check = (*gameboard)[j][i];
            }

            if(count > 3)
            {
                return true;
            }
        }
    }

    // Check for descending diagonal win
    for(int i = 0; i < (height * 2); i++)
    {
        int count = 1;
        Player last_check = NONE;
        for(int j = 0; j < width; j++)
        {
            try{
                // here I am using the vector's .at() function to catch out of bounds exceptions
                if((last_check != NONE) && (gameboard->at((i - 5) + j)[j] == last_check))
                {
                    count++;
                } else
                {
                    count = 1;
                    last_check = gameboard->at((i - 5) + j)[j];
                }

                if(count > 3)
                {
                    return true;
                }
            } catch (...)
            {

            }
        }
    }

    // Check for ascending diagonal win
    for(int i = 0; i < (height * 2); i++)
    {
        int count = 1;
        Player last_check = NONE;
        for(int j = 0; j < width; j++)
        {
            try{
                // here I am using the vector's .at() function to catch out of bounds exceptions
                if((last_check != NONE) && (gameboard->at(i - j)[j] == last_check))
                {
                    count++;
                } else
                {
                    count = 1;
                    last_check = gameboard->at(i - j)[j];
                }

                if(count > 3)
                {
                    return true;
                }
            } catch (...)
            {

            }
        }
    }

    return false;
}

void Board::PromptRestart()
{
    char input;
    std::cout << "\nWould you like to play again (y/n)? ";
    std::cin >> input;

    if(input == 'y')
    {
        std::cout << "\nStarting a new game..." << std::endl;
        ResetBoard();
    }
}