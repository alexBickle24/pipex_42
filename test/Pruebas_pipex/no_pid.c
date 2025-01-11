

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    pid_t   pid;
    int     fd;

    fd = open("Prueba_buffer", O_CREAT | O_WRONLY | O_APPEND, 0664);
    if (fd < 0)
    {
        printf("error");
        return(1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror(strerror(errno));
        return(1);
    }
    if (!dup2(fd, STDOUT_FILENO))
    {
        perror(strerror(errno));
        return(1);
    }
    printf("Escribo en el archivo desde los dos procesos a la vez2");
    return(0);
}