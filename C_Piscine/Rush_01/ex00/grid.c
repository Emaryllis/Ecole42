/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:01:48 by egoh              #+#    #+#             */
/*   Updated: 2024/03/09 16:01:51 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_grid(int grid_arr[4][4]);

void	inc_asign(int grid[4][4], int constant, int roworcolumn, int inc_or_dec)
{
	int	z;

	if (inc_or_dec == 0)
	{
		z = -1;
		while (++z < 4)
		{
			if (roworcolumn == 0)
				grid[constant][z] = z + 1;
			else
				grid[z][constant] = z + 1;
		}
	}
	else
	{
		z = 4;
		while (--z > -1)
		{
			if (roworcolumn == 0)
				grid[constant][z] = 4 - z;
			else
				grid[z][constant] = 4 - z;
		}
	}
}

void	asign_one(int grid_arr[4][4], int i, int j)
{
	if (i == 0)
		grid_arr[0][j] = 4;
	else if (i == 1)
		grid_arr[3][j] = 4;
	else if (i == 2)
		grid_arr[j][0] = 4;
	else
		grid_arr[j][3] = 4;
}

void	asign(int grid_arr[4][4], int *i, int *j, int ori_grid_arr[4][4])
{
	int	z;

	z = -1;
	if (ori_grid_arr[*i][*j] == 1)
		asign_one(grid_arr, *i, *j);
	else if (*i == 0)
		inc_asign(grid_arr, *j, 1, 0);
	else if (*i == 1)
		inc_asign(grid_arr, *j, 1, 1);
	else if (*i == 2)
		inc_asign(grid_arr, *j, 0, 0);
	else
		inc_asign(grid_arr, *j, 0, 1);
}

void	init_grid(int ori_grid_arr[4][4], int grid_arr[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (ori_grid_arr[i][j] == 4 || ori_grid_arr[i][j] == 1)
			{
				asign(grid_arr, &i, &j, ori_grid_arr);
			}
		}
	}
}
