/****
 *Author: Taylor Fahlman
****/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//Declare fubction prototypes and global index
void consume(void *buff);
void produce(void *buff);
int buffer_index; 

//Buffer item
struct buffer_item {
    int number;
    int sleep_time; 
};

//Create buffer, 32 buffer items
struct buffer_list {
    struct buffer_item buffer[32];
    pthread_mutex_t lock;
};

struct buffer_list *buffer;

//Consume thread function
void consume(void *buff){

    int value;
    int time_value;
    struct buffer_item from_buffer;

    //acquire lock
    from_buffer = buffer->buffer[buffer_index];
    buffer_index--;
    value = from_buffer.number;
    time_value = from_buffer.sleep_time;
    
    sleep(time_value);
    printf("%d\n",value);
    //relase lock
}

//Producer thread function
void produce(void *buff){

    //Generate numbers
    
    //Acquire Lock
    //Enter numbers into buffer
    struct buffer_item stuff;
    stuff.number = 1;
    stuff.sleep_time = 1;
    buffer->buffer[buffer_index] = stuff;
    buffer_index++;
    //Release lock
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
