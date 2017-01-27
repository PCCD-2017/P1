//
// Created by David Rodriguez Pereira on 24/1/17.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


void termination_handler(int);

int fin = 0;
int mask[64] = {};

int main(){
    struct sigaction saction, saction2;
    for (int j = 0; j < 64; ++j) {
        mask[j] = 0;
    }
    saction.sa_flags = SA_RESTART;
    sigemptyset(&saction.sa_mask);
    saction.sa_handler = termination_handler;

	printf("Ejercicio 3 - Practica 1.\n");
	printf("PID : %d\n", getpid());

    for (int i = 0; i <= 63; ++i) {
        sigaction(i, &saction, NULL);
        printf("%i", i);
    }


    while(!fin){
        pause();
    }
	return 0;
}

void termination_handler(int signum){
    if(signum==15) {
        fin = 1;
    } else if(signum==10){
        fin = 1;
    } else if(signum==12){
        fin = 1;
    }
    return;
}



