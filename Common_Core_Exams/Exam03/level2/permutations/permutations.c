#include <unistd.h> // write
#include <stdio.h> // puts
#include <stdlib.h> // malloc, free
// Allowed functions: puts, malloc, calloc, realloc, free, write

static void bsort(char *s, int len) {
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (s[j] > s[j + 1]) {
				char tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
		}
	}
}

// Recursive permutation function using a "used" boolean array
static void permute(char *s, int len, char *curr, int depth, int *used) {
	// Backtrack: Goal state
	if (depth == len) {
		curr[len] = '\0';
		puts(curr);
		return;
	}

	for (int i = 0; i < len; i++) {
		if (!used[i]) {
			// Backtrack: Is valid
			// Backtrack: Choice
			used[i] = 1;
			curr[depth] = s[i];

			permute(s, len, curr, depth + 1, used); // Backtrack: Explore
			used[i] = 0; // Backtrack: Un-choose
		}
	}
}

/* ======================= Backtracking =======================
 * - Parsing: Handled by argc/argv
 * - Error Handling: Lines 50-59
 * - Initializing: Lines 64-71
 * - Goal State: Lines 21-25
 * - Make Choice: Lines 31-32
 * - Validation/Pruning: Line 28
 * - Backtrack (Undo Choice): Lines 34-35
 * ============================================================
 */
int main(int argc, char **argv) {
	if (argc != 2 || argv[1][0] == '\0')
		return 0;

	char *s = argv[1];
	int len = 0;
	while (s[len]) {
		if (s[len] < 'A' || (s[len] > 'Z' && s[len] < 'a') || s[len] > 'z')
			return 0;
		len++;
	}

	bsort(s, len);

	char *curr = malloc(len + 1);
	if (!curr)
		return 1;
	int *used = calloc(len, sizeof(int));
	if (!used) {
		free(curr);
		return 1;
	}

	permute(s, len, curr, 0, used);

	free(curr);
	free(used);
	return 0;
}
