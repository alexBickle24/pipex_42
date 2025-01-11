


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int i = 0;
    int iterations = 20;//Número de iteraciones

    while (i < iterations) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork fallido");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Código del proceso hijo
            printf("Proceso hijo: PID = %d, iteración = %d\n", getpid(), i);
            exit(0); // Termina el proceso hijo inmediatamente
        } else {
            // Código del proceso padre
            printf("Proceso padre: PID = %d, iteración = %d\n", getpid(), i);
            // El padre continúa
        }
        i++; // Incrementar la iteración
    }

    // Esperar a que todos los hijos terminen
    while (wait(NULL) > 0);
    return 0;
}