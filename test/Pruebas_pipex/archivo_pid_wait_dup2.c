


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(void)
{
    pid_t   pid;
    int     fd;
    unsigned int     i;

    i = 20;
    while (--i)
    {
        pid = fork();
        if (pid < 0)
        {
            perror(strerror(errno));
            return(1);
        }
        if (pid == 0)
        {
            fd = open("Prueba_buffer_pid_wait_dup2.txt", O_CREAT | O_WRONLY | O_APPEND, 0664);
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
            close(fd);
            printf("%d  Escribo en el archivo desde el porceso hijo, mi pid es %d\n", i, getpid());
            exit(0);
        }
        else
        {
            fd = open("Prueba_buffer_pid_wait.txt", O_CREAT | O_WRONLY | O_APPEND, 0664);
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
            close(fd);
            printf("%d  Escribo en el archivo desde el porceso padre, mi pid es %d\n", i, getpid());
        }
    }

    while(wait(NULL) > 0)
    return(0);
}