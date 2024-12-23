#include"engine.h"

using namespace std;

Chess::Chess(string fenBoard) {
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
                continue;
            } 
            else if (boardPart[i] == 'k' || boardPart[i] == 'K') { // Kings
                king[boardPart[i] == 'K'][0] = 7 - pos / 8;
                king[boardPart[i] == 'K'][1] = pos % 8;
            }
            board[7 - pos / 8][pos % 8] = boardPart[i];
            pos++;
        }
    }
}

void Chess::makeMove(string move) {
    int startRow = 8 - (move[1] - '0');
    int startCol = move[0] - 'a';
    int endRow = 8 - (move[3] - '0');
    int endCol = move[2] - 'a';
    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = ' ';
    turn = !turn;
}

int evaluate(){
    return 0;
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