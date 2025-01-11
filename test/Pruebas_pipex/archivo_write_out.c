



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
    int     i;

    fd = open("archivo_write.txt", O_CREAT | O_WRONLY,0664);
    if (fd < 0)
    {
        printf("error");
        return(1);
    }
    dup2(fd, STDOUT_FILENO);
    i = 0;
    while (i++ < 20)
    {
        pid = fork();
        if (pid < 0)
        {
            perror(strerror(errno));
            return(1);
        }
        if (pid == 0)
        {
            write(fd ,"Escribo en el archivo desde el porceso hijo\n", 44);
            exit(0);
        }
        else
        {
            write(fd ,"Escribo en el archivo desde el porceso padre\n", 45);
        }
    }
    return(0);
}