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
void deleter(void *num);

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
int number;
int deleters, searchers, inserters;

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

void searcher(void *args) {

    int i;
    struct buffer_item *find = buff.head;

    while(deleters != 0)
    {
        sleep(5);
    }
    printf("Searching\n");
    if(number < buff.items)
    {
        printf("Can't find this node\n");
        return;
    }
    for(i = 0; i < number; i++)
    {
        find = find->next;
    }   
    printf("Number: %d\n", find->number);
}

void inserter(void) {

    struct buffer_item item;

    while(deleters != 0)
    {
        sleep(5);
    }
    while(inserters != 0)
    {
        sleep(5);
    }
    inserters = 1;
    item.number = gen_number(100, 1);
    buff.cur->next = &item;
    buff.cur = buff.cur->next;
    buff.items++;
    printf("Added %d to end\n", item.number);
    inserters = 0;
}

void deleter(void *arg) {

    int i;
    struct buffer_item *to_delete = buff.head;
    struct buffer_item *temp;

    while(deleters != 0)
    {
        sleep(5);
    }
    deleters = 1;
    while(inserters != 0)
    {
        sleep(5);
    }
    while(searchers != 0)
    {
        sleep(5);
    }

    printf("Delteing\n");
    if(number == 1)
    {
        printf("Not removing the head\n");
        return;
    }
    else if(number < buff.items)
    {
        printf("This node doesn't exist\n");
    }
    for(i = 0; i < number; i++)
    {
        if(i == (number - 2))
        {
            temp = to_delete;
        }
        to_delete = to_delete->next;          
    }
    
    temp->next = to_delete->next;
    free(to_delete);
    printf("Done Deleting\n");
    deleters = 0;
}


int main(int argc, char **argv) {

    struct sigaction sig;
    struct buffer_item init_item;
    int choice;
    pthread_t thread1, thread2, thread3, thread4;
    void *delete_func = deleter;
    void *insert_func = inserter;
    void *search_func = searcher;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sig.sa_handler = sig_catch;
    sigaction(SIGINT, &sig, NULL);

    init_item.next = NULL;
    init_item.number = 1;
    buff.head = &init_item;

    deleters = 0;
    searchers = 0;
    inserters = 0;
    number = 2;
    
    pthread_create(&thread1, NULL, insert_func, NULL);
    pthread_create(&thread2, NULL, insert_func, NULL);
    pthread_create(&thread3, NULL, search_func, NULL);
    pthread_create(&thread4, NULL, delete_func, NULL);

    for(;;) {
        pthread_t new;
        choice = gen_number(3, 1);
        if(choice == 1)
        {
        }
        number = gen_number(buff.items, 1);
    }
}
