#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "get_next_line.h"

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int fd = open(argv[1], O_RDONLY);

		char *ptr;
		int i = 1;
		while(get_next_line(fd, &ptr))
		{
					printf("line # %d, value is: %s\n", i, ptr);
					free(ptr);
					i++;
		}
		close(fd);
	}
	return (0);
}

