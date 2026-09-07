#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
// realloc, free, printf, fprintf, stdout, stderr, perror

#define READ_SIZE 4096

/** Reads all data READ_SIZE bytes at a time from stdin.
 * It expands the result buffer using realloc after each read.
 * The bytes read are appended to the result buffer.
 * @param eof_out Set to EOF if no data was read before EOF.
 * @returns NULL for EOF/Mem alloc error, buffer w/ data otherwise.
 */
static char *read_filter(int *eof_out) {
	char r_buf[READ_SIZE];
	char *result = NULL;
	size_t total_bytes = 0;
	ssize_t bytes; // Requires signed type since read can return -1 on error

	while ((bytes = read(STDIN_FILENO, r_buf, READ_SIZE)) > 0) {
		// Safe cast because bytes > 0, +1 for NULL terminator
		char *f_buf = realloc(result, total_bytes + (size_t) bytes + 1);
		if (!f_buf) {
			perror("realloc");
			return free(result), NULL;
		}

		result = f_buf;

		// Could use memcpy for faster performance since no
		// overlap, but memcpy isn't in the allowed functions
		memmove(result + total_bytes, r_buf, (size_t) bytes);
		total_bytes += (size_t) bytes;
		result[total_bytes] = '\0';
	}

	// bytes < 0 -> r_buf == NULL -> mem error -> free result (if any)
	if (bytes < 0) {
		perror("read");
		return free(result), NULL;
	}
	if (!result) {
		*eof_out = EOF;
		return NULL;
	}
	return result;
}

/** Checks the buffer for occurrences of target using memmem.
 * If not found, writes the remaining buffer. If found, get
 * the position of the match, writes everything before it,
 * then writes '*' for each character in target. It then
 * continues searching after skipping the matched substring.
 */
static void ft_filter(char *buffer, const char *target) {
	size_t t_len = strlen(target);
	size_t b_len = strlen(buffer);

	size_t i = 0;

	while (i < b_len) {
		void *hit = memmem(buffer + i, b_len - i, target, t_len);
		if (!hit) {
			// No more matches. Write remaining content.
			write(STDOUT_FILENO, buffer + i, b_len - i);
			break;
		}

		size_t hit_pos = (char *) hit - buffer;

		// Write everything before the match
		if (hit_pos > i)
			write(STDOUT_FILENO, buffer + i, hit_pos - i);

		// Write '*', could use a buffer for '*', then write all at
		// once to reduce syscalls, but this is exam not prod code
		for (size_t k = 0; k < t_len; k++)
			write(STDOUT_FILENO, "*", 1);

		// Skip the matched substring
		i = hit_pos + t_len;
	}
}

int main(int argc, char **argv) {
	if (argc != 2 || argv[1][0] == '\0')
		return 1;

	int eof_out = 0;
	char *result = read_filter(&eof_out);
	if (eof_out == EOF)
		return 0;
	if (!result)
		return 1;

	ft_filter(result, argv[1]);

	free(result);
	return 0;
}
