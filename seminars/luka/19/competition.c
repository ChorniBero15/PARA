#include "competition.h"

#include <stdlib.h>
#include <stdio.h>

#include "robot.h"

struct {
Competition* comp;
Robot* robot1;
Robot* robot2;
int ind; 
} battleArg[505];

void* battle(void* arg) {
  int id = *(int*)arg;

  printf("Fighting %d %d\n", battleArg[id].robot1->id, battleArg[id].robot2->id);

  bool fwon = RobotFightWith(battleArg[id].robot1, battleArg[id].robot2);

  pthread_mutex_lock(&(battleArg[id].comp->lock));

  battleArg[id].comp->numRobots++;
  if(fwon) {
    battleArg[id].comp->robots[battleArg[id].ind] = battleArg[id].robot1;
    battleArg[id].comp->winner = battleArg[id].robot1;
  } else {
    battleArg[id].comp->robots[battleArg[id].ind] = battleArg[id].robot2;
    battleArg[id].comp->winner = battleArg[id].robot2;
  }
  battleArg[id].comp->numBattles--;

  pthread_mutex_unlock(&(battleArg[id].comp->lock));

  return NULL;

}

void* func(void* arg) {
  Competition* comp = arg;

  printf("CompStarted \n");

  int ids[505];

  while(true) {

    pthread_mutex_lock(&comp->lock);
    if(!comp->canAddNew && comp->numBattles == 0 && comp->numRobots == 1){
      pthread_mutex_unlock(&comp->lock);
      break;      
    }

    printf("Finding Robot \n");

    if(comp->numRobots > 1) {
      comp->numRobots-=2;
      Robot* r1 = NULL; Robot* r2 = NULL; int indx = -1;
      for(int i = 0; i < comp->totalRobots; i++) {
        if(comp->robots[i] && r1) {
          r2 = comp->robots[i];
          comp->robots[i] = NULL;
        } else if(comp->robots[i]) {
          r1 = comp->robots[i];
          comp->robots[i] = NULL;
          indx = i;
        }
      }

      battleArg[comp->totalBattles].comp = comp;
      battleArg[comp->totalBattles].ind = indx;
      battleArg[comp->totalBattles].robot1 = r1;
      battleArg[comp->totalBattles].robot2 = r2;

      ids[comp->totalBattles] = comp->totalBattles;
      comp->totalBattles++;
      comp->numBattles++;

      pthread_t thread;
      pthread_create(&thread, NULL, battle, &ids[comp->totalBattles]);
      pthread_detach(thread);
    }

    pthread_mutex_unlock(&comp->lock);

  }

  printf("CompEnded \n");

  return NULL;
}

void CompetitionInit(Competition* comp) {
  for(int i = 0; i < 1000; i++) comp->robots[i] = NULL;

  comp->totalBattles = 0;
  comp->totalRobots = 1;
  comp->numBattles = 0;
  comp->winner = NULL;
  comp->canAddNew = true;
  comp->numRobots = 0;
  pthread_mutex_init(&comp->lock, NULL);
}

void CompetitionStart(Competition* comp) {
  pthread_create(&comp->thread, NULL, func, comp);
}

const Robot* CompetitionStop(Competition* comp) {
  printf("===================\n No More Additions \n");


  pthread_mutex_lock(&comp->lock);
  comp->canAddNew = false;
  pthread_mutex_unlock(&comp->lock);

  printf("===================\n Mutex Unlocked \n");

  pthread_join(comp->thread, NULL);

  printf("===================\n Winner Detected \n");

  return comp->winner;
  // waiting for the winner
}

bool CompetitionAddParticipant(Competition* comp, const Robot* robot) {
  pthread_mutex_lock(&comp->lock);
  if(comp->canAddNew) {
    comp->robots[comp->totalRobots-1] = robot;
    comp->totalRobots++;
    comp->numRobots++;
    pthread_mutex_unlock(&comp->lock);
    return true;
  } 
  else {
    pthread_mutex_unlock(&comp->lock);
    return false;
  }
}
