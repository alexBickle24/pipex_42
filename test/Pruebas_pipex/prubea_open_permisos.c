



#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd;

    fd = open("open.txt", O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
    {
        write(1, "aa\n", 3);
        return(1);
    }
    close(fd);
    return(0);
}