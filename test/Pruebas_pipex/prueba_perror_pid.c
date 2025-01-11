



#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid < 1)
        perror("primero");
    if (pid == 0)
    {
        printf("seguindo\n");
        perror("tercero");
    }
    wait(NULL);
    perror("cuarto");
    return(0);
}