#include "Board.hpp"
#include <algorithm>
#include <iostream>

Board::Board(const int x, const int y){

    current_turn = RED;
    win = false;

    moves = new std::vector<std::vector<unsigned char>*>(y);
    for(auto each_row : *moves){
        each_row = new std::vector<unsigned char>(x);
    }
}

Board::~Board(){
    for(auto each_row : *moves){
        delete each_row;
    }
    delete moves;
}

void Board::ResetBoard(){

    current_turn = RED;
    win = false;

    for(int i = 0; i < moves->size(); i++){
        for(int j = 0; j < moves->at(j)->size(); j++){
            std::cout << moves->at(i)->at(j) << " ";
        }
        std::cout << std::endl;
    }
}

void Board::PrintBoard(){

}