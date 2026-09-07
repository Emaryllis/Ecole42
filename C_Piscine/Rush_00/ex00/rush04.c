/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
void	ft_putchar(char c);

/** 
 * First if statement prints 'A' for the top-left and bottom-right corners
 * Third if statement prints 'C' for the top-right and bottom-left corners
 * Fourth if statement prints 'B' for the borders
 * 5th if statement prints ' ' for the inside of the grid */
void	printer(int width, int height, int row, int col)
{
	if ((row == 0 && col == 0) || (row == height - 1 && col == width - 1
			&& height > 1 && width > 1))
	{
		ft_putchar('A');
	}
	else if ((row == 0 && col == width - 1) || (row == height - 1 && col == 0))
	{
		ft_putchar('C');
	}
	else if (row == 0 || row == height - 1 || col == 0 || col == width - 1)
	{
		ft_putchar('B');
	}
	else
	{
		ft_putchar(' ');
	}
}

/** First while loop iterates over each row
 * Second while loop iterates over each column */
void	rush(int width, int height)
{
	int	row;
	int	col;

	row = 0;
	while (row < height && width > 0)
	{
		col = 0;
		while (col < width)
		{
			printer(width, height, row, col);
			col++;
		}
		ft_putchar('\n');
		row++;
	}
}
