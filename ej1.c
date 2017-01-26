#include <stdio.h>
#include <unistd.h>


/**
 * Ejercicio 1: Escriba un proceso p1 que espere a
 * recibir una señal utilizando la función pause()
 * (consulte el man de dicha función). Envíe a dicho
 * proceso, utilizando el comando kill, cada una de las
 * señales definidas y compruebe la acción por defecto
 * de cada una de ellas.
 *
 * @return 0
 */
int main() {
    printf("Ejercicio 1 - Practica 1.\n");
    printf("PID : %d\n", getpid());
    printf("%d\n", pause());
    printf("Pause interrumpido\n");
    return 0;
}