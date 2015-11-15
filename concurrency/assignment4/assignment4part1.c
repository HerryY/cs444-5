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
void process(void *);

struct buffer {
    int number;
    sem_t mutex;    
};

struct buffer buf;
void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

void process (void *buffer)
{

}

int main(int argc, char **argv) {
 
    void *proc_function = process;

    //Init the semaphore to 3 
    sem_init(&buf.mutex, 0, 3);


    for(;;){

    }
}
