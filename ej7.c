/*
 * Ejercicio 7
 */

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void sigaction_handler(int);

int fin = 0;
int piso = 0;
int pid = 0;

int main(int argc, char* argv[]){
    struct sigaction sa;
    printf("PID del proceso sensor: %d\n", getpid());
    printf("Introduzca el pid del ascensor: \n");
    fscanf(stdin, "%d", &pid);
    piso = atoi(argv[1]);
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = 0;
    sa.sa_handler = sigaction_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while(!fin)
        pause();
    return 0;
}

void sigaction_handler(int signum){
    if(signum == SIGUSR1){
        printf("Se ha activado el sensor del piso %d.\n", piso);
        kill(pid, SIGALRM);
    }
    if(signum == SIGUSR2){
        printf("El ascensor se dirige al piso %d.\n", piso);
        kill(pid, SIGALRM);
    }
    return;
}
