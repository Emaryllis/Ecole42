/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:01:'0' by egoh             #+#    #+#             */
/*   Updated: 2024/03/09 16:01:51 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * req_i[1] is the column index, req_i[2] is the row index.<br/>
 * req_i[1] resets to 0 when it reaches 4 since it hit the end of the row.<br/>
 * req_i[2] increments when req_i[1] resets.<br/>
 * Initialize the grid using the grid index(arr[0])
 * converted from a character to an int
 */
void	req_convert(const char *req_str, int *req_i, int req_arr[4][4])
{
	if (req_i[1] == 4)
	{
		req_i[1] = 0;
		req_i[2]++;
	}
	req_arr[req_i[2]][req_i[1]] = req_str[req_i[0]] - 48;
	req_i[1]++;
	req_i[0]++;
}

/**
 * attr[0] is an index for the grid string.<br/>
 * Call req_convert if character is a digit.<br/>
 * Skip over if character is a space.<br/>
 * Print error message if character is not digit/space.<br/>
 * Also print error if grid string is not 31 characters.<br/>
 * This is to make sure there are exactly 16 digits and 15 spaces
 * @returns 0 if successful, 1 if error
 */
int	req_convert_check(char *req_str, int *req_i, int req_arr[4][4])
{
	int	count_space;

	count_space = 0;
	while (req_str[req_i[0]] != '\0')
	{
		if (req_str[req_i[0]] >= '1' && req_str[req_i[0]] <= '4')
			req_convert(req_str, req_i, req_arr);
		else if (req_str[req_i[0]] == ' ')
		{
			req_i[0]++;
			count_space++;
		}
		else
			return (1);
	}
	if (req_i[0] != 31 || req_arr[3][3] == -1 || count_space != 15)
		return (1);
	return (0);
}
void	print_grid(const int grid_arr[4][4]);
void	solve(int req_arr[4][4]);

/**
 * Make sure there is exactly 1 param.<br/>
 * Initialize req_index to 0.<br/>
 * Make last element of grid_arr to be -1 to ensure
 * the whole grid array was iterated.<br/>
 * req_convert_check to convert the requirements string to an array.<br/>
 * If it returns 1, there was an error converting the string.<br/>
 * Call solve if no error
 */
int	main(int len, char **args)
{
	int	index;
	int	req_arr[4][4];
	int	req_i[3];

	if (len == 2)
	{
		index = -1;
		while (index++ < 3)
			req_i[index] = 0;
		req_arr[3][3] = -1;
		if (req_convert_check(args[1], req_i, req_arr) == 1)
		{
			write(1, "Error", 5);
			return (0);
		}
		solve(req_arr);
	}
	else
		write(1, "Error", 5);
	return (0);
}

/**
 * Prints the grid by iterating through the row then the column<br/>
 * Second while loop only prints 3 times as the last one needs
 * to be a character, then a new line is printed
 * @param grid_arr Array version of the grid
 */
void	print_grid(const int grid_arr[4][4])
{
	int		row;
	int		col;
	char	temp;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 3)
		{
			temp = grid_arr[row][col] + '0';
			write(1, &temp, 1);
			write(1, " ", 1);
		}
		temp = grid_arr[row][col] + '0';
		write(1, &temp, 1);
		write(1, "\n", 1);
	}
}
