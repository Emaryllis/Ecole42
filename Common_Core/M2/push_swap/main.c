/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 09:50:28 by egoh              #+#    #+#             */
/*   Updated: 2025/10/05 05:25:00 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	init_data(int *intlist, int count);

static void	error(void)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_strlist(char **strlist, bool exit_out)
{
	int	i;

	i = 0;
	while (strlist[i])
		free(strlist[i++]);
	free(strlist);
	if (exit_out)
		error();
}

int	main(int argc, char **argv)
{
	t_intlist	intlist;
	char		**strlist;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if (argc == 2)
	{
		strlist = ft_split(argv[1], ' ');
		if (!strlist)
			error();
		intlist = (t_intlist){get_intlist(strlist), strlist_count(strlist)};
		free_strlist(strlist, !intlist.list);
	}
	else
	{
		intlist = (t_intlist){get_intlist(argv + 1), argc - 1};
		if (!intlist.list)
			error();
	}
	init_data(intlist.list, intlist.count);
	free(intlist.list);
	return (EXIT_SUCCESS);
}
