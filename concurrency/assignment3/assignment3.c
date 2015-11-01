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
int gen_number(int high, int low);
void searcher(void *num);
void inserter(void);
void deleter(void);

struct buffer_item {
    int number;
    struct buffer_item* next;
};

struct buffer {
    struct buffer_item* head;
    struct buffer_item* cur;
    int items;
};

struct buffer buff;

void sig_catch(int sig){
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

void searcher(void *num) {
    
}

void inserter(void) {

    struct buffer_item item;

    item.number = gen_number(100, 1);
    buff.cur->next = &item;
    buff.cur = buff.cur->next;
    buff.items++;
}

void deleter(void) {

}


int main(int argc, char **argv) {

    struct sigaction sig;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);

    for(;;) {

    }
}
