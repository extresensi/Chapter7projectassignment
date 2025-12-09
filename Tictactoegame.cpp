/*
------------------------------------------------------------
Program: Tic-Tac-Toe Game
Author: Charles Duncan
Date: December 2025
Description:
    This program allows two players to play Tic-Tac-Toe.
    The board is represented by a 3x3 char array initialized
    with '*'. Players alternate placing 'X' and 'O' until
    one wins or the game ends in a tie.

Preconditions:
    - Players enter row and column numbers between 1 and 3.
    - Players cannot place a token in an occupied cell.

Postconditions:
    - Displays board after each move.
    - Declares winner or tie when game ends.
------------------------------------------------------------
*/

#include <iostream>
using namespace std;

// Constants
const int SIZE = 3;
const char EMPTY = '*';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

// Function Prototypes
void initializeBoard(char board[SIZE][SIZE]);
void displayBoard(const char board[SIZE][SIZE]);
void placeToken(char board[SIZE][SIZE], char token);
void getLocation(int& row, int& col, const char board[SIZE][SIZE]);
bool checkForWinner(const char board[SIZE][SIZE], char token);
bool isBoardFull(const char board[SIZE][SIZE]);

int main() {
    char board[SIZE][SIZE];
    initializeBoard(board);

    cout << "Welcome to Tic-Tac-Toe!" << endl;
    displayBoard(board);

    bool gameOver = false;
    char currentPlayer = PLAYER1;

    while (!gameOver) {
        placeToken(board, currentPlayer);
        displayBoard(board);

        if (checkForWinner(board, currentPlayer)) {
            cout << "Player " << (currentPlayer == PLAYER1 ? "1 (X)" : "2 (O)") 
                 << " wins!" << endl;
            gameOver = true;
        } else if (isBoardFull(board)) {
            cout << "It's a tie!" << endl;
            gameOver = true;
        } else {
            // Switch players
            currentPlayer = (currentPlayer == PLAYER1 ? PLAYER2 : PLAYER1);
        }
    }

    return 0;
}

/*
------------------------------------------------------------
Function: initializeBoard
Purpose: Sets all cells in the board to '*'
------------------------------------------------------------
*/
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

/*
------------------------------------------------------------
Function: displayBoard
Purpose: Prints the board with row/column numbers
------------------------------------------------------------
*/
void displayBoard(const char board[SIZE][SIZE]) {
    cout << "\n   1   2   3" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) cout << "|";
        }
        cout << endl;
        if (i < SIZE - 1) cout << "  ---+---+---" << endl;
    }
    cout << endl;
}

/*
------------------------------------------------------------
Function: placeToken
Purpose: Places a token at a valid location
------------------------------------------------------------
*/
void placeToken(char board[SIZE][SIZE], char token) {
    int row, col;
    getLocation(row, col, board);
    board[row][col] = token;
}

/*
------------------------------------------------------------
Function: getLocation
Purpose: Gets valid row/col input from user
------------------------------------------------------------
*/
void getLocation(int& row, int& col, const char board[SIZE][SIZE]) {
    bool valid = false;
    while (!valid) {
        cout << "Enter row (1-3): ";
        cin >> row;
        cout << "Enter column (1-3): ";
        cin >> col;

        // Convert to 0-based index
        row--; col--;

        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
            if (board[row][col] == EMPTY) {
                valid = true;
            } else {
                cout << "Cell already occupied. Try again." << endl;
            }
        } else {
            cout << "Invalid input. Try again." << endl;
        }
    }
}

/*
------------------------------------------------------------
Function: checkForWinner
Purpose: Checks rows, columns, and diagonals for a win
------------------------------------------------------------
*/
bool checkForWinner(const char board[SIZE][SIZE], char token) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == token && board[i][1] == token && board[i][2] == token)
            return true;
    }
    // Check columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == token && board[1][j] == token && board[2][j] == token)
            return true;
    }
    // Check diagonals
    if (board[0][0] == token && board[1][1] == token && board[2][2] == token)
        return true;
    if (board[0][2] == token && board[1][1] == token && board[2][0] == token)
        return true;

    return false;
}

/*
------------------------------------------------------------
Function: isBoardFull
Purpose: Checks if all cells are filled
------------------------------------------------------------
*/
bool isBoardFull(const char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) return false;
        }
    }
    return true;
}
