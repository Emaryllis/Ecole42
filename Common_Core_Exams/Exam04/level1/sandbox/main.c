#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

int main()
{
    int result;

    printf("Testing nice function:\n");
    result = sandbox(nice_function, 5, true);
    printf("Result: %d\n\n", result);

    printf("Testing bad function (segfault):\n");
    result = sandbox(bad_function_segfault, 5, true);
    printf("Result: %d\n\n", result);

    printf("Testing bad function (timeout):\n");
    result = sandbox(bad_function_timeout, 2, true);
    printf("Result: %d\n\n", result);

    return 0;
}
 
