/****
 *Author: Taylor Fahlman
 *Assignment: The Consumer-Producer Problem
 *Date Due: 10/12/2015
****/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define CPUID(EAX, EBX, ECX, EDX)\
__asm__ __volatile__("cpuid;" :\
"=a"(EAX), "=b"(EBX), "=c"(ECX), "=d"(EDX)\
 : "a"(EAX)\
);

#define _rdrand_generate(num) \
({unsigned char err; \
asm volatile("rdrand %0; setc %1":"=r"(*num) "=qm"(err)); err; })

//Declare function prototypes and global index
void sig_catch(int sig);
void consume(void *buff);
void produce(void *buff);
int generate_random_number(int upper_time_limit, int lower_time_limit);
void cpuid(void);
int consumer_buffer_index;
int producer_buffer_index;
unsigned int eax,ebx,ecx,edx;

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

struct buffer_list buffer;

void cpuid(void){
    CPUID(eax,ebx,ecx,edx);
}

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

int generate_random_number(int upper_time_limit, int lower_time_limit){
    int num = 0;
    eax = 0x01;
    cpuid();
    //If the left shifted 30th bit is set, supports rdrand
    if(ecx & 1<<30) 
    {
        _rdrand_generate(&num);
    }
    else
    {
        //Use mersene twister
    }
    num %= (upper_time_limit - lower_time_limit);
    if(num < lower_time_limit)
    {
        num = lower_time_limit;
    }

    return num;
}

//Consume thread function
void consume(void *buff){

    int value;
    int time_value;
    struct buffer_item from_buffer;
    
    //acquire lock
    pthread_mutex_lock(&buffer.lock);
    //receive number from buffer item
    from_buffer = buffer.buffer[consumer_buffer_index];
    consumer_buffer_index++;
    if(consumer_buffer_index >= 32)
    {
        consumer_buffer_index = 0;
    }
    value = from_buffer.number;
    time_value = from_buffer.sleep_time;
    
    sleep(time_value);
    printf("Value:%d\n",value);
    //release lock
    pthread_mutex_unlock(&buffer.lock);
}

//Producer thread function
void produce(void *buff){
   
    struct buffer_item stuff;

    //Acquire Lock
    pthread_mutex_lock(&buffer.lock);
    //Generate sleep number
    //Generate other numbers
    //Enter numbers into buffer
    stuff.number = 1;
    stuff.sleep_time = 1;
    buffer.buffer[producer_buffer_index] = stuff;
    producer_buffer_index++;
    if(producer_buffer_index >= 32)
    {
        producer_buffer_index = 0;
    }
    //Release lock
    pthread_mutex_unlock(&buffer.lock);
}

int main(int argc, char **argv) {

    pthread_t consumer;
    pthread_t producer;
    void* consume_func = consume;
    void* produce_func = produce;
    struct sigaction sig;
    consumer_buffer_index = 0;
    producer_buffer_index = 0;

    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;

    sigaction(SIGINT, &sig, NULL);

    pthread_mutex_init(&buffer.lock, NULL);
    pthread_create(&producer, NULL, produce_func, NULL);
    pthread_create(&consumer, NULL, consume_func, NULL);
    for(;;){

    }
}
