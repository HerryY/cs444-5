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
pthread_mutex_t fork12, fork23, fork34, fork45, fork51;
void plato(void);
void locke(void);
void pythagoras(void);
void socrates(void);
void marx(void);
void eat(void);
void think(void);

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

void eat(void){

}

void think(void){

}

void plato(void){

    //Philosopher 1, gets forks 1,2
}

void locke(void){

    //Philosopher 2, gets forks 2,3
}

void pythagoras(void){

    //Philosopher 3, gets forks 3,4
}

void socrates(void) {

    //Philosopher 4, gets forks 4,5 
}

void marx(void) {

    //Philosopher 5, gets forks 5,1

}

int main(int argc, char **argv) {

    struct sigaction sig;
    
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);

    
}
