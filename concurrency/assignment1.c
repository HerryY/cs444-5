/****
 *Author: Taylor Fahlman
 *
 *
 *
****/


#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void *consume(void *buff);
void *produce(void *buff);

struct buffer_item {
    int number;
    int sleep_time; 
};

void *consume(void *buff){

    return;
}

void *produce(void *buff){

    return;
}

int main(int argc, char **argv) {

    pthread_t *consumer;
    pthread_t *producer;

    pthread_create(consumer, NULL, consume, NULL);
    return 0;
}
