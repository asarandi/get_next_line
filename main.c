#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;

		char *ptr;
		int i = 1;
		while((get_next_line(fd, &ptr)) == 1)
		{
					printf("line # %d, value is: %s\n", i, ptr);
					free(ptr);
					i++;
		}
		close(fd);
//		sleep(30);
	return (0);
}

