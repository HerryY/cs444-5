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
int fork12 = 0, fork23 = 0, fork34 = 0, fork45 = 0, fork51 = 0;
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

    for(;;)
    {

        //Think
        //Check that the adjacent philos dont have forks
        //If they do, wait on signal 

        //Philosopher 1, gets forks 1,2
        fork12 = 1;
        pthread_mutex_lock(&fork1);
        pthread_mutex_lock(&fork2);

        //Do eat
    
        pthread_mutex_unlock(&fork1);
        pthread_mutex_unlock(&fork2);
        fork12 = 0;

        //Signal others

    }
    //Signal on fork12
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
    
    pthread_mutex_init(&fork1, NULL);
    pthread_mutex_init(&fork2, NULL);
    
}
