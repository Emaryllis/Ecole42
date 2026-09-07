#include "vbc.h"

/**
 * @param c Token to be displayed.
 * @return 1 always, to indicate an error, and
 * to avoid comma abuse from caller.
 *
 * This function is given as a void function.
 * Static is also added.
 */
static int unexpected(unsigned char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of file\n");
	return 1; // Added to given function
}

/**
 * @param c Current token
 * @param n Next token
 * @param b_bal Balance of braces
 * @return 1 if invalid, 0 otherwise.
 *
 * Used to handle and check if the braces are balanced.
 * (b_bal must be >= 0 at all times) If not, it throws
 * an unexpected err msg.
 */
static int handle_braces(unsigned char c, unsigned char n, int *b_bal)
{
	if (c == '(')
		(*b_bal)++;
	else if (c == ')')
		(*b_bal)--;
	if ((c == '(' && n == ')') || *b_bal < 0)
		return unexpected(')');
	return 0;
}

/**
 * @param s Expr str to check against.
 * @return 1 if invalid, 0 otherwise.
 *
 * Note: It uses unsigned char instead of char for portability.
 * 1. Track parentheses balance in b_bal, iterate through characters with index i.
 * 2. For each current token c and next token n:
 *    - Update/validate parentheses: '(' increments b_bal, ')' decrements it.
 *    - Reject empty parentheses '()'.
 *    - Reject an extra closing parenthesis when b_bal becomes negative.
 *    - Only digits, '+', '*', '(' and ')' are valid tokens.
 *    - Integers must be single-digit: reject two consecutive digits.
 *    - If current token is '+' or '*', the next token can't be '+', '*', ')', or NUL.
 *      (i.e., after an operator you must have a digit or '(').
 *    - If current token is '(', the next token must not be ')' (no empty parentheses).
 * 3. After each iteration, increments index, updates last & c.
 * 4. After the loop, returns an unexpected err msg if:
 *    - There are unbalanced braces. (b_bal > 0)
 *    - The last token is an operator.
 * 5. Return 0 since the expr is valid.
 *
 * Short explanation for exam:
 * 1. Init b_bal for brace bal, i for index, last for eof, c for token.
 * 2. Each iter through the expr loop, check:
 *    - Balanced braces.
 *    - Token is a single digit int.
 *    - If current is '+', '*', next token can't be '+', '*', ')', or EOF.
 *    - Next token isn't ')' if current is '('.
 * 3. After every iter, ↑ index, update last & c.
 * 4. After loop, return unexpected err if b_bal > 0 or last is '+' or '*'.
 * 5. Return 0 since expr is valid.
 */
int check_input(char *s)
{
	int b_bal = 0;
	int i = 0;
	unsigned char last = 0;
	unsigned char c = s[i];
	while (c) {
		unsigned char n = s[i + 1];
		if (handle_braces(c, n, &b_bal))
			return 1;
		if (isdigit(c)) {
			if (n && isdigit(n))
				return unexpected(n);
		} else if (c == '+' || c == '*') {
			if (n == '+' || n == '*' || n == ')' || n == '\0')
				return unexpected(n ? n : 0);
		} else if (c != '(' && c != ')')
			return unexpected(c);
		last = c;
		c = s[++i];
	}
	if (b_bal > 0 || last == '+' || last == '*' || last == '(')
		return unexpected(0);
	return 0;
}