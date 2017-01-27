#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * Declaracion de estructuras.
 */

struct _signals{
    int signalNum;
    struct _signals *p_next;
};
typedef struct _signals Signals;


/**
 * @header void handler(int);
 *
 * Función usada para detectar la
 * señal SIGTERM y terminar el proceso.
 *
 * @param signum
 */

void handler(int);

/**
 * @header add_signal(int signum)
 *
 * @note Creamos en cada llamada a esta funcion,
 * un puntero a una estructura, si es el
 * primer dato de la estructura, tanto el
 * puntero p_first como el puntero p_aux,
 * van a apuntar al inicio de la estructura,
 * de no ser NULL, el unico puntero que
 * vamos a mover el p_aux.
 *
 * @param signum recibe la señal
 */

void add_signal(int);


/**
 * Variables globales.
 * @var end: señala la captura de @signal SIGTERM.
 * @var *p_first, *p_aux: punteros a @struct _signals
 */

int end = 0;
Signals *p_first = NULL, *p_aux = NULL;

int main(){
    system("clear");
    printf("Ejercicio 3 - Practica 1.\n");
    printf("PID : %d\n", getpid());

    struct sigaction act;
    //reset all members
    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    act.sa_flags = 0;
    for (int i = 0; i < 30; ++i) {
        sigaction(i, &act, NULL);
    }

    while (!end){
        pause();
    }

    p_aux = p_first;
    printf("\n\n( ");
    while (p_aux!=NULL){
        if(p_aux->p_next != NULL) printf("%d, ",p_aux->signalNum);
        else printf("%d )\n\n",p_aux->signalNum);
        p_aux = p_aux->p_next;
    }

    return 0;
}

void handler(int signum){
    add_signal(signum);
    switch (signum){
        case SIGTERM:
            end = 1;
            break;
        default:
            break;
    }
    return;
}

void add_signal(int signum){
    Signals *p_new;
    p_new = (struct _signals *)malloc(sizeof(struct _signals));
    if(p_new == NULL) printf("No disk space");

    p_new->signalNum = signum;
    p_new->p_next = NULL;

    if(p_first == NULL){
        p_first = p_new;
        p_aux = p_new;
    } else{
        p_aux->p_next =  p_new;
        p_aux = p_aux->p_next;
    }


}