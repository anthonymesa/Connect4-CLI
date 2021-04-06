/*
 * Project: Connect4
 * 
 * File: Board.hpp
 * Author: Anthony Mesa
 * Date: 03-26-21
 */

#include <vector>
#include <string>

class Board{

public:

    Board(const int board_size_x, const int board_size_y);
    ~Board();
    
    // Win state    

    bool win;
    void SetWin(bool x);
    bool GetWin();
    bool CheckWin();

    // Current player state

    enum Player { NONE, RED, YELLOW };
    const char* PlayerToString(const Player player_number);
    const char* GetCurrentPlayer();
    Player NextTurn();
    Player current_turn;

    // Gameboard state

    typedef std::vector<std::vector<Player>> Grid;

    int height, width;
    Grid* gameboard;
    void PrintBoard();
    void ResetBoard();
    void MakeMove(const int column);

    // Error checking
    
    bool ValidMove(const int column);
    std::string error_msg;
    std::string GetError();
};
