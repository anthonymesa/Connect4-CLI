/*
 * Project: Connect4
 * 
 * File: Board Class
 * Author: Anthony Mesa
 * Date: 03-26-21
 */

#include <vector>
#include <string>

class Board{

public:

    // Constructor/Destructor

    Board(const int board_size_x, const int board_size_y);
    ~Board();

    // Mandatory

    enum Player { NONE, RED, YELLOW };
    typedef std::vector<std::vector<Player>> Grid;

    Player current_turn;
    bool win;
    Grid* gameboard;

    void PrintBoard();
    bool CheckWin();
    Player NextTurn();
    void ResetBoard();

    // Extra

    int height, width;
    std::string error_msg;
    bool error;

    void SetPlayerMove(const Player player_piece, const int column);
    int GetPlayerMove(const std::string msg);
    const char* GetPiece(const Player player_number);
    bool ValidMove(const int column);
    void PromptRestart();
};
