#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));  // Seed the random number generator with the current time

    int arr[10];

    for(int i = 0; i < 1000; i++){
        int a = rand() % 10;

        arr[a]++;
        printf("%d \n", a);
    }

    for(int i = 0; i< 10; i++) printf("%d: %d \n", i, arr[i]);
}
