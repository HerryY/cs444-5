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

void consume(void *buff);
void produce(void *buff);


struct buffer_item {
    int number;
    int sleep_time; 
};

struct buffer_item *buffer;

void consume(void *buff){

    int value;
    int time_value;
    struct buffer_item from_buffer;

    from_buffer = *buffer;
    value = from_buffer.number;
    time_value = from_buffer.sleep_time;
    
    //acquire lock
    sleep(time_vale);
    print(value)
    //relase lock
}

void produce(void *buff){

    //Generate numbers
    //Enter numbers into buffer
    struct buffer_item stuff;
    stuff.number = 1;
    stuff.sleep_time = 1;
    buffer = &stuff;
}

int main(int argc, char **argv) {

    pthread_t *consumer;
    pthread_t *producer;
    void* consume_func = consume;
    void* produce_func = produce;
    
    pthread_create(producer, NULL, produce_func, NULL);
    pthread_create(consumer, NULL, consume_func, NULL);
    return 0;
}
