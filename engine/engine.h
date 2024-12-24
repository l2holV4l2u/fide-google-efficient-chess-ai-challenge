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
    int king[2][2]; // position of the kings

    Chess(string fenBoard);
    Chess makeMove(string move);
    void showBoard() const;
    int evaluate();
};

// Function declaration for finding moves
vector <string> findAllMoves(Chess& localchess);

string findBestMove(Chess& localchess);

#endif // ENGINE_H