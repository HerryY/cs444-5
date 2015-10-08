/****
 *Author: Taylor Fahlman
 *
 *
 *
****/


#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void consume(void *buff);
void produce(void *buff);
int buffer_index; 

struct buffer_item {
    int number;
    int sleep_time; 
};

//Create buffer, 32 buffer items
struct buffer_item *buffer[32];

void consume(void *buff){

    int value;
    int time_value;
    struct buffer_item from_buffer;

    from_buffer = *buffer[buffer_index];
    buffer_index--;
    value = from_buffer.number;
    time_value = from_buffer.sleep_time;
    
    //acquire lock
    sleep(time_value);
    //print(value);
    //relase lock
}

void produce(void *buff){

    //Generate numbers
    //Enter numbers into buffer
    struct buffer_item stuff;
    stuff.number = 1;
    stuff.sleep_time = 1;
    buffer[buffer_index] = &stuff;
    buffer_index++;
}

int main(int argc, char **argv) {

    pthread_t *consumer;
    pthread_t *producer;
    void* consume_func = consume;
    void* produce_func = produce;
    buffer_index = 0;

    pthread_create(producer, NULL, produce_func, NULL);
    pthread_create(consumer, NULL, consume_func, NULL);
    return 0;
}
