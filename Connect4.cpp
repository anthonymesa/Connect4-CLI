#include "Board.hpp"
#include <iostream>

int main(){

    std::cout << "\nWelcome to Connect4!\n" << std::endl;

    Board* gameboard = new Board(7, 6);

    while(!gameboard->win){

        int column = gameboard->GetPlayerMove("Choose a column (1 - 7):");

        gameboard->SetPlayerMove(gameboard->current_turn, column);

        if(gameboard->error)
        {
            std::cout << gameboard->error_msg << std:: endl;
        } else
        {
            gameboard->PrintBoard();
            gameboard->win = gameboard->CheckWin();

            if(gameboard->win)
            {
                std::cout << gameboard->GetPiece(gameboard->current_turn) << " player won!" << std::endl;
                gameboard->PromptRestart();
            } else
            {
                gameboard->current_turn = gameboard->NextTurn();
            }
        }
    }

    delete gameboard;

}