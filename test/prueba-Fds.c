
// #include <unistd.h>
// #include <fcntl.h>


// int main(void)
// {
// 	int fd;
// 	int pipes[2];
// 	int pipes_2[2];
// 	pid_t id;

// 	fd = open("inter.txt", O_RDONLY);
// 	// close (fd);
// 	pipe(pipes);
// 	// pipe(pipes_2);
// 	id = fork();
// 	if (id = 0)
// 	{
// 		// close(pipes[1]);
// 		// close(pipes[0]);
// 		// close(fd);
// 	}
// 	sleep(2);
// 	close(pipes[1]);
// 	close(pipes[0]);
// 	pipe(pipes_2);
// 	// pipe(pipes_2);
// 	// close(pipes_2[1]);
// 	// close(pipes_2[0]);
// 	close(fd);
// 	// retuen(0);

// }



///COMO REASIGNA LOS FD CUANDO SE HAN CERRADO VALGRIND TE LOS INDICA
//valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd1, fd2, fd3, fd4;

    fd1 = open("file1.txt", O_CREAT | O_RDWR, 0644);
    fd2 = open("file2.txt", O_CREAT | O_RDWR, 0644);
    fd3 = open("file3.txt", O_CREAT | O_RDWR, 0644);
    fd4 = open("file4.txt", O_CREAT | O_RDWR, 0644);

    // Imprimir los descriptores abiertos
    printf("FD1: %d, FD2: %d, FD3: %d, FD4: %d\n", fd1, fd2, fd3, fd4);

    // Cerrar fd1 y fd2
    close(fd1);
    close(fd2);

    // Abrir dos nuevos descriptores
    int fd5 = open("file5.txt", O_CREAT | O_RDWR, 0644);
    int fd6 = open("file6.txt", O_CREAT | O_RDWR, 0644);

    // Imprimir los nuevos descriptores
    printf("FD5: %d, FD6: %d\n", fd5, fd6);

    return 0;
}