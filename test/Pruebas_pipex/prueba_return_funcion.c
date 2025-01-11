



#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>


void funcion(void)
{
    char *hola;

    hola = malloc(42);
    if(!hola)
    {
        exit(1);
    }
    char    *args[2]= {"ls", NULL};
    if(execve("bin/ls", args, NULL))
    {
        perror(strerror(errno));
        exit(1);
    }
}

int     main(void)
{
    char    *a;
 
    a = malloc(34);
    if (!a)
        return(1);
    funcion();
}