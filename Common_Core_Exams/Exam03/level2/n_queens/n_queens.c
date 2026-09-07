#include <stdio.h>
#include <stdlib.h>

int ft_abs(int a) {
	return (a < 0) ? -a : a;
}

// Check if it's safe to place a queen at row, col
int is_valid(int *board, int row, int col) {
	for (int prev_row = 0; prev_row < row; prev_row++) {
		int prev_col = board[prev_row];
		
		// If same column as previous columns or is diagonal to any
		if (prev_col == col || ft_abs(prev_col - col) == ft_abs(prev_row - row)) {
			return 0;
		}
	}
	return 1;
}

void solve_n_queens(int *board, int row, int n) {
	if (row == n) { // Goal state: all queens placed
		for (int i = 0; i < n; i++) {
			fprintf(stdout, "%d ", board[i]);
		}
		fprintf(stdout, "\n");
		return;
	}

	for (int col = 0; col < n; col++) { // Choice: each column in this row
		if (is_valid(board, row, col)) {
			board[row] = col;           // Make choice
			solve_n_queens(board, row + 1, n);
			board[row] = -1;            // Undo choice
		}
	}
}
/* ======================= Backtracking =======================
 * - Parsing: Handled by argc/argv
 * - Error Handling: Lines 51-58
 * - Initalizing: Lines 61-66
 * - Goal State: Lines 23-29
 * - Make Choice: Line 33
 * - Validation/Pruning: is_valid() function (Lines 10-20)
 * - Backtrack (Undo Choice): Line 34-35
 * ============================================================
 */
int main(int c, char **v) {
	// Error handling
	if (c != 2)
		return EXIT_FAILURE;
	char *tmp = v[1];
	while (tmp && *tmp) {
		if (*tmp < '0' || *tmp > '9')
			return EXIT_FAILURE;
		tmp++;
	}

	// Initalize board with -1
	int n = atoi(v[1]);

	// Print nl for n = 0, 2, 3
	if (n < 4 && n != 1)
		return write(1, "\n", 1), EXIT_SUCCESS
	
	int *board = (int *)malloc(n * sizeof(int));
	if (!board)
		return EXIT_FAILURE;
	for (int i = 0; i < n; i++)
		board[i] = -1;

	solve_n_queens(board, 0, n);

	free(board);
	return EXIT_SUCCESS;
}
