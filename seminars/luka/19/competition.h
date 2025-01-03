#ifndef PARADIGMS_ROBOTS_COMPETITION_H_
#define PARADIGMS_ROBOTS_COMPETITION_H_

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include "robot.h"

#define MAX_ROBOTS 1000

typedef struct {
  Robot* winner;
  Robot* robots[MAX_ROBOTS];

  bool canAddNew;
  int numRobots;
  int numBattles;
  int totalRobots;
  int totalBattles;

  pthread_mutex_t lock;
  pthread_t thread;
} Competition;

// უკეთებს შეჯიბრს ინიციალიზაციას.
void CompetitionInit(Competition* comp);
// უნდა გაუშვას შეჯიბრის მენეჯმენტისთვის მთავარი ნაკადი.
void CompetitionStart(Competition* comp);
// უნდა აკრძალოს შეჯიბრში ახალი მონაწილეების დამატება,
// დაელოდოს უკვე დამატებულ მონაწილეებს შორის გამარჯვებულს,
// და დააბრუნოს იგი.
const Robot* CompetitionStop(Competition* comp);
// აბრუნებს true თუ რობოტი წარმატებით დაემატა შეჯიბრში,
// და false წინააღმდეგ შემთხვევაში.
bool CompetitionAddParticipant(Competition* comp, const Robot* robot);

#endif // PARADIGMS_ROBOTS_COMPETITION_H_
