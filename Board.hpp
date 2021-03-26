/*
 * Project: Connect4
 * 
 * File: Board Class
 * Author: Anthony Mesa
 * Date: 03-26-21
 */

class Board{

public:

    Board();
    ~Board();

    enum Player { RED=1, YELLOW=2 };
    Player current_turn;
    bool win;
    const int ROWS;
    const int COLS;

    unsigned char moves[][];

    void PrintBoard();
    bool CheckWin();
    Player NextTurn();
    void ResetBoard();
};
