#include "get_next_line.h"
// Allowed functions: read, free, malloc

/* Old ft_strchr:
 * Did not checking if s is NULL and if c
 * is not in s, it will segfault due to
 * invalid read.
 *
 * The function just searches for the first
 * occurrence of character c in string s
 * and returns a pointer to it, or NULL if
 * not found. This also protects the gnl
 * function from crashing when the static
 * variable is NULL in this case.
 *
 *	char *ft_strchr(char *s, int c)
 *	{
 *	  int i = 0;
 *	  while(s[i] != c)
 *	    i++;
 *	  if (s[i] == c)
 *	    return s + i;
 *	  else
 *	    return NULL;
 *	}
 */
char *ft_strchr(char *s, int c) {
	int i = 0;

	if (!s)
		return (NULL);
	while (s[i]) {
		if (s[i] == (char) c)
			return s + i;
		i++;
	}
	return (NULL);
}

/* Old ft_memcpy:
 *
 *	void *ft_memcpy(void *dest, const void *src, size_t n)
 *	{
 *	  while(--n > 0)
 *		((char *)dest)[n - 1] = ((char *)src)[n - 1];
 *	  return dest;
 *	}
 *
 * The mistake is that it doesn't copy the first byte
 * since when the while loop reaches 0, it exits without
 * copying the byte at index 0. Decrementing n when it is
 * at 0 will make it a very large size_t value, leading
 * to out-of-bounds access.
 *
 * The function just copies n bytes from src to
 * dest using a simple loop. No checking needed
 * since it is considered an unsafe function.
 */
void *ft_memcpy(void *dest, const void *src, size_t n) {
	while (n > 0) {
		n--;
		((char *) dest)[n] = ((char *) src)[n];
	}
	return (dest);
}

/* Old ft_strlen:
 * The mistake was incrementing s instead
 * of using a separate counter variable.
 *
 * The function just calculates the length
 * of the string by iterating through each
 * character until it reaches the NULL character.
 *
 *	size_t ft_strlen(char *s)
 *	{
 *	  size_t res = 0;
 *	  while (*s)
 *	  {
 *		s++;
 *		res++;
 *	  }
 *	  return res;
 *	}
 */
size_t ft_strlen(char *s) {
	size_t res = 0;
	if (!s)
		return 0;
	while (s[res])
		res++;
	return (res);
}

/* Old ft_memmove:
 * The mistake was calling ft_memmove recursively without changing
 * anything that leads to infinite recursion in the first two lines.
 * When checking dest == src, it missed checking if n == 0 as well.
 *
 * An alternative approach is to change the while loop condition from
 * i >= 0 to i > 0 so that it skips the while loop when i is 0 and
 * directly returns 0, but the former method is more readable.
 *
 * Another mistake is not checking if src is NULL before calling
 * ft_strlen since it would return 0 and the additional -1 would
 * make it a very large size_t value, leading to out-of-bounds
 * access in the while loop.
 *
 * Since we need to copy n bytes and is not sure if dest
 * or src is larger, duplicating the pointers and leaving
 * the original intact is the easiest way to handle both
 * cases. So the old code only handles when dest > src, but
 * misses the case when dest < src, where we use pointer
 * arithmetic to increment, then copy from back to front.
 *
 *	void *ft_memmove(void *dest, const void *src, size_t n)
 *	{
 *	  if (dest > src)
 *		return ft_memmove(dest, src, n);
 *	  else if (dest == src)
 *		return dest;
 *	  size_t i = ft_strlen((char *)src) - 1;
 *	  while (i >= 0)
 *	  {
 *		((char *)dest)[i] = ((char *)src)[i];
 *		i--;
 *	  }
 *	  return dest;
 *	}
 */
void *ft_memmove(void *dest, const void *src, size_t n) {
	unsigned char *d;
	const unsigned char *s;

	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	if (d == s || n == 0)
		return (dest);
	if (d < s) {
		while (n--)
			*d++ = *s++;
	} else {
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}

/* Old str_append_mem:
 * The mistake was assuming ft_memcpy checks if s1 is NULL, but
 * it does not. So we need to check to add a NULL check for s1.
 *
 * This function appends size2 bytes from s2 to s1. It allocates
 * memory for the new combined string length with the NULL
 * character, copies the contents of s1, then copies the contents
 * of s2 behind s1, adds the NULL character, frees the old s1, and
 * overrides s1 with the new pointer. This function is essentially
 * just realloc(s1, size2) & appending s2 to the end of s1.
 *
 *	int str_append_mem(char **s1, char *s2, size_t size2)
 *	{
 *	  size_t size1 = ft_strlen(*s1);
 *	  char *tmp = malloc(size2 + size1 + 1);
 *	  if (!tmp)
 *		return 0;
 *	  ft_memcpy(tmp, *s1, size1);
 *	  ft_memcpy(tmp + size1, s2, size2);
 *	  tmp[size1 + size2] = '\0';
 *	  free(*s1);
 *	  *s1 = tmp;
 *	  return 1;
 *	}
 */
int str_append_mem(char **s1, char *s2, size_t size2) {
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return 0;
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1;
}

/* This is the only function that is given
 * that is correct. Just leave it as is
 */
int str_append_str(char **s1, char *s2) {
	return str_append_mem(s1, s2, ft_strlen(s2));
}

/* Old get_next_line:
 * The mistakes was not updating tmp so it loops forever
 * when it doesn't find a newline in b with the given
 * BUFFER_SIZE. And it should only return when memory
 * allocation fails, it finds a newline and returns ret,
 * or an error with read occurred. (Sets everything to NULL)
 *
 * To accomplish the correct behavior, we make it an infinite
 * loop and only return when the above conditions are met. It
 * first finds a newline in the static variable. If found, it
 * tries to append up to and including the newline to ret using
 * pointer arithmetic to calculate the size. Then it shifts the
 * remaining part of b to the front using ft_memmove and returns
 * ret.
 *
 * If no newline is found, it appends the entire b to ret.
 * If memory allocation fails for appending, it returns NULL.
 * Then it reads from fd into b. If read encounters an
 * error or end-of-file, it resets b. If ret has content,
 * it is returned, else it frees ret and returns NULL.
 * If read is successful, it NULL-terminates b and the
 * loop continues. This ensures that only BUFFER_SIZE
 * is being used for reading the file descriptor.
 *
 *
 *	char *get_next_line(int fd)
 *	{
 *	  static char b[BUFFER_SIZE + 1] = "";
 *	  char *ret = NULL;
 *	  char *tmp = ft_strchr(b, '\n');
 *	  while(!tmp)
 *	  {
 *		if (!str_append_str(&ret, b))
 *		  return (NULL);
 *		int read_ret = read(fd, b, BUFFER_SIZE);
 *		if (read_ret == -1)
 *		  return (NULL);
 *		b[read_ret] = 0;
 *	  }
 *	  if (!str_append_mem(&ret, b, tmp - b + 1))
 *	  {
 *		free(ret);
 *		return NULL;
 *	  }
 *	  return ret;
 *	}
 */
char *get_next_line(int fd) {
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;

	while (1) {
		char *temp = ft_strchr(b, '\n');
		if (temp) {
			if (!str_append_mem(&ret, b, temp - b + 1)) {
				free(ret);
				return NULL;
			}
			ft_memmove(b, temp + 1, ft_strlen(temp + 1) + 1);
			return ret;
		}

		if (!str_append_str(&ret, b))
			return NULL;

		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0) {
			b[0] = '\0';
			if (ret && *ret)
				return ret;
			free(ret);
			return NULL;
		}

		b[read_ret] = '\0';
	}
}
