#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
// Allowed functions: getc, ungetc, printf, malloc, calloc, realloc, free, isdigit, fscanf, write

typedef struct	json {
	enum {
		MAP,
		INTEGER,
		STRING
	} type;
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;
		int	integer;
		char	*string;
	};
}	json;

typedef struct	pair {
	char	*key;
	json	value;
}	pair;

/** Given helper function */
int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

/** Given helper function */
void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

/** Given helper function */
int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

/** Given helper function */
int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return 1;
	unexpected(stream);
	return 0;
}

/** Given helper function */
void	free_json(json j)
{
	switch (j.type)
	{
		case MAP:
			for (size_t i = 0; i < j.map.size; i++)
			{
				free(j.map.data[i].key);
				free_json(j.map.data[i].value);
			}
			free(j.map.data);
			break ;
		case STRING:
			free(j.string);
			break ;
		default:
			break ;
	}
}

/** Given helper function */
void	serialize(json j)
{
	switch (j.type)
	{
		case INTEGER:
			printf("%d", j.integer);
			break ;
		case STRING:
			putchar('"');
			for (int i = 0; j.string[i]; i++)
			{
				if (j.string[i] == '\\' || j.string[i] == '"')
					putchar('\\');
				putchar(j.string[i]);
			}
			putchar('"');
			break ;
		case MAP:
			putchar('{');
			for (size_t i = 0; i < j.map.size; i++)
			{
				if (i != 0)
					putchar(',');
				serialize((json){.type = STRING, .string = j.map.data[i].key});
				putchar(':');
				serialize(j.map.data[i].value);
			}
			putchar('}');
			break ;
	}
}

/**
 * Simple wrapper for eof checking
 * Executes unexpected(), frees res & returns -1 if c is eof.
 * Returns 0 otherwise (no failure)
 */
int check_eof(int c, FILE *stream, char **res)
{
	if (c == EOF)
	{
		unexpected(stream);
		free(*res);
		return -1;
	}
	return 0;
}

/**
 * @param stream The pointer to the open FILE input stream.
 * @return A null-terminated string on success; NULL if malloc fail or an unexpected EOF.
 *
 * 1. Allocates an initial heap storage buffer with calloc.
 * 2. Consumes the initial opening double-quote character from the stream pointer.
 * 3. Enters a continuous extraction cycle:
 *    - Captures the next character token.
 *    - Passes the token to check_eof. If it fails, terminates and returns NULL.
 *    - If the token is an unescaped double-quote, breaks out of the loop.
 *    - If a backslash is encountered, calls `getc` again to grab the character immediately following it.
 *    - It passes it to check_eof to prevent cases of eof following after a backslash ("hello \)
 *    - Compares the index against current capacity. If there is no space, doubles capacity & resize using realloc.
 *    - Writes the final evaluated character byte into the array slot and increments the tracker index.
 * 4. Null-terminates the string and returns the pointer.
 */
char *get_str(FILE *stream)
{
	size_t capacity = 64;
	int i = 0;
	char *res = calloc(capacity, sizeof(char));
	if (!res)
		return NULL;
	(void)getc(stream);
	while (1)
	{
		int c = getc(stream);
		if (check_eof(c, stream, &res) == -1)
			return NULL;
		if (c == '"')
			break;
		if (c == '\\')
		{
			c = getc(stream);
			if (check_eof(c, stream, &res) == -1)
				return NULL;
		}
		if (i + 1 >= capacity)
		{
			capacity *= 2;
			char *tmp = realloc(res, capacity * sizeof(char));
			if (!tmp)
			{
				free(res);
				return NULL;
			}
			res = tmp;
		}
		res[i++] = c;
	}
	res[i] = '\0';
	return res;
}

/** Expands the map data array memory allocation dynamically. */
static int grow_map_data(json *dst)
{
	pair *tmp = realloc(dst->map.data, (dst->map.size + 1) * sizeof(pair));
	if (!tmp)
	{
		free_json(*dst);
		return -1;
	}
	dst->map.data = tmp;
	return 0;
}

int argo(json *dst, FILE *stream); // Forward declaration

/**
 * @param dst Pointer to the target destination JSON structure to hold the map key-value pair.
 * @param stream The pointer to the open FILE input stream.
 * @param current The current pair.
 *
 * 1. Peeks at the next token. If it is not a double-quote, print error msg & return -1.
 * 2. Executes get_str() to get map key. Initate cleanup if NULL.
 * 3. Executes expect() to verify & consume the colon delimiter. Initate cleanup if 0.
 * 4. Recursively passes the child node value pointer back to argo(). Initate cleanup if -1.
 * 5. Initate cleanup if any function from steps 2-4 returns a failure code.
 * 6. Increment the map size by 1 and return 0.
 */
static int parse_pair(json *dst, FILE *stream, pair *current)
{
	if (peek(stream) != '"')
	{
		unexpected(stream);
		free_json(*dst);
		return -1;
	}
	current->key = get_str(stream);
	if (current->key == NULL || expect(stream, ':') == 0 || argo(&current->value, stream) == -1)
	{
		if (current->key != NULL)
			free(current->key);
		free_json(*dst);
		return -1;
	}
	dst->map.size++;
	return 0;
}

/**
 * 1. Peeks ahead after processing a complete pair block.
 * 2. If it sees a closing brace, consumes it with accept() & returns 0.
 * 3. If it sees a comma, consumes it with accept() & returns 1.
 * 4. If it encounters any other token, cleanup, print error msg & return -1.
 */
static int handle_map_delimiters(json *dst, FILE *stream)
{
	int c = peek(stream);
	if (c == '}')
	{
		accept(stream, c);
		return 0;
	}
	if (c == ',')
	{
		accept(stream, c);
		return 1;
	}
	unexpected(stream);
	free_json(*dst);
	return -1;
}

/**
 * @param dst Pointer to the target destination JSON structure to hold the map data array.
 * @param stream The pointer to the open FILE input stream.
 * @return Returns 1 on succes; returns -1 for syntax or malloc errors.
 *
 * 1. Initalizes dst with the map type, 0 size & NULL data.
 * 2. Consumes the opening brace.
 * 3. Peeks ahead at the next token. If it matches a closing brace, return 1.
 * 4. Loops continuously to extract dictionary elements:
 *    - Handles allocation for a new pair element with grow_map_data.
 *    - Parses the current pair using parse_pair.
 *    - Handles map delimiters with handle_map_delimiters.
 *    - If it returns 0, break. If it returns -1, return -1.
 * 5. Returns 1 when the loop exits.
 */
int parse_map(json *dst, FILE *stream)
{
	dst->type = MAP;
	dst->map.size = 0;
	dst->map.data = NULL;
	(void)getc(stream);

	if (accept(stream, '}'))
		return 1;

	while (1)
	{
		if (grow_map_data(dst) == -1)
			return -1;
		pair *current = &dst->map.data[dst->map.size];
		if (parse_pair(dst, stream, current) == -1)
			return -1;
		int delimiter_status = handle_map_delimiters(dst, stream);
		if (delimiter_status == 0)
			break;
		if (delimiter_status == -1)
			return -1;
	}
	return 1;
}

/** Simple integer extraction with fscanf */
void    parse_int(json *dst, FILE *stream)
{
	int n = 0;

	fscanf(stream, "%d", &n);
	dst->type = INTEGER;
	dst->integer = n;
}

/**
 * @param dst Pointer to the JSON structure.
 * @param stream The pointer to the open FILE input stream.
 * @return Returns 1 on success, or -1 if invalid syntax.
 *
 * 1. Gets the next char with peek.
 * 2. If the char is EOF, print err msg & return -1.
 * 3. Compares the token against structural type flags:
 * - If it is a digit, execute parse_int to handle the integer.
 * - If it matches a double-quote, updates the type to string and uses get_str to get the string.
 * - If it matches an opening brace, executes parse_map() to parse the key in the json structure.
 * 4. If it isn't any of the above, prints err msg & returns -1.
 */
int argo(json *dst, FILE *stream)
{
	int c = peek(stream);

	if (c == EOF)
	{
		unexpected(stream);
		return -1;
	}
	if (isdigit(c))
	{
		parse_int(dst, stream);
		return 1;
	}
	if (c == '"')
	{
		dst->type = STRING;
		dst->string = get_str(stream);
		if (dst->string == NULL)
			return (-1);
		return 1;
	}
	if (c == '{')
		return (parse_map(dst, stream));
	unexpected(stream);
	return -1;
}
