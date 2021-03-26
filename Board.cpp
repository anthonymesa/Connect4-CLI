#include "Board.hpp"

Board(){
    current_turn = RED;
    win = false;
    moves = new unsigned char[ROWS][COLS];
}