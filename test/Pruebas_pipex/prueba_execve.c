



//probar a ejecuta el comando wc | ls y luego ls | wc (ver como se comporta)
//despues comparar con la funcion en dos situaciones:
//primera situacion (SIN WAIT): cambiando un comando por otro
//segunda situacion (CON WAIT): cambiando un comando por otro

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int     main(void)
{
    char    *a;
    char    *args[2]= {"ls", NULL};
    char    *args2[2]= {"wc", NULL};
    int     pipe_ports[2];
    pid_t   id;
    int     fd_dest;

    fd_dest = open("execve.txt", O_CREAT | O_TRUNC | O_WRONLY);
    if (fd_dest < 0)
    {
        write(1, "a\n", 2);
        return(1);
    }
    a = malloc(34);
    if (!a)
        return(1);
    pipe(pipe_ports);
    id = fork();
    if (id < 0)
    {
        perror(strerror(errno));
        exit(1);
    }
    if (id == 0)
    {
        write(1, "son\n", 4);
        dup2(pipe_ports[1], STDOUT_FILENO);
        close(pipe_ports[0]);
        if(execve("/bin/wc", args2, NULL))
        {
            perror(strerror(errno));
            exit(1);
        }
    }
    else 
    {
        write(1, "father\n", 8);
        dup2(pipe_ports[0], STDIN_FILENO);
        close(pipe_ports[1]);
        if(execve("/bin/ls", args, NULL))
        {
            perror(strerror(errno));
            exit(1);
        }
    }
}

