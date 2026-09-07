/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_disp_file(int fd)
{
	char	buffer;

	while (read(fd, &buffer, 1) != 0)
		write(1, &buffer, 1);
}

int	file_checker(int argc, char *arg1)
{
	if (argc != 2)
	{
		if (argc > 2)
			write(2, "Too many arguments.\n", 20);
		else
			write(2, "File name missing.\n", 19);
		return (1);
	}
	if (ft_strcmp(arg1, ".") == 0 || ft_strcmp(arg1, "/") == 0
		|| ft_strcmp(arg1, "..") == 0 || ft_strcmp(arg1, "./") == 0
		|| ft_strcmp(arg1, "../") == 0)
	{
		write(1, "Is a directory.\n", 16);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (file_checker(argc, argv[1]) == 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Cannot read file.\n", 18);
		return (1);
	}
	ft_disp_file(fd);
	if ((close(fd)) == -1)
	{
		write(1, "Cannot read file.\n", 18);
		return (1);
	}
	return (0);
}
