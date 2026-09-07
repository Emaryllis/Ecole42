/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2025/09/12 02:30:00 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"
#include <errno.h>

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_array(paths), path);
		free(path);
		i++;
	}
	return (free_array(paths), NULL);
}

/* A simple error displaying function. */
void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static void	free_split(char **cmd, int path_exists, int offset)
{
	int	i;

	i = -1;
	ft_putstr_fd("bash: ", 2);
	if (errno != EACCES)
	{
		if (!cmd)
			exit(EXIT_FAILURE);
		if (cmd[0])
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": ", 2);
		}
		if (path_exists || !cmd[0])
			ft_putstr_fd("Command not found\n", 2);
		else
			ft_putstr_fd("No such file or directory\n", 2);
	}
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	if (errno != EACCES)
		exit(127 + offset);
	ft_putstr_fd("Permission denied\n", 2);
	exit(126);
}

/**
	Function that take the command and send it to find_path before executing it.
	Warning: The function will leak memory if execve succeeds,
	but it is harmless (still reachable, reclaimed by OS).
	Note: Valgrind will report "still reachable" for the cmd array here.
	This is not a leak - the OS frees all memory after execve.
	The only solution is allocating cmd outside execute,
	and then free it outside the execute process (execve takes over
	the process), which is more complicated than necessary for this project
*/
void	execute(char *argv, char **envp, int offset)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
		free_split(cmd, 0, offset);
	if (ft_strchr(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else
		path = find_path(cmd[0], envp);
	if (!path)
		free_split(cmd, 1, offset);
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_split(cmd, 0, offset);
	}
}
