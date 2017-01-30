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
bool fin = false;
int T_piso = 3;
int vecesSubir = 0;
int vecesBajar = 0;
int pos = 0;
int maxAltura = 1;


int main(int argc, char *argv[]) {
    pos = atoi(argv[1]);
    system("clear");
    printf("Ejercicio 5 modificado de la practica 1\n");

    int i;
    for(i = 1; i < argc - 1; i++){
        sensores[i] = atoi(argv[i + 1]);
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

    fin = false;

    while (!fin) {
        pause();
        while (espera) {
            printf("Ascensor en movimiento. Ejecutando código mientras.\n");
            sleep(2);
        }
        printf("PID proceso: %d\n\n", getpid());
    }
    printf("\n\nProceso finalizado.\n");
    printf("El ascensor ha subido: %d veces\n", vecesSubir);
    printf("El ascensor ha bajado: %d veces\n\n", vecesBajar);

    return 0;
}

/**
 * Función usada para detectar la
 * señal SIGTERM y terminar el proceso.
 *
 * @param signum
 */
void handler(int signum) {
    switch (signum) {
        case SIGUSR1:
            if (pos == maxAltura) {
                printf("No se puede subir más.");
            } else {
                fin = false;
                espera = 1;
                printf("Ascensor subiendo...\n");
                vecesSubir = vecesSubir + 1;
                espera = 1;
                pos = pos + 1;
                kill(sensores[pos], SIGUSR2);
            }
            break;
        case SIGUSR2:
            if (pos < 2) {
                printf("No se puede bajar más.");
            } else {
                fin = false;
                espera = 1;
                printf("Ascensor bajando...\n");
                vecesBajar = vecesBajar + 1;
                espera = 1;
                kill(sensores[pos], SIGUSR2);
            }
            break;
        case SIGTERM:
            fin = true;
            printf("Recibida señal sigterm.");
            espera = 1;
            break;
        case SIGALRM:
            fin = false;
            espera = 0;
            kill(sensores[pos], SIGUSR1);
            printf("El ascensor ha llegado a su destino.\n");
            break;
        default:
            fin = false;
            espera = 0;
            break;
    }
    return;
}
