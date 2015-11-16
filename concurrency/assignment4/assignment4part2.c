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
void cut_hair(void);
void line_pop(void);
void line_push(void);

struct chair {

    int taken;
    struct chair *next;
};

struct line {

    int number_of_customers;
    int chairs;
    struct chair *current;
    struct chair *next;
};

pthread_mutex_t barber_lock;
struct line global_queue;

void sig_catch(int sig){
    
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

void barber(void *queue)
{
    int i;

    for(;;)
    {
        i = 0;
        while(global_queue.number_of_customers == 0)
        {
            printf("The Barber is sleeping\n");
            sleep(5);
        }
    
        for(i = 0; i < global_queue.number_of_customers; i++)
        {
            //accuire mutex
             
            
            //Cut hair
            cut_hair();
        }
    }
}

void customer(void *queue)
{

}


void cut_hair()
{

}

void get_hair_cut()
{

}

int main(int argc, char **argv) {

    
    

}
