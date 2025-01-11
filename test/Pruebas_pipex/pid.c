


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

    printf("el PID oroginal es %d\n", getpid());
    fd = open("pid", O_CREAT | O_WRONLY, 0664);
    if (fd < 0)
    {
        printf("error");
        return(1);
    }
    if (!dup2(fd, STDOUT_FILENO))
    {
        perror(strerror(errno));
        return(1);
    }
    pid = fork();
    if (pid < 0)
    {
        perror(strerror(errno));
        return(1);
    }
    if (pid == 0)
    {
        printf("Escribo en el archivo desde el porceso hijo, mi pid es %d\n", getpid());
        exit(0);
    }
    else
    {
        printf("Escribo en el archivo desde el porceso padre, mi pid es %d\n", getpid());
    }
    printf("Si esto se ejecuta un vez esta solo en el proceso padreJA\n");
    return(0);
}