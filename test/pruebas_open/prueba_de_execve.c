
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


void	prueba(pid_t pid, char **args)
{
	
	
	if (pid == 0)
	{
		printf("se ejecuta el proceso hijo\n");
		if (execve("/bin/ls", args, NULL))
		{
			printf("error");
			exit(1);
		}
	}
}

int main(void)
{
	pid_t pid;
	char *args[2] = {"/bin/ls", NULL};

	pid = fork();
	if (pid < 0)
	{
		printf("error");
		exit(1);
	}
	if (pid == 0)
	{
		prueba(pid, args);
	}
	else 
	{
		int status;

		wait (&status);
		printf("el proceso padre se empieza a ajecutar, com estado %d\n", status);
	}
	printf("se acaba el programa\n");
	return (0);
}