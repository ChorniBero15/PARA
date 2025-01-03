#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

sem_t studentsDone;
sem_t teachersFree;
bool allDone;
int numTeachers;


struct {
  bool free;
  bool eval;
  sem_t signal;
  pthread_mutex_t lock;
  sem_t evaling;
  int studentId;
} teachersInfo[MAX_NUM_TEACHERS];

void* Teacher(void* args) {
  int id = *(int*)args;
  // IMPLEMENT

  while(true) {
    sem_wait(&teachersInfo[id].signal);
    if(allDone) break;

    teachersInfo[id].eval = TeacherEvaluateStudent(id, teachersInfo[id].studentId);

    sem_post(&teachersInfo[id].evaling);
  }

  TeacherDone(id);

  return NULL;
}

void* Student(void* args) {
  int id = *(int*)args;
  // IMPLEMENT 

  while(true) {
    StudentRecordSet(id);

    sem_wait(&teachersFree);
    int indx;

    for(indx = 0; indx < numTeachers; indx++) {
      // jer mutex ufro sworia? 
      if(teachersInfo[indx].free) {
        pthread_mutex_lock(&teachersInfo[indx].lock);
        teachersInfo[indx].free = false;
        break;
      }
    }

    teachersInfo[indx].studentId = id;
    sem_post(&teachersInfo[indx].signal);
    sem_wait(&teachersInfo[indx].evaling);

    bool result = teachersInfo[indx].eval;


    pthread_mutex_unlock(&teachersInfo[indx].lock);
    teachersInfo[indx].free = true;
    sem_post(&teachersFree);


    StudentWasEvaluatedByTeacher(id, indx, result);

    if(result) break;    
  }

  StudentDone(id);

  sem_post(&studentsDone);

  return NULL;
}

void StartSchool(int num_students, int num_teachers) {
  numTeachers = num_teachers;
  sem_init(&studentsDone, 0, 0);
  sem_init(&teachersFree, 0, num_teachers);

  for(int i = 0; i < num_teachers; i++) {
    teachersInfo[i].free = true;
    sem_init(&teachersInfo[i].signal, 0, 0);
    sem_init(&teachersInfo[i].evaling, 0, 0);
    pthread_mutex_init(&teachersInfo[i].lock, NULL);
  }
  // IMPLEMENT: Initialize semaphores and mutexes if needed.
  int teacher_id[MAX_NUM_TEACHERS];
  int student_id[MAX_NUM_STUDENTS];

  for (int i = 0; i < num_teachers; ++i) {
    teacher_id[i] = i;
    pthread_t tid;
    pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
    pthread_detach(tid);
  }

  for (int i = 0; i < num_students; ++i) {
    student_id[i] = i;
    pthread_t tid;
    pthread_create(&tid, NULL, Student, &student_id[i]);
    pthread_detach(tid);
  }

  for(int i = 0; i < num_students; i++) {
    sem_wait(&studentsDone);
  }

  allDone = true;

  for(int i = 0; i < num_teachers; i++) {
    sem_post(&teachersInfo[i].signal);
  }

  // IMPLEMENT: Wait for the all students and teachers to finish.
  SchoolEnd();
}
