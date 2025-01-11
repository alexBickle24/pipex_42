

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int     main(void)
{
    char    *a;
    char    *args[2]= {"ls", NULL};
 
    a = malloc(34);
    if (!a)
        return(1);
    if(execve("bin/ls", args, NULL))
    {
        perror(strerror(errno));
        exit(1);
    }
    return(0);

}