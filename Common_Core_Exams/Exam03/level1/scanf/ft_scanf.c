#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
// Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end

/** Skips whitespace characters in the file. */
int match_space(FILE *f) {
	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	while (isspace(c))
		c = fgetc(f);
	if (c != EOF)
		ungetc(c, f);
	return 1;
}

/** Checks if character is not EOF and stores it.
 * @return 1 on success, 0 on EOF.
 */
int scan_char(FILE *f, va_list ap) {
	char *p = va_arg(ap, char *);
	int c = fgetc(f);
	if (c == EOF)
		return 0;
	*p = c;
	return 1;
}

/** Essentially recreating atoi but instead of
 * a string it reads from a file. It returns a
 * code rather than the result which is stored.
 * @returns 1 on success, 0 on failure/EOF.
 */
int scan_int(FILE *f, va_list ap) {
	int c = fgetc(f);
	int sign = 1;
	if (c == '+' || c == '-') {
		sign = c == '-' ? -1 : 1;
		c = fgetc(f);
	}

	if (c == EOF || !isdigit(c)) {
		if (c != EOF) ungetc(c, f);
		return 0;
	}

	long val = 0;
	while (isdigit(c)) {
		val = val * 10 + (c - '0');
		c = fgetc(f);
	}

	if (c != EOF)
		ungetc(c, f);

	int *p = va_arg(ap, int *);
	*p = val * sign;
	return 1;
}

/** Converts any characters that isn't whitespaces
 * or EOF into a string and stores it.
 * @returns 1 on success, 0 on failure/EOF.
 */
int scan_string(FILE *f, va_list ap) {
	char *p = va_arg(ap, char *);
	char *start = p;

	int c = fgetc(f);
	while (c != EOF && !isspace(c)) {
		*p++ = c;
		c = fgetc(f);
	}
	*p = '\0';

	if (c != EOF)
		ungetc(c, f);

	return p > start ? 1 : 0;
}

/** Simple switch statement to match conversion specifiers */
int match_conv(FILE *f, const char **format, va_list ap) {
	switch (**format) {
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

/** Matches a specific character in the file.
 * @return boolean indicating match success, or EOF.
 */
int match_char(FILE *f, char c) {
	int r = fgetc(f);
	if (r == EOF)
		return EOF;
	if (r == c)
		return 1;
	ungetc(r, f);
	return 0;
}

/** Check for eof at the start, then it tries to map the
 * stream to its format specifiers with *format == '%'.
 * Any whitespace in the format string are skipped. For
 * those not '%' or a whitespace character, it falls back
 * to matching a specific character and exits on failure.
 * @return number of successful conversions, or EOF on error.
 */
int ft_vfscanf(FILE *f, const char *format, va_list ap) {
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format) {
		if (*format == '%') {
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			nconv++;
		} else if (isspace(*format)) {
			if (match_space(f) == EOF)
				break;
		} else if (match_char(f, *format) != 1)
			break;
		format++;
	}

	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
