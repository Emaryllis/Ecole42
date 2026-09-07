#include <unistd.h>
#include <stdlib.h>
// Allowed functions: pipe, fork, dup2, execvp, close, exit

/**
 * @param file The command to execute (e.g., "ls", "echo").
 * @param argv The arguments for the command, including the command itself as argv[0], and terminated by NULL.
 * @param type 'r' to read from the child process's stdout, 'w' to write to the child process's stdin.
 * @return On success, returns a file descriptor for communication with the child process. On failure, returns -1.
 *
 * Type must match either 'r' or 'w', and presence check for file & argv. Return -1 if fails (1st conditional)
 * If pipe fails to be allocated, return -1 (2nd conditional)
 * Tries to fork, closes fds & return -1 on failure. (3rd conditional)
 * Runs logic for child process (4th conditional)
 * In the child process:
 *     - Redirect fds to either stdout or stdin when type = 'r' or 'w' respectively, exit(1) on failure
 *     - Closes excess fds & lets execvp handle the args & return, or exit 1 if execvp fails.
 * In the parent process, close the unused fd and return the other fd.
 *
 * Short explaination for exam:
 * Return -1 for invalid file, argv & type. Same with pipe failure (-1)
 * Fork to create child, close fds & return -1 on failure.
 * In child, redirect stdin or stdout for execvp, then close fds.
 * For child, dup2 or execvp failure exits with 1.
 * In parent, close write if reading, else (writing) close read.
 * For parent, return the other fd (the non closed one)
 */
int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;
	if(!file || !argv || (type != 'r' && type != 'w'))
		return(-1);

	if(pipe(fd)== -1)
		return(-1);

	pid = fork();
	if(pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return(-1);
	}
	if(pid == 0)
	{
		if(type == 'r')
		{
			if(dup2(fd[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else
		{
			if(dup2(fd[0], STDIN_FILENO) == -1)
				exit(1);
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	else
	{
		if(type == 'r')
		{
			close(fd[1]);
			return(fd[0]);
		}
		else
		{
			close(fd[0]);
			return(fd[1]);
		}
	}
}
