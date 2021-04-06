/*
 * Project: Connect4
 * 
 * File: Board.cpp
 * Author: Anthony Mesa
 * Date: 03-26-21
 */

#include "Board.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>

/**
 * Constructor - sets height, width, and resets board.
 *
 * @param board_size_x Desired width in playable cells
 * @param board_size_y Desired height in playable cells
 */
Board::Board(const int board_size_x, const int board_size_y)
{
    width = board_size_x;
    height = board_size_y;
    ResetBoard();
}

/**
 * Destructor
 */
Board::~Board()
{
    delete gameboard;
}

/**
 * First turn is always set to RED.
 */
void Board::ResetBoard()
{
    // Reset rules

    current_turn = RED;
    win = false;

    // Reset board

    delete gameboard;
    gameboard = new Grid();
    
    // Create new gameboard dynamically by setting
    // all elements of the 2D vector to NONE.

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

/**
 * Dynamically prints the gameboard to screen.
 */
void Board::PrintBoard()
{
    // Topmost border

    std::cout << "\n=======================\n" << std::endl;
    
    // Dynamically create the horizonatal border.

    std::string line_border;
    for(int i = 0; i < width; i++)
    {
        if(i == (width - 1))
        {
            line_border += "+-+";
        } else 
        {
            line_border += "+-";
        }
    }

    // Print horizontal border as first line.

    std::cout << line_border << std::endl;

    // For each row of elements in the gameboard
    // print those elements and then print the 
    // horizontal border.

    for(auto each_row : *gameboard){
        std::cout << "|";
        for(auto each_column : each_row){
            std::cout << (*PlayerToString(each_column)) << "|";
        }
                
        std::cout << std::endl << line_border << std::endl;
    }

    // Bottommost border

    std::cout << "\n=======================\n" << std::endl;
}

/**
 * Get the string that represents the given Player enum.
 *
 * @param player_number The player to be converted to string
 * @return C-style string representing player enum provided
 */
const char* Board::PlayerToString(const Player player_number)
{
    switch(player_number){
        case 1:
            return "RED";
        case 2:
            return "YELLOW";
        default:
            return " ";
    }
}

/**
 * @return The current_player enum as a string
 */
const char* Board::GetCurrentPlayer()
{
    return PlayerToString(current_turn);
}

/**
 * Set a cell in the gameboard at the provided column index 
 * to the value of current_player.
 *
 * Start with the 0'th element in the column and iterate
 * down the column checking if the next space below it is
 * a free space (Player enum NONE). If the next space is not
 * a free space or it is the bottom of the column, place the
 * current_player's piece in the gameboard at that cell.
 *
 * @param column Index of column where move should be made
 */
void Board::MakeMove(const int column)
{
    // Validate that column value is useable.

    if(ValidMove(column)){
        
        // Iterate over the rows of the gameboard.

        for(int i = 0; i < gameboard->size(); i++)
        {
            // If i + 1 equals the size of the gameboard rows
            // vector (the first dimension) then we are at the
            // bottom of the column.

            if((i + 1) == gameboard->size())
            {
                // Set the bottom-most column element to current_turn.

                (*gameboard)[i][column] = current_turn;
            }

            // If we are not at the bottom of the gameboard,
            // check if the next element in the column below
            // the current element is a free space. If not,
            // we have gone as far down the column as we can go.

            else if((*gameboard)[i + 1][column] != NONE)
            {
                (*gameboard)[i][column] = current_turn;
                return;
            }
        }
    }
}

/**
 * Check if column index provided is a valid move.
 *
 * If move isn't valid, then the error message is set,
 * which should be displayed to the user.
 *
 * @param column Index of column where move would be made
 * @return Whether move is valid
 */
bool Board::ValidMove(const int column)
{
    // Check if move is out of bounds.

    if(column >= width)
    {
        error_msg = "\nERROR: Move out of bounds. Try again\n";
        return false;
    }

    // Check if the row is full by checking the first
    // element in the column for NONE enum.
    
    if((*gameboard)[0][column] != NONE)
    {
        error_msg = "\nERROR: Column full, move could not be made. Try again\n";
        return false;
    }

    // Given validity, clear the error message

    error_msg = "";
    return true;
}

/**
 * Alternates the current_turn variable to the
 * next player based on current_turn's current value.
 *
 * @return The enum depicting the next player
 */
Board::Player Board::NextTurn()
{
    if(current_turn == RED)
    {
        current_turn = YELLOW;
        return YELLOW;
    } else
    {
        current_turn = RED;
        return RED;
    }
}

/**
 * Checks for win on the gameboard by iterating
 * accross all directions of the gameboard, checking
 * along all four dimensions. There are four types of 
 * win states that need to be checked for.
 * 
 * (Note, What we are checking for here is whether there
 * are four of the same values in succession in the check).
 *
 * Possible horizontal win:
 *
 *   - - R R R R Y  
 *
 * Possible vertical win:
 * 
 *   -
 *   Y
 *   Y
 *   Y
 *   Y
 *   - 
 *
 * Possible descending diagonal win:
 *
 *   -
 *    Y
 *     R
 *      R
 *       R
 *        R
 *         -
 *
 * Possible ascending diagonal win:
 *
 *         -
 *        -
 *       -
 *      Y
 *     Y
 *    Y
 *   Y
 *
 * If more than one valid win state exists after a single move, 
 * the win will be given to the player whose win state was first
 * discovered.
 *
 * @return Whether a win was detected
 */
bool Board::CheckWin()
{
    // Check for a horizontal win

    for(int i = 0; i < height; i++)
    {
        // Count will be used to keep track of how many of the
        // same type of player that we find in succession.

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

                // here we are using the vector's .at() function to catch out of bounds exceptions
                // so we can iterate over all of the diagonals in the board.

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
                
                // here we are using the vector's .at() function to catch out of bounds exceptions

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

/**
 * Setter for win.
 *
 * @param x New value for win
 */
void Board::SetWin(bool x)
{
    win = x;
}

/**
 * Getter for win.
 *
 * @return win
 */
bool Board::GetWin()
{
    return win;
}

/**
 * Getter for error_msg
 *
 * @return error_msg
 */
std::string Board::GetError()
{
    return error_msg;
}