#include "helper.h"
#include "amocana.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_CONTESTANTS = 100

void* judge() {
    return NULL;
}

void* registrar() {
    return NULL;
}

void* contestant() {
    return NULL;
}

void* host() {
    return NULL;
}

void addContestant(int contestantId);

void contestClosed(int sleepTime) {
    sleep(sleepTime);

};

void startTheContest(int numJudges, int numRegistrars) {

}
