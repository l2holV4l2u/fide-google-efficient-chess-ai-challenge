#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Board {
public:
    string sn;  // String notation of the board
    string fen; // FEN representation of the board
    bool turn; // 0 for black, 1 for white

    // Constructor declaration (using `const string&` for efficiency and consistency)
    Board(const string& fenBoard);
    void showBoard() const;
};

// Function declaration for finding moves
vector <string> findMoves(const Board& board);

#endif // ENGINE_H