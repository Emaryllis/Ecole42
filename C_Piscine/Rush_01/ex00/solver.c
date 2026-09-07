/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:01:48 by egoh              #+#    #+#             */
/*   Updated: 2024/03/09 16:01:51 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	solve(int req_arr[4][4]);
void	print_grid(const int grid_arr[4][4]);
void	init_grid(int ori_grid_arr[4][4], int grid_arr[4][4]);
int		grid_looper(int grid_arr[4][4], int req_arr[4][4], int row, int col);
int		check_left_right(int check, const int *grid_i,
			int grid[4][4], int arr[4][4]);
int		check_up_down(int check, const int *grid_i,
			int grid[4][4], int arr[4][4]);
int		check_right_left(int check, const int *grid_i,
			int grid[4][4], int arr[4][4]);
int		check_down_up(int check, const int *grid_i,
			int grid[4][4], int arr[4][4]);

/**
 * Set current cell to current number.<br/>
 * Check the row from left to right, then right to left,
 * then column from up to down, then down to up.<br/>
 * Run the checks to see if the grid is valid.<br/>
 * Return 0 if the grid is valid, else return 1.
 */
int	is_valid(int grid[4][4], int arr[4][4], int *grid_i)
{
	grid[grid_i[0]][grid_i[1]] = grid_i[2];
	if (check_left_right(0, grid_i, grid, arr) == 1)
		return (1);
	if (check_right_left(0, grid_i, grid, arr) == 1)
		return (1);
	if (check_up_down(0, grid_i, grid, arr) == 1)
		return (1);
	if (check_down_up(0, grid_i, grid, arr) == 1)
		return (1);
	return (0);
}

/**
 * The following checks check if their side
 * meets a requirement of either 2 or 3.<br/>
 * It checks in this order: top, bottom, left, right.<br/>
 * If any check passes, return 1, else return 0.<br/>
 * This is to reduce time complexity by narrowing the possible solutions.
 */
int	check_edge(int req_arr[4][4], int row, int col)
{
	if ((row == 0) && (req_arr[0][col] == 2 || req_arr[0][col] == 3))
		return (1);
	if ((row == 3) && (req_arr[1][col] == 2 || req_arr[1][col] == 3))
		return (1);
	if ((col == 0) && (req_arr[2][row] == 2 || req_arr[2][row] == 3))
		return (1);
	if ((col == 3) && (req_arr[3][row] == 2 || req_arr[3][row] == 3))
		return (1);
	return (0);
}

/**
 * Loops through the index while incrementing.<br/>
 * If the current cell is on the edge(row/col is 0/3),
 * is 4, and meets check_edge(), skip this number.<br/>
 * Set the current number to the current cell.<br/>
 * If current grid is valid and is solved
 * with the current number, return 0.<br/>
 * If current grid is not valid or the puzzle is not
 * solved with the current cell, reset the current
 * cell (Set to -1) and continue with the next number.<br/>
 * If current number(index) goes beyond 4,
 * the current cell cannot be filled.<br/>
 */
int	condition_loop(int *index, int *grid_i,
			int req_arr[4][4], int grid_arr[4][4])
{
	int	row;
	int	col;

	row = grid_i[0];
	col = grid_i[1];
	while (++*index < 5)
	{
		if (*index == 4 && (grid_i[0] == 0 || grid_i[1] == 0 || grid_i[0] == 3
				|| grid_i[1] == 3) && check_edge(req_arr, row, col) == 1)
			continue ;
		grid_i[2] = *index;
		if (is_valid(grid_arr, req_arr, grid_i) == 0
			&& grid_looper(grid_arr, req_arr, row, col + 1) == 0)
			return (0);
		grid_arr[row][col] = -1;
	}
	return (1);
}

/**
 * If last element has been reached, return 0.<br/>
 * If column is at the end(col==4),
 * recurse to the next row at column 0.<br/>
 * If the current cell is already filled(not -1),
 * recurse to the next cell and increment the column by 1.<br/>
 * If the current cell is not filled, check the check_edge.<br/>
 * If the check_edge returns 0, the grid is valid,
 * the grid is at the last element, so the puzzle is solved.<br/>
 * If the check_edge returns 1, the puzzle is not solved.<br/>
 */
int	grid_looper(int grid_arr[4][4], int req_arr[4][4], int row, int col)
{
	int	index;
	int	grid_i[3];

	index = 0;
	grid_i[0] = row;
	grid_i[1] = col;
	if (row == 4)
		return (0);
	else if (col == 4)
		return (grid_looper(grid_arr, req_arr, row + 1, 0));
	else if (grid_arr[row][col] != -1)
		return (grid_looper(grid_arr, req_arr, row, col + 1));
	else
	{
		if (condition_loop(&index, grid_i, req_arr, grid_arr) == 0)
			return (0);
		else
			return (1);
	}
}

/**
 * The nested while loops initializes the sorted grid(grid_arr) with -1.<br/>
 * grid_looper() attempts to solve the puzzle.<br/>
 * If the puzzle is solved, print grid, else print an error.<br/>
 */
void	solve(int req_arr[4][4])
{
	int	grid_arr[4][4];
	int	row;
	int	col;

	row = -1;
	while (++row < 4)
	{
		col = -1;
		while (++col < 4)
			grid_arr[row][col] = -1;
	}
	init_grid(req_arr, grid_arr);
	if (grid_looper(grid_arr, req_arr, 0, 0) == 0)
		print_grid(grid_arr);
	else
		write(1, "Error", 5);
}
