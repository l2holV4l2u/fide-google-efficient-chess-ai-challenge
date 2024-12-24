#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include "engine.h"
#include "chess.cpp"
#include "movegen.cpp"

using namespace std;

int main() {
    string input;
    /*
    srand(static_cast<unsigned int>(time(nullptr)));
    while (input != "q") {
        getline(cin, input);
        Chess chess(input);
        vector <string> moves = findAllMoves(chess);
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
    */
    getline(cin, input);
    Chess chess(input);
    vector <string> moves = findAllMoves(chess);
    Chess newchess = chess.makeMove(moves[0]);
    chess.showBoard();
    cout << "-------------------" << endl;
    cout << moves[0] << endl;
    cout << "-------------------" << endl;
    newchess.showBoard();
    return 0;
}