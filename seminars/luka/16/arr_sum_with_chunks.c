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

void generateArray(int *arr) {
    int sum = 0;
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % MAX_NUM;
        sum += arr[i];
    }
    printf("Sum of array is %d\n", sum);
}

typedef struct{
    int* start;

    int* ans;
    sem_t* sem;
} Args;

void* sum(void* arg_ptr){
    Args arg = *(Args*)arg_ptr;

    int sum = 0;
    int* curr;
    
    for(int i = 0; i < STEP_SIZE; i++) {
        curr = arg.start + i;

        sum += *curr;
    }

    sem_wait(arg.sem);
    *arg.ans += sum;
    sem_post(arg.sem);

    return NULL;
}

int main() {
    int ans = 0;

    int step_size = ARR_SIZE / NUM_THREADS;

    int arr[ARR_SIZE];

    generateArray(arr);

    sem_t sem;
    sem_init(&sem, 0, 1);
    pthread_t threads[NUM_THREADS];
    Args args[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++) {
        args[i].ans = &ans;
        args[i].sem = &sem;
        args[i].start = (arr + i * step_size);

        pthread_create(&threads[i], NULL, sum, &args[i]);
    }

    for(int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);

    printf("%d \n", ans);

    return 0;
}