#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
// Allowed functions: fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal,
// errno, sigaddset, sigemptyset, sigfillset, sigdelset, sigismember


void alarm_handler(int sig)
{
    (void)sig;
}

/**
 * @param f The function to test and execute inside the child process.
 * @param timeout The maximum allowed execution time in seconds before the function is killed.
 * @param verbose A boolean flag to enable or disable printing execution status messages.
 * @return On f() success, returns 1. 0 if ret != -1, child sys err/sig. -1 if sandbox func fails (waitpid/fork/generic)
 *
 * Assumption: Wrapped *all* printf functions with verbose flag.
 * Initalizes a sigaction and set its handler to an empty function, flags to 0, and empty mask. (sigemptyset)
 * Uses the above sigaction for the sig alarm (SIGALRM) listener.
 * If fork fails, return -1 (1nd conditional)
 * In the child process, executes the target function f() and exits with 0.
 * The instructions below happen in the parent process.
 * Sets a countdown timer using t sec, where t = timeout [alarm(timeout)]
 * If waitpid fails due to a system error or alarm:
 * - Force-kills the child with SIGKILL and calls waitpid to cleanup the child process.
 * - Prints timeout error, then returns 0. For other failures, return -1.
 * If the child exited normally (WIFEXITED):
 * - Prints success & returns 1 if child returns 0.
 * - Else print return code with bad msg & return 0.
 * If the child crashed via a signal (WIFSIGNALED):
 * - Print generic bad msg with signal failure msg, then return 0.
 * Returns -1 to catch any unhandled errors.
 *
 * Short explaination for exam: (With the same assumption as above)
 * Setup alarm signal with empty handler to use with timeout.
 * Create child using fork, return -1 on failure.
 * In child, run the target function f() and exit with 0.
 * In parent, start alarm timer. [alarm(timeout)]
 * Wait for child process to finish with waitpid. (blocking)
 * If waitpid returns -1:
 * - If EINTR, Kill & cleanup child [waitpid] and print timeout err, then return 0.
 * - Return -1 for other waitpid failures. (Parent func err)
 * If child exits normally with 0, return 1, else print child's ret & return 0.
 * If child returns a signal, print generic bad msg + sig err msg, return 0.
 * Returns -1 to catch any unhandled errors.
 */
int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    pid_t pid = fork();
    if (pid == -1)
        return (-1);
    if (pid == 0)
    {
        f();
        exit(0);
    }
    alarm(timeout);

	int status;
    if (waitpid(pid, &status, 0) == -1)
    {
        if (errno == EINTR)
        {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            if (verbose)
                printf("Bad function: timed out after %u seconds\n", timeout);
            return(0);
        }
        return (-1);
    }
    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == 0)
        {
            if (verbose)
                printf("Nice function!\n");
            return (1);
        }
        else
        {
            if (verbose)
                printf("Bad function: exited with code %d\n", WEXITSTATUS(status));
            return (0);
        }
    }
    if (WIFSIGNALED(status))
    {
        if (verbose)
            printf("Bad function: %s\n", strsignal(WTERMSIG(status)));
        return(0);
    }
    return (-1);
}
