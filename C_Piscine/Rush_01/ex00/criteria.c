/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   criteria.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:01:48 by egoh              #+#    #+#             */
/*   Updated: 2024/03/09 16:01:51 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_left_right(int check, const int *grid_i,
						int grid[4][4], int arr[4][4])
{
	int	i;
	int	highest;
	int	count;

	i = -1;
	highest = 0;
	count = 0;
	while (++i < 4)
	{
		if (grid_i[2] == grid[grid_i[0]][i] && i != grid_i[1])
			return (1);
		if (grid[grid_i[0]][i] > highest)
		{
			highest = grid[grid_i[0]][i];
			count++;
		}
		if (grid[grid_i[0]][i] == -1)
			check = 1;
	}
	if (count > arr[2][grid_i[0]] && check == 0)
		return (1);
	if (check == 0 && count != arr[2][grid_i[0]])
		return (1);
	return (0);
}

int	check_up_down(int check, const int *grid_i, int grid[4][4], int arr[4][4])
{
	int	i;
	int	highest;
	int	count;

	count = 0;
	i = -1;
	highest = 0;
	while (++i < 4)
	{
		if (grid_i[2] == grid[i][grid_i[1]] && i != grid_i[0])
			return (1);
		if (grid[i][grid_i[1]] > highest)
		{
			highest = grid[i][grid_i[1]];
			count++;
		}
		if (grid[i][grid_i[1]] == -1)
			check = 1;
	}
	if (count > arr[0][grid_i[1]] && check == 0)
		return (1);
	if (check == 0 && count != arr[0][grid_i[1]])
		return (1);
	return (0);
}

int	check_right_left(int check, const int *grid_i,
						int grid[4][4], int arr[4][4])
{
	int	count;
	int	highest;
	int	i;

	count = 0;
	highest = 0;
	i = 4;
	while (--i > -1)
	{
		if (grid[grid_i[0]][i] > highest)
		{
			highest = grid[grid_i[0]][i];
			count++;
		}
		if (grid[grid_i[0]][i] == -1)
			check = 1;
	}
	if (count > arr[3][grid_i[0]] && check == 0)
		return (1);
	if (check == 0 && count != arr[3][grid_i[0]])
		return (1);
	return (0);
}

int	check_down_up(int check, const int *grid_i, int grid[4][4], int arr[4][4])
{
	int	count;
	int	highest;
	int	i;

	count = 0;
	highest = 0;
	i = 4;
	while (--i > -1)
	{
		if (grid[i][grid_i[1]] > highest)
		{
			highest = grid[i][grid_i[1]];
			count++;
		}
		if (grid[i][grid_i[1]] == -1)
			check = 1;
	}
	if (count > arr[1][grid_i[1]] && check == 0)
		return (1);
	if (check == 0 && count != arr[1][grid_i[1]])
		return (1);
	return (0);
}
