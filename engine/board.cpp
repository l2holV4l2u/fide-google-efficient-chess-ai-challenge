#include"engine.h"

using namespace std;

Board::Board(const string& fenBoard) {
    fen = fenBoard;
    string boardPart = fenBoard.substr(0, fenBoard.find(" ")), temp = "";
    turn = fenBoard[fenBoard.find(" ") + 1] == 'w';
    for (int i = 0; i < boardPart.length(); i++) {
        if (boardPart[i] != '/') {
            if (isdigit(boardPart[i])) { // Empty squares
                for (int j = 0; j < boardPart[i] - '0'; j++) {
                    temp += " ";
                }
            } else { // Pieces
                temp += boardPart[i];
            }
        }
        else {
            sn = temp + sn;
            temp = "";
        }
    }
    sn = temp + sn;
}

void Board::showBoard() const {
    int rank = 8;
    cout << "    a   b   c   d   e   f   g   h\n"; // Column headers
    cout << "  +---+---+---+---+---+---+---+---+\n";
    cout << rank << " |"; // Print the rank number

    for (int i = 0; i < fen.length(); i++) {
        if (fen[i] == ' ') { // End of FEN
            cout << "\n  +---+---+---+---+---+---+---+---+\n";
            return;
        } else if (fen[i] == '/') {
            cout << "\n  +---+---+---+---+---+---+---+---+\n";
            cout << --rank << " |"; // Print the rank number
        } else if (isdigit(fen[i])) { // Empty squares
            for (int j = 0; j < fen[i] - '0'; j++) {
                cout << "   |";
            }
        } else { // Pieces
            cout << " " << fen[i] << " |";
        }
    }
}
