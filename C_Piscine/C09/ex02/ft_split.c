/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int	is_sep(char chr, const char *charset)
{
	int	chr_i;

	chr_i = 0;
	while (charset[chr_i])
	{
		if (chr == charset[chr_i])
			return (1);
		chr_i++;
	}
	if (chr == '\0')
		return (1);
	return (0);
}

int	word_count(const char *str, char *charset)
{
	int	str_i;
	int	words;

	words = 0;
	str_i = 0;
	while (str[str_i])
	{
		if (is_sep(str[str_i + 1], charset) == 1
			&& is_sep(str[str_i], charset) == 0)
			words++;
		str_i++;
	}
	return (words);
}

void	add_word(char *dest, const char *src, char *charset)
{
	int	src_i;

	src_i = 0;
	while (is_sep(src[src_i], charset) == 0)
	{
		dest[src_i] = src[src_i];
		src_i++;
	}
	dest[src_i] = '\0';
}

void	split_words(char **split, const char *str, char *charset)
{
	int		str_i;
	int		find_end;
	int		word;

	word = 0;
	str_i = 0;
	while (str[str_i])
	{
		if (is_sep(str[str_i], charset) == 1)
			str_i++;
		else
		{
			find_end = 0;
			while (is_sep(str[str_i + find_end], charset) == 0)
				find_end++;
			split[word] = (char *)malloc(sizeof(char) * (find_end + 1));
			add_word(split[word], str + str_i, charset);
			str_i += find_end;
			word++;
		}
	}
}

char	**ft_split(const char *str, char *charset)
{
	char	**word_arr;
	int		words;

	words = word_count(str, charset);
	word_arr = (char **)malloc(sizeof(char *) * (words + 1));
	word_arr[words] = 0;
	split_words(word_arr, str, charset);
	return (word_arr);
}

//#include <assert.h>
//#include <string.h>
//#include <stdio.h>
//int main() {
//	char **result;
//
//	// Test 1: Normal case
//	result = ft_split("Hello World", " ");
//	assert(strcmp(result[0], "Hello") == 0);
//	assert(strcmp(result[1], "World") == 0);
//	assert(result[2] == NULL);
//
//	// Test 2: Multiple separators
//	result = ft_split("Hello-World-Testing-123", "-");
//	assert(strcmp(result[0], "Hello") == 0);
//	assert(strcmp(result[1], "World") == 0);
//	assert(strcmp(result[2], "Testing") == 0);
//	assert(strcmp(result[3], "123") == 0);
//	assert(result[4] == NULL);
//
//	// Test 3: Empty string
//	result = ft_split("", " ");
//	assert(result[0] == NULL);
//
//	// Test 4: No separators
//	result = ft_split("HelloWorld", " ");
//	assert(strcmp(result[0], "HelloWorld") == 0);
//	assert(result[1] == NULL);
//
//	// Test 5: Separator at the beginning and end
//	result = ft_split("-Hello-World-", "-");
//	assert(strcmp(result[0], "Hello") == 0);
//	assert(strcmp(result[1], "World") == 0);
//	assert(result[2] == NULL);
//
//	// Free memory
//	for (int i = 0; result[i] != NULL; i++) free(result[i]);
//	free(result);
//	printf("All tests passed!\n");
//	return 0;
//}
