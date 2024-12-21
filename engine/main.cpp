#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include "engine.h"
#include "chess.cpp"
#include "move.cpp"

using namespace std;

int main() {
    bool turn = 0; // 0 for white, 1 for black
    string input;
    srand(static_cast<unsigned int>(time(nullptr)));
    while (input != "q") {
        getline(cin, input);
        Chess chess(input);
        vector <string> moves = findMoves(chess);
        if (!moves.empty()) {
            // Pick a random index from the moves vector
            int randomIndex = rand() % moves.size();
            cout << moves[randomIndex] << endl;
        } 
        else {
            cout << "No valid moves available." << endl;
            break;
        }
    }
    return 0;
}
