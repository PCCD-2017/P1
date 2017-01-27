//
// Created by Ruben Perez Vaz on 26/1/17.
//
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    kill(atoi(argv[2]), atoi(argv[1]));
    return 0;
}