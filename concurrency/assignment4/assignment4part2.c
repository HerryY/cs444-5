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
    int copy_of_customer_number;

    for(;;)
    {
        i = 0;
        copy_of_customer_number = global_queue.number_of_customers;
        while(global_queue.number_of_customers == 0)
        {
            printf("The Barber is sleeping\n");
            sleep(5);
        }
    
        for(i = 0; i < copy_of_customer_number; i++)
        {
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
    
    printf("Cutting hair\n");
    sleep(10);
    printf("Done cutting hair\n");
}

void get_hair_cut()
{
    printf("Getting hair cut\n");
    sleep(10);
    printf("Done getting hair cut\n");
    
}

int main(int argc, char **argv) {

    for(;;)
    {

    }
    

}
