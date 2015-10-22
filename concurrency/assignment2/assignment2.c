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
int gen_number(int high, int low);

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    pthread_mutex_destroy(&fork1);
    pthread_mutex_destroy(&fork2);
    pthread_mutex_destroy(&fork3);
    pthread_mutex_destroy(&fork4);
    pthread_mutex_destroy(&fork5);
    pthread_cond_destroy(&fork1_sig);
    pthread_cond_destroy(&fork2_sig);
    pthread_cond_destroy(&fork3_sig);
    pthread_cond_destroy(&fork4_sig);
    pthread_cond_destroy(&fork5_sig);
    kill(0,sig);
    exit(0);
}

int gen_number(int high, int low) {

    int num = 0;

    num = (int)genrand_int32();
    num = abs(num);
    num %= (high - low);
    if (num < low)
    {
        num = low;
    }

    return num;
}

void eat(void){
    
    int num = 0;
    
    num = gen_number(9, 2);
    sleep(num);
}

void think(void){
    int num = 0;

    num = gen_number(20, 1);
    sleep(num);
}

void plato(void){

    for(;;)
    {
        //Think
        think();
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
        eat();

        //Puts forks
        pthread_mutex_unlock(&fork1);
        pthread_cond_signal(&fork1_sig);
        pthread_mutex_unlock(&fork2);
        pthread_cond_signal(&fork2_sig);
        fork12 = 0;
    }
}

void locke(void){

    for(;;)
    {
        //Think
        think();

       //Philosopher 2, gets forks 2,3
        if(fork12 == 1)
        {
            pthread_cond_wait(&fork2_sig, &fork2);    
        }
        pthread_mutex_lock(&fork2);
        if(fork34 == 1)
        {
            pthread_cond_wait(&fork3_sig, &fork3);
        }
        pthread_mutex_lock(&fork3);
        fork23 = 1;
        
        //Eat
        eat();

       //Puts forks
        pthread_mutex_unlock(&fork2);
        pthread_cond_signal(&fork2_sig);
        pthread_mutex_unlock(&fork3);
        pthread_cond_signal(&fork3_sig);
        fork23 = 0;
    }
}

void pythagoras(void){

    for(;;)
    {
        //Think
        think();
        
        //Philosopher 3, gets forks 3,4
        if(fork23 == 1)
        {
            pthread_cond_wait(&fork3_sig, &fork3);
        }
        pthread_mutex_lock(&fork3);
        if(fork45 == 1)
        {
            pthread_cond_wait(&fork4_sig, &fork4);
        }
        pthread_mutex_lock(&fork4);
        fork34 = 1;

        //Eat
        eat();

        //Puts forks
        pthread_mutex_unlock(&fork3);
        pthread_cond_signal(&fork3_sig);
        pthread_mutex_unlock(&fork4);
        pthread_cond_signal(&fork4_sig);
        fork34 = 0;
    }
}

void socrates(void) {

    for(;;)
    {
        //Think
        think();

        //Philosopher 4, gets forks 4,5
        if(fork34 == 1)
        {
            pthread_cond_wait(&fork4_sig, &fork4);
        }
        pthread_mutex_lock(&fork4);
        if(fork51 == 1)
        {   
            pthread_cond_wait(&fork5_sig, &fork5);
        }
        pthread_mutex_lock(&fork5);
        fork45 = 1;

        //Eat
        eat();

        //Puts forks
        pthread_mutex_unlock(&fork4);
        pthread_cond_signal(&fork4_sig);
        pthread_mutex_unlock(&fork5);
        pthread_cond_signal(&fork5_sig);
        fork45 = 0;
    }
}

void marx(void) {

    //Philosopher 5, gets forks 5,1

}

int main(int argc, char **argv) {

    struct sigaction sig;
    pthread_t plato_thread;
    pthread_t locke_thread;
    pthread_t pythag_thread;
    void* plato_func = plato;
    void* locke_func = locke;
    void* pthag_func = pythagoras;

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
    pthread_create(&locke_thread, NULL, locke_func, NULL);
    pthread_create(&pythag_thread, NULL, pthag_func, NULL);

    for(;;){

    }
}
