#include"engine.h"

using namespace std;

Chess::Chess(const string& fenBoard) {
    fen = fenBoard;
    string boardPart = fenBoard.substr(0, fenBoard.find(" "));
    int pos = 0;
    turn = fenBoard[fenBoard.find(" ") + 1] == 'w';
    for (int i = 0; i < boardPart.length(); i++) {
        if (boardPart[i] != '/') {
            if (isdigit(boardPart[i])) { // Empty squares
                for (int j = 0; j < boardPart[i] - '0'; j++) {            
                    board[7 - pos / 8][pos % 8] = ' ';
                    pos++;
                }
            } 
            else { // Pieces        
                board[7 - pos / 8][pos % 8] = boardPart[i];
                pos++;
            }
        }
    }
}

void Chess::showBoard() const {
    cout << "    a   b   c   d   e   f   g   h\n"; // Column headers
    cout << "  +---+---+---+---+---+---+---+---+\n";
    for (int i = 7; i >= 0; i--) {
        cout << i + 1 << " |"; // Print the rank number
        for (int j = 0; j < 8; j++) {
            cout << " " << board[i][j] << " |";
        }
        cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }
}
