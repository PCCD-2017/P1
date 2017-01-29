/*
 * Ejercicio 6
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int eleccion = 0;
    while(eleccion != 3 ){
        system("clear");
        printf("Introduzca una orden para el pulsador.");
        printf("\n\t1 : Subir.\n\t2 : Bajar.\n\t3 : Salir.\n");
        fscanf(stdin, "%d", &eleccion);
        switch(eleccion){
            case 1:
                printf("Ha seleccionado subir.\n\n");
                kill(atoi(argv[1]), SIGUSR1);
                break;
            case 2:
                printf("Ha seleccionado bajar.\n\n");
                kill(atoi(argv[1]), SIGUSR2);
                break;
            case 3:
                printf("Ha seleccionado salir. Adiós.");
                kill(atoi(argv[1]), SIGKILL);
                break;
            default:
                printf("Orden no válida.");
                break;
        }
    }
    return 0;
}