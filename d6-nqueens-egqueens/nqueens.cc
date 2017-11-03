/* N Queens problem: tries to find in how many ways we
 * can map N queens to an NxN chess board in a way that
 * they cannot attack each other. Also informs each of
 * the possible mappings. */
#include <iostream>
#include <cstdint>

using namespace std;
using queen_t = size_t;
using board_t = uint*;

/* Prints the columns where each queen can be safe */
void printSolution ( queen_t n_queens, board_t board ) {
    for ( queen_t q = 0; q < n_queens; ++q )
        cout << board[q] << " ";
    cout << endl;
}

/* Checks if a queen is safe in a given position */
bool isQueenSafe ( queen_t queen, queen_t column, board_t board ) {
    // Checks all previous rows for conflicting queens
    for ( queen_t q = 0; q < queen; ++q ) {
        queen_t c = board[q];
        if (( c == column ) || // Both queens are in the same column or
            ( c == ( column - ( queen - q ) ) ) || // the same diagonal or
            ( c == ( column + ( queen - q ) ) ) )  // the same anti-diagonal
            return false;
    }
    return true;
}

/* Recursively tries to map queens to the board */
uint32_t solveNQueens ( queen_t current_queen, queen_t n_queens, board_t board ) {
    uint32_t solutions = 0;
    if ( current_queen == n_queens ) {
        // We mapped all the queens!
        solutions = 1;
#ifdef DEBUG
        printSolution ( n_queens, board );
#endif
    } else {
        // We have to check all possible columns for the queen
        for ( queen_t c = 0; c < n_queens; ++c ) {
            if ( isQueenSafe ( current_queen, c, board ) ) {
                /* This queen is safe in this position.
                 * We can leave it here and check the next
                 * row for the next queen. */
                board[current_queen] = c;
                // Place next queen
                solutions += solveNQueens ( current_queen + 1, n_queens, board );
            }
        }
    }
    // Returns the number of solutions found
    return solutions;
}

int main ( int argc, char* argv[] ) {
    /* Number of queens and size of the board */
    queen_t n_queens = 0;
    cin >> n_queens;       //gets the number of queens

    /* Board for the queens.
     * As each queen is always in the same line,
     * we do not need to store it. */
    board_t board = new uint[n_queens];

    uint32_t total_solutions = 0;
    if (n_queens > 0)
        total_solutions = solveNQueens ( 0, n_queens, board );

    cout << "Solutions = " << total_solutions << endl;

    delete[] board;
    return 0;
}
