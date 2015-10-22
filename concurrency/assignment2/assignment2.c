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
#include "mt19937ar.c"

void sig_catch(int sig);
pthread_mutex_t fork1, fork2, fork3, fork4, fork5;
int fork12 = 0, fork23 = 0, fork34 = 0, fork45 = 0, fork51 = 0;
pthread_cond_t fork1_sig, fork2_sig, fork3_sig, fork4_sig, fork5_sig;
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
        if(fork51 == 1)
        {
            pthread_cond_wait(&fork1_sig, &fork1);
        }
        pthread_mutex_lock(&fork1);
        if(fork23 == 1)
        {
            pthread_cond_wait(&fork2_sig, &fork2);
        }
        pthread_mutex_lock(&fork2);
        fork12 = 1;
        //Do eat
    
        pthread_mutex_unlock(&fork1);
        pthread_cond_signal(&fork1_sig);
        pthread_mutex_unlock(&fork2);
        pthread_cond_signal(&fork2_sig);

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
    pthread_t plato_thread;
    void* plato_func = plato;

    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);
    
    pthread_mutex_init(&fork1, NULL);
    pthread_mutex_init(&fork2, NULL); 
    pthread_mutex_init(&fork3, NULL); 
    pthread_mutex_init(&fork4, NULL); 
    pthread_mutex_init(&fork5, NULL); 
    pthread_cond_init(&fork1_sig, NULL);
    pthread_cond_init(&fork2_sig, NULL);
    pthread_cond_init(&fork3_sig, NULL);
    pthread_cond_init(&fork4_sig, NULL);
    pthread_cond_init(&fork5_sig, NULL);

    pthread_create(&plato_thread, NULL, plato_func, NULL);
}
