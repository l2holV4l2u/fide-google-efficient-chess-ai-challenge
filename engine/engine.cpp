#include<iostream>
#include<string>
#include<vector>

using namespace std;

string getBestMove(string board){
    string bestMove = "e2e4";
    return bestMove;

}

void showBoard(string board){
    int rank = 8;
    cout << "    a   b   c   d   e   f   g   h\n"; // Column headers
    cout << "  +---+---+---+---+---+---+---+---+\n";
    cout << rank << " |"; // Print the rank number
    for(int i=0;i<board.length();i++){
        if(board[i] == ' '){ // End of FEN
            cout << "\n  +---+---+---+---+---+---+---+---+\n";
            return;
        }
        else if(board[i] == '/'){
            cout << "\n  +---+---+---+---+---+---+---+---+\n";
            cout << --rank << " |"; // Print the rank number
        } 
        else if(isdigit(board[i])){ // Empty squares
            for(int j=0;j<board[i] - '0';j++){
                cout << "   |";
            }
        }
        else{ // Pieces
            cout << " " << board[i] << " |";
        }
    }
}

void findMoves(string board){
    vector <string> moves;
    for(int i=0;i<board.length();i++){
        if(board[i] == ' '){ // End of FEN
            return;
        }
        else if(board[i] != '/' && !isdigit(board[i])){
            
        }
    }
}

int main(){
    bool turn = 0; // 0 for white, 1 for black
    //string board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR "; // Initial board state using FEN
    //showBoard(board);
    string board;
    while(true){
        cin >> board;
        cout << getBestMove(board) << endl;
    }
    return 0;
}