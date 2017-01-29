/**
 * Ejercicio 5
 */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

/**
 * Función usada para detectar la
 * señal SIGTERM y terminar el proceso.
 * sensores[] almacena los PID de los procesos sensor, uno para cada piso.
 *
 * @param signum señal recogida.
 */
void handler(int signum);
int ascensorSubiendo(int pos);
int ascensorBajando(int pos);
int sensores[] = {};
int espera = 0;

/**
 * Variables globales.
 *
 * @boolean subir: indica si ascensor sube, @signal SIGUSR1.
 * @boolean bajar: indica si el ascensor baja, @signal SIGUSR2.
 * @boolean fin: indica el fin del proceso, @signal SIGQUIT.
 * @def T_piso: tiempo constante que tarda el ascensor en subir
 * espera : indica si el ascensor está subiendo o bajando.
 */
bool subir = false;
bool bajar = false;
bool fin = false;
int T_piso = 3;
int vecesSubir = 0;
int vecesBajar = 0;
int pos = 0;


int main(int argc, char *argv[]) {
    pos = atoi(argv[1]);
    int maxAltura = 1;

    system("clear");
    printf("Ejercicio 5 modificado de la practica 1\n");

    for(int i = 2; i < argc; i++){
        sensores[i] = atoi(argv[i]);
    }

    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    act.sa_flags = 0;

    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    sigaction(SIGALRM, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    printf("Introduzca una altura maxima: ");
    scanf("%d", &maxAltura);
    system("clear");
    printf("PID proceso: %d\n\n", getpid());
    printf("El ascensor se encuentra en el piso: %d\n", pos);

    while (!fin) {
        pause();
        while(espera){
            printf("Ascensor en movimiento. Ejecutando código mientras.\n");
            sleep(2);
        }
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
            espera = 1;
            kill(sensores[pos+1], SIGUSR1);
            break;
        case SIGUSR2:
            bajar = true;
            subir = false;
            fin = false;
            espera = 1;
            kill(sensores[pos-1], SIGUSR1);
            break;
        case SIGTERM:
            fin = true;
            subir = false;
            bajar = false;
            espera = 1;
            break;
        case SIGALRM:
            fin = false;
            subir = false;
            bajar = false;
            espera = 0;
            printf("El ascensor ha llegado a su destino\n.");
            break;
        default:
            subir = false;
            bajar = false;
            fin = false;
            espera = 0;
            break;
    }
    return;
}

int ascensorSubiendo(int pos){
    printf("Ascensor subiendo...\n");
    vecesSubir = vecesSubir + 1;
    espera = 1;
    return pos + 1;
}

int ascensorBajando(int pos){
    printf("Ascensor bajando...\n");
    vecesBajar = vecesBajar + 1;
    espera = 1;
    kill(sensores[pos], SIGUSR1);
    return pos - 1;
}