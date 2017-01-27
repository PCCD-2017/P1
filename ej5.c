/**
 * Ejercicio 5
 */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


/**
 * Función usada para detectar la
 * señal SIGTERM y terminar el proceso.
 *
 * @param signum señal recogida.
 */
void handler(int signum);
int ascensorSubiendo(int pos);
int ascensorBajando(int pos);

/**
 * Variables globales.
 *
 * @boolean subir: indica si ascensor sube, @signal SIGUSR1.
 * @boolean bajar: indica si el ascensor baja, @signal SIGUSR2.
 * @boolean fin: indica el fin del proceso, @signal SIGQUIT.
 * @def T_piso: tiempo constante que tarda el ascensor en subir
 */
bool subir = false;
bool bajar = false;
bool fin = false;
int T_piso = 3;
int vecesSubir = 0;
int vecesBajar = 0;


int main(int argc, char *argv[]) {
    int pos = 1;
    int maxAltura = 1;

    system("clear");
    printf("Ejercicio 5 de la practica 1\n");

    struct sigaction act;
    //reset all members
    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    act.sa_flags = 0;
    //31 signals (kill -l)
    for (int i = 5; i <= 32; ++i) {
        sigaction(i, &act, NULL);
    }

    printf("Introduzca una altura maxima: ");
    scanf("%d", &maxAltura);
    system("clear");
    printf("PID proceso: %d\n\n", getpid());
    printf("El ascensor se encuentra en el piso: %d\n", pos);

    while (!fin) {
        pause();
        system("clear");
        printf("PID proceso: %d\n\n", getpid());
        if (subir) {
            if (pos < maxAltura) {
                pos = ascensorSubiendo(pos);
            } else
                printf("El ascensor se encuentra en el ultimo piso, no puede subir mas\n\n");
        }
        if (bajar) {
            if (pos > 1) {
                pos = ascensorBajando(pos);
            } else {
                printf("El ascensor se encuentra en el primer piso, no puede bajar mas\n\n");
            }
        }
    }
    printf("\n\nProceso finalizado.\n");
    printf("El ascensor ha subido: %d veces\n",vecesSubir);
    printf("El ascensor ha bajado: %d veces\n\n",vecesBajar);

    return 0;
}

/**
 * Función usada para detectar la
 * señal SIGTERM y terminar el proceso.
 *
 * @param signum
 */
void handler(int signum){
    switch (signum) {
        case SIGUSR1:
            subir = true;
            bajar = false;
            fin = false;
            break;
        case SIGUSR2:
            bajar = true;
            subir = false;
            fin = false;
            break;
        case SIGTERM:
            fin = true;
            subir = false;
            bajar = false;
            break;
        default:
            subir = false;
            bajar = false;
            fin = false;
            break;
    }
    return;
}

int ascensorSubiendo(int pos){
    time_t start, end;
    double elapsed;

    printf("Ascensor subiendo...\n");

    vecesSubir = vecesSubir + 1;

    time(&start);
    do{
        time(&end);
        elapsed = difftime(end,start);
    }while (elapsed < T_piso);

    printf("El ascensor se encuentra en el piso: %d\n\n", pos + 1);

    return pos + 1;
}

int ascensorBajando(int pos){
    time_t start, end;
    double elapsed;

    printf("Ascensor bajando...\n");
    vecesBajar = vecesBajar + 1;

    time(&start);
    do{
        time(&end);
        elapsed = difftime(end,start);
    }while (elapsed < T_piso);

    printf("El ascensor se encuentra en el piso: %d\n\n", pos - 1);

    return pos - 1;
}