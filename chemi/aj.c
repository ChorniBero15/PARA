#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10
#define ARR_SIZE 100000
#define MAX_NUM 10000
#define STEP_SIZE 10000

typedef struct {
    int a;
    int b; 
    int c;
} info;

info Info[12];

int main() {
    Info[4].a = 0;

    printf("%d", Info[4].a);
    printf("%d", Info[323].b);
}