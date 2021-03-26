/*
 * Project: Connect4
 * 
 * File: Board Class
 * Author: Anthony Mesa
 * Date: 03-26-21
 */

#include <vector>

class Board{

public:

    Board(const int x, const int y);
    ~Board();

    enum Player { RED=1, YELLOW=2 };
    Player current_turn;
    bool win;
    int moves;

    void PrintBoard();
    bool CheckWin();
    Player NextTurn();
    void ResetBoard();
};
