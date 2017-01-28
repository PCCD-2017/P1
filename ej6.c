/*
 * Ejercicio 6
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

const char *PIDAscensor = 0;

int main(int argc, char* argv[]){
    int entrada = 0;
    printf("Introduzca el PID del proceso Ascensor.");
    scanf("%d", &PIDAscensor);
    while(entrada != 3 ){
        printf("Introduzca una orden para el pulsador.");
        printf("\n\t1 : Subir.\n\t2 : Bajar.\n\t3 : Salir.\n");
        scanf("%d", &entrada);
        switch(entrada){
            case 1:
                printf("Ha seleccionado subir.");
                kill(atoi(PIDAscensor), SIGUSR1);
                break;
            case 2:
                printf("Ha seleccionado bajar.");
                kill(atoi(PIDAscensor), SIGUSR2);
                break;
            case 3:
                printf("Ha seleccionado salir. Adiós.");
                kill(atoi(PIDAscensor), SIGKILL);
                break;
            default:
                printf("Orden no válida.");
                break;
        }
    }
    return 0;
}