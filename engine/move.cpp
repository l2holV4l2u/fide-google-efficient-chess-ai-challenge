#include "engine.h"

bool side; // 0 for black, 1 for white
vector <string> moves;
Chess chess("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

string algebraicNotation(int row, int col) {
    return string(1, 'a' + col) + string(1, '1' + row);
}

bool outOfBound(int row, int col) {
    return row < 0 || row >= 8 || col < 0 || col >= 8;
}

bool pushValid(int currow, int curcol, int nextrow, int nextcol) { // Use reference for moves and board
    if (outOfBound(nextrow, nextcol)) return true; // Stop further moves in this direction
    char target = chess.board[nextrow][nextcol];
    // for capture - || islower(target) != islower(chess.board[currow][curcol])
    if (target == ' ' ) { // Empty square
        moves.push_back(algebraicNotation(currow, curcol) + algebraicNotation(nextrow, nextcol));
        return target == ' '; // Continue in this direction
    }
    return true; // Stop further moves
}

void findKnightMoves(int row, int col) {
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            pushValid(row, col, row + 2 * i, col + 1 * j);
            pushValid(row, col, row + 1 * i, col + 2 * j);
        }
    }
}

void findPawnMoves(int row, int col) {
    int forward = (side ? 1 : -1);
    pushValid(row, col, row + forward, col); // Forward move
    if ((!side && row == 6 && chess.board[row - 1][col] == ' ') || (side && row == 1 && chess.board[row + 1][col] == ' ')) { // Initial double move
        pushValid(row, col, row + 2 * forward, col);
    }
}

void findBishopMoves(int row, int col) {
    for (int i = -1; i <= 1 ; i += 2){
        for (int j = -1; j <= 1; j += 2){
            for (int k = 1; k <= 8; k++){
                if (pushValid(row, col, row + k * i, col + k * j)) break;
            }
        }
    }
}

void findRookMoves(int row, int col) {
    int direction[4] = {-1, 1, 0, 0};
    for (int i = 0; i < 4 ; i ++){
        for (int j = 1; j <= 8; j++){
            if (pushValid(row, col, row + j * direction[i], col + j * direction[3-i])) break;
        }
    }
}


void findQueenMoves(int row, int col) {
    findRookMoves(row, col);
    findBishopMoves(row, col);
}

void findKingMoves(int row, int col) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            pushValid(row, col, row + i, col + j);
        }
    }
}

// gives all possible moves for the current side in UCI notation
vector <string> findMoves(Chess& localchess) {
    moves.clear();
    chess = localchess;
    side = chess.turn;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (chess.board[i][j] == ' ' || isupper(chess.board[i][j]) != side) continue; // Skip empty squares & opponent's pieces
            char piece = tolower(chess.board[i][j]);
            if(piece == 'n') findKnightMoves(i, j);
            else if(piece == 'p') findPawnMoves(i, j);
            else if(piece == 'b') findBishopMoves(i, j);
            else if(piece == 'r') findRookMoves(i, j);
            else if(piece == 'q') findQueenMoves(i, j);
            else if(piece == 'k') findKingMoves(i, j);
        }
    }
    return moves;
}