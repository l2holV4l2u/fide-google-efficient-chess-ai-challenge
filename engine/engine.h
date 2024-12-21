#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Chess {
public:
    char board[8][8]; // 2D array to store the board
    string fen; // FEN representation of the board
    bool turn; // 0 for black, 1 for white

    // Constructor declaration (using `const string&` for efficiency and consistency)
    Chess(const string& fenBoard);
    void showBoard() const;
};

// Function declaration for finding moves
vector <string> findMoves(const Chess& chess);

#endif // ENGINE_H