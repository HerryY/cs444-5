/****
 *Author: Taylor Fahlman
 *Assignment: The Dining Philosophers Problem
 *Date Due: 10/12/2015
****/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <mt19937ar.c>

void sig_catch(int sig);
pthread_mutex_t fork1, fork2, fork3, fork4, fork5;
void plato(void);
void locke(void);
void pythagoras(void);
void socrates(void);
void marx(void);

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

void plato(void){

}

void locke(void){

}

void pythagoras(void){

}

void socrates(void) {

}

void marx(void) {

}

int main(int argc, char **argv) {

    struct sigaction sig;
    
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);

    for(;;)
    {

    }
}
