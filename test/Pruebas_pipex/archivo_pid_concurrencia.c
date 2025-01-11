

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    pid_t   pid;
    int     fd;
    int     i;

    fd = open("Prueba_pid_concurrencia", O_CREAT | O_WRONLY, 0664);
    if (fd < 0)
    {
        printf("error");
        return(1);
    }
    i = 0;
    while (i < 20)
    {
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
        if (pid == 0)
        {
            printf("%d  Escribo en el archivo desde el porceso hijo, mi pid es %d\n", i, getpid());
            exit(0);
        }
        else
        {
            printf("%d  Escribo en el archivo desde el porceso padre, mi pid es %d\n", i, getpid());
        }
        printf("esto se ejecuta en el proceso padre\n");
        i++;
    }
    return(0);
}


