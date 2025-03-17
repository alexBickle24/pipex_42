
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *ptr;

	ptr = NULL;
	int fd = open(ptr, O_CREAT);
	if (fd < 0)
	{
		printf("%d\n", fd);
		return (0);
	}
	close (fd);
	return(0);
}