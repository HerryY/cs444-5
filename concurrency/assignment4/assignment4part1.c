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
int generate_random_number(int upper_time_limit, int lower_time_limit);

void sig_catch(int sig){
    printf("Catching signal %d\n", sig);
    kill(0,sig);
    exit(0);
}

int main(int argc, char **argv) {

}
