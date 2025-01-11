


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


void    ft_iterar(void)
{
    pid_t pid;
    
    pid = fork();
    if (pid < 0)
    {
        perror(strerror(errno));
        return ;
    }
    if (pid == 0)
    {
        printf("Escribo en el archivo desde el porceso hijo, mi pid es %d\n", getpid());
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Escribo en el archivo desde el porceso padre, mi pid es %d\n", getpid());
    }
}

int main(void)
{
    int     fd;
    int     i;

    fd = open("Prueba_buffer_pid_wait_f.txt", O_CREAT | O_WRONLY, 0664);
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
    i = 0;
    while (i++ < 20)
    {
        ft_iterar();
        i++;
    }
    return(0);
}