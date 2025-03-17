
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("/tmp/hola", O_CREAT);
	return (0);
}