#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/**
 * @param cmds A null-terminated command arg array for execvp
 *
 * 1. Iterates through each command & creates a new pipe if there is a next command.
 * 2. If pipe fails, return 1.
 * 3. Forks a child process for execvp, return 1 & close fds if applicable
 * 4. In each child process:
 *    - Redirects stdin to the previous pipe read end (input) if it's not the first command.
 *    - Redirects stdout to the current pipe write end (output) if it's not the last command.
 *    - Calls execvp to execute & replace the child process, exits 1 on failure.
 * 5. In the parent process:
 *    - Closes the previous pipe read end if it exists, as it's no longer needed.
 *    - Closes the current pipe write end after forking the child.
 *    - Replaces the last_fd with the current pipe read end for the next command.
 * 6. After all commands are processed, waits for the child process to finish and returns 0.
 *
 * Short explanation for exam:
 * 1. Index through cmds.
 * 2. Create a pipe if not last cmd.
 * 3. Fork for execvp, return 1 & cleanup fds if fails.
 * 4. In child process:
 *    - Redirect stdin to last read pipe if not 1st cmd. (last_fd != -1)
 *    - Redirect stdout to curr write pipe if not last cmd. (cmds[i + 1] != NULL)
 *    - Call execvp, exit 1 if fails.
 * 5. In parent process:
 *    - Close last_fd if exists. (!= -1)
 *    - If not last cmd, close curr write pipe & set last_fd to curr read pipe.
 * 6. Go back to step 2 until all cmds are processed. (cmds[i] != NULL)
 * 7. Wait for all children to finish, return 0.
 */
int    picoshell(char **cmds[])
{
	int fd[2];
    int last_fd = -1;
    int i = 0;

    while (cmds[i]) {
        if (cmds[i + 1] && pipe(fd) == -1)
            return 1;
		const pid_t pid = fork();
        if (pid == -1) {
            if (cmds[i + 1])  {
                close(fd[0]);
                close(fd[1]);
            }
            return 1;
        }
        if (pid == 0) {
            if (last_fd != -1) {
                if (dup2(last_fd, STDIN_FILENO) == -1)
                    exit(1);
                close(last_fd);
            }
            if (cmds[i + 1]) {
                close(fd[0]);
                if (dup2(fd[1], STDOUT_FILENO) == -1)
                    exit(1);
                close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        if (last_fd != -1)
            close(last_fd);
        if (cmds[i + 1]) {
            close(fd[1]);
            last_fd = fd[0];
        }
        i++;
    }
	int status;
	int ret = 0;
	while (wait(&status) > 0)
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ret = WEXITSTATUS(status);
	return ret;
}