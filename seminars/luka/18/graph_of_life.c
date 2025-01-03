#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int numDoneReading;
int numDoneWriting;
int numThreads;
pthread_mutex_t magariLock;
pthread_cond_t magariCond;

typedef struct {
  int id;
  int numIterations;
} Arg;

void* func(void* arg) {
  int id = ((Arg*)arg)->id;
  int numIt = ((Arg*)arg)->numIterations;

  for(int i = 0; i < numIt; i++) {
      int numN = GetNumNeighbors(id);
      int* nums = GetNeighbors(id);

      int aliveN = 0;

      for(int i = 0; i < numN; i++) if(IsAlive(*(nums+i))) aliveN++;

      pthread_mutex_lock(&magariLock);
      numDoneReading++;
      if(numDoneReading == numThreads) {
        numDoneReading = 0;
        pthread_cond_broadcast(&magariCond);
      } else {
        pthread_cond_wait(&magariCond, &magariLock); 
      }

      if(aliveN == 2 || aliveN == 3) SetIsAlive(id, true);
      else SetIsAlive(id, false);

      numDoneWriting++;
      if(numDoneWriting == numThreads) {
        PrintAll();
        numDoneWriting = 0;
        pthread_cond_broadcast(&magariCond);
      } else pthread_cond_wait(&magariCond, &magariLock); // 

      pthread_mutex_unlock(&magariLock);
  }

  return NULL;
}


void SimulateGraphOfLife(int num_nodes, int num_iterations) {
  pthread_t threads[num_nodes];
  Arg nodeArgs[num_nodes]; 

  numThreads = num_nodes;
  numDoneReading = 0;
  numDoneWriting = 0;

  pthread_mutex_init(&magariLock, NULL);
  pthread_cond_init(&magariCond, NULL);

  for(int i = 0; i < num_nodes; i++) { 
    nodeArgs[i].id = i;
    nodeArgs[i].numIterations = num_iterations;
    pthread_create(&threads[i], NULL, func, &nodeArgs[i]);  
  }

  for(int i = 0; i < num_nodes; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&magariLock);
  pthread_cond_destroy(&magariCond);

  return;
}
