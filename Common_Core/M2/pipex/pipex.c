/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:07:53 by egoh              #+#    #+#             */
/*   Updated: 2024/02/29 14:10:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	child_process(char **argv, char **envp, int *fd)
{
	int	filein;

	close(fd[0]);
	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
	{
		close(fd[1]);
		error(argv[1]);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[1]);
	close(filein);
	execute(argv[2], envp, -127);
}

static void	second_child_process(char **argv, char **envp, int *fd)
{
	int	fileout;

	close(fd[1]);
	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
	{
		close(fd[0]);
		error(argv[4]);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[0]);
	close(fileout);
	execute(argv[3], envp, 0);
}

static void	check_args(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" infile cmd1 cmd2 outfile\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	handle_exit_code(pid_t pid1, pid_t pid2, int *status, int *code)
{
	int		i;
	int		temp_status;
	pid_t	pid;

	i = -1;
	while (++i < 2)
	{
		pid = waitpid(-1, &temp_status, 0);
		if (pid == pid1)
			status[0] = temp_status;
		if (pid == pid2)
			status[1] = temp_status;
		pid = 0;
	}
	if ((status[0] & 0x7F) == 0)
		code[0] = (status[0] >> 8) & 0xFF;
	if ((status[1] & 0x7F) == 0)
		code[1] = (status[1] >> 8) & 0xFF;
	if (code[1] == 126 || code[1] == 127)
		exit(code[1]);
	if (code[0] == 126 || code[0] == 127)
		exit(code[0]);
	exit(code[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	check_args(argc, argv);
	if (pipe(fd) == -1)
		error("Pipe Error");
	pid1 = fork();
	if (pid1 == -1)
		error("Fork Error (1st child)");
	if (pid1 == 0)
		child_process(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		error("Fork Error (2nd child)");
	if (pid2 == 0)
		second_child_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	handle_exit_code(pid1, pid2, (int [2]){0}, (int [2]){0});
}
