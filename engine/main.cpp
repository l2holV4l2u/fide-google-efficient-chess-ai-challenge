#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include "engine.h"
#include "board.cpp"
#include "move.cpp"

using namespace std;

int main() {
    bool turn = 0; // 0 for white, 1 for black
    string initialBoard = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w"; // Initial board state using FEN
    string input;
    srand(static_cast<unsigned int>(time(nullptr)));
    while (input != "q") {
        getline(cin, input);
        if (input == "q") {
            break;
        }
        Board board(input);
        vector<string> moves = findMoves(board);
        if (!moves.empty()) {
            // Pick a random index from the moves vector
            int randomIndex = rand() % moves.size();
            cout << moves[randomIndex] << endl;     
        }
    }
    return 0;
}
