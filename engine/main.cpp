#include"engine.h"
#include"board.cpp"
#include"move.cpp"

using namespace std;

int main(){
    bool turn = 0; // 0 for white, 1 for black
    string initialBoard = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w"; // Initial board state using FEN
    Board board(initialBoard);
    board.showBoard();
    //cout << board.sn << endl;
    vector <string> moves = findMoves(board);
    cout<< board.sn << endl;
    for(auto move:moves){
        cout << move << endl;
    }
    cout<< moves.size() << endl;
    return 0;
}