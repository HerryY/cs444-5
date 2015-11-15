/****
 *Author: Taylor Fahlman
 *Assignment: Shareable resource with 3 available slots
 *Date Due: 11/19/2015
****/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void sig_catch(int sig);
void barber(void *);
void customer(void *);
void get_hair_cut(void);

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

void barber(void *queue)
{

}

void customer(void *queue)
{

}

void get_hair_cut()
{

}

int main(int argc, char **argv) {

    
    

}
