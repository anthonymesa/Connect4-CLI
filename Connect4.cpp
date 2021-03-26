#include "Board.hpp"

int main(){

    Board* gameboard = new Board(7, 6);
    gameboard->ResetBoard();

    delete gameboard;
}
