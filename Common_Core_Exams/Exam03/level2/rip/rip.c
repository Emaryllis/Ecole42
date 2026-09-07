#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_state {
	int rem; // total parentheses left to remove
	int bal; // current balance
} t_state;

/** Checks if the string is balanced st.bal == 0 && st.rem == 0
 * isn't sufficient since cases like ')()(' could occur. Checking
 * the updated balance after each iteration to be sure.
 */
bool is_balanced(char *s) {
	int balance = 0;

	for (int i = 0; s[i]; i++) {
		if (s[i] == '(')
			balance++;
		else if (s[i] == ')')
			balance--;
		if (balance < 0)
			return false;
	}
	return (balance == 0);
}

/** Taking advantage that the ascii values of () are
 * side by side, we can either use bitwise operators
 * or ternary statements to determine if we should
 * increment or decrement the balance. A positive
 * balance means more '(' than ')' and vice versa.
 */
void backtrack(char *s, int len, int i, t_state st) {
	if (i == len) {
		// Goal state: reached EOL and is balanced
		if (st.bal == 0 && st.rem == 0 && is_balanced(s))
			puts(s);
		return;
	}

	// Choice: Try removing current parenthesis
	if (st.rem > 0) {
		char tmp = s[i];
		s[i] = ' ';
		backtrack(s, len, i + 1, (t_state){st.rem - 1, st.bal});
		s[i] = tmp;
	}

	// Choice: Try leaving it as-is & add to bal
	/* '(' as 1, ')' as -1
	 * You can use this if you prefer a cleaner bitwise option:
	 * int delta = 1 - (c & 1) * 2;
	 */
	int delta = s[i] == '(' ? 1 : -1;
	backtrack(s, len, i + 1, (t_state){st.rem, st.bal + delta});
}

/** Precompute minimal total removals needed
 * @returns true if invalid character found, false otherwise
 */
bool compute_rem(char *s, int len, t_state *st) {
	st->rem = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '(')
			st->rem++;
		else if (s[i] == ')')
			st->rem > 0 ? st->rem-- : st->rem++;
		else
			return true;
	}
	return false;
}

/* ======================= Backtracking =======================
 * - Parsing: Handled by argc/argv
 * - Error Handling: Lines 86-87 & handled by compute_rem()
 * - Initializing: Lines 89-95, 101
 * - Goal State: Lines 37-38
 * - Make Choice: Lines 43-46, 55-56
 * - Validation/Pruning: Lines 35 & 39
 * - Backtrack (Undo Choice): Line 47
 * ============================================================
 */
int main(int argc, char **argv) {
	if (argc != 2 || argv[1][0] == '\0')
		return EXIT_FAILURE;

	char *s = argv[1];
	int len = 0;
	while (s[len])
		len++;

	t_state st;
	if (compute_rem(s, len, &st))
		return EXIT_FAILURE;
	if (st.rem == 0 && is_balanced(s)) {
		puts(s);
		return EXIT_SUCCESS;
	}
	st->bal = 0;

	backtrack(s, len, 0, st);

	return EXIT_SUCCESS;
}
