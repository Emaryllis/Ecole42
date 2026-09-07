#include "get_next_line.h"
#include <string.h>
#include <fcntl.h>
int main(int c, char **v) {
	if (c != 2)
		return 1;

	int fd = open(v[1], O_RDONLY);
    if (fd < 0)
		return 1;

	char *line;
    int line_count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: [%s]", ++line_count, line);
        if (line[strlen(line) - 1] != '\n')
            printf("\\n");
        printf("\n");
        free(line);
    }

    printf("Total lines read: %d\n", line_count);
    close(fd);
    return 0;
}
