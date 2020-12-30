#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_sem.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

#define MAX_OCCUPANCY      3
#define NUM_ITERATIONS     100
#define NUM_PEOPLE         20

enum Endianness {LITTLE = 0, BIG = 1};
const static enum Endianness otherEndianness [] = {BIG, LITTLE};

struct Well {

  uthread_sem_t mx;
  uthread_sem_t done;
  uthread_sem_t allowedEntry[2];
  int peopleInside;
  enum Endianness personType;
  int count[2];

};

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_PEOPLE)
int           entryTicker;
int           waitingHistogram         [WAITING_HISTOGRAM_SIZE];
int           waitingHistogramOverflow;
uthread_sem_t waitingHistogramMutex;
int           occupancyHistogram       [2] [MAX_OCCUPANCY + 1];

struct Well* createWell() {

  struct Well* well = malloc(sizeof (struct Well));
  well->mx = uthread_sem_create(1);
  well->done = uthread_sem_create(0);
  well->allowedEntry[LITTLE] = uthread_sem_create (0);
  well->allowedEntry[BIG] = uthread_sem_create (0);
  well->peopleInside = 0;
  well->personType = 0;
  well->count[LITTLE] = 0;
  well->count[BIG] = 0;

  return well;
}

void recordEntry(struct Well* well, enum Endianness type) {

  assert(well->peopleInside == 0 || well->personType == type);
  assert(well->peopleInside < MAX_OCCUPANCY);

  well->peopleInside++;
  well->personType = type;
  entryTicker++;
  occupancyHistogram[well->type][well->peopleInside]++;

}

void enterWell(struct Well* well, enum Endianness g) {

  uthread_sem_wait (well->mutex);

    bool isEmpty = (peopleInside == 0);
    bool enoughRoom = (well->peopleInside < MAX_OCCUPANCY);
    bool sameType = (well->personType == g);
    bool waitOtherType = (well->peopleInside[otherEndianness[g]] > 0);
    bool canEnter = (isEmpty || (enoughRoom && sameType && !waitOtherType));

    if (canEnter) {

      recordEntry(well, g);

    } else {

      well->count[g]++;
    }

  uthread_sem_signal (well->mutex);

  if (!canEnter) {

    uthread_sem_wait(well->canEnter[g]);
  }
}

void leaveWell(struct Well* well) {

  uthread_sem_wait (well->mutex);

    well->peopleInside = well->peopleInside - 1;

    enum Endianness inPersonType = well->personType;
    enum Endianness outPersonType = otherEndianness[inPersonType];

    if (well->count[outPersonType] > 0) {

      if (well->peopleInside == 0) {

        for (int i = 0; i < well->count[outPersonType] && i < MAX_OCCUPANCY; i++) {

          well->count[outPersonType] = well->count[outPersonType] - 1;
          recordEntry(well, outPersonType);
          uthread_sem_signal(well->canEnter[outPersonType]);
        }
      }

    } else if (well->count[inPersonType]) {

      well->count[inPersonType]--;
      recordEntry(well, inPersonType);
      uthread_sem_signal(well->canEnter[inPersonType]);

    }

  uthread_sem_signal(well->mx);
}

void recordWaitingTime(int time) {

  uthread_sem_wait(waitingHistogramMutex);

    if (time < WAITING_HISTOGRAM_SIZE) {

      waitingHistogram[time] = waitingHistogram[time] + 1;

    } else {

      waitingHistogramOverflow = waitingHistogramOverflow + 1;
    }

  uthread_sem_signal(waitingHistogramMutex);
}

void* person(void* w) {

  struct Well* well = w;
  enum Endianness type = random() & 1;

  for(int i = 0; i < NUM_ITERATIONS; i++) {

    int start = entryTicker;
    enterWell(well, type);
    recordWaitingTime(entryTicker - start - 1);

    for(int i = 0; i < NUM_PEOPLE; i++) {

      uthread_yield();
    }

    leaveWell (well);

    for(int i = 0; i < NUM_PEOPLE; i++) {

      uthread_yield();
    }
  }

  uthread_sem_signal(well->done);
  return NULL;
}

/*void mysrandomdev() {
  unsigned long seed;
  int f = open ("/dev/random", O_RDONLY);
  read    (f, &seed, sizeof (seed));
  close   (f);
  srandom (seed);
}*/

int main (int argc, char** argv) {
  uthread_init (1);
  struct Well* well = createWell();
  uthread_t pt[NUM_PEOPLE];
  waitingHistogramMutex = uthread_sem_create (1);

  for (int i = 0; i < NUM_PEOPLE; i++) {

    uthread_detach(uthread_create(person, well));
  }

  for (int i = 0; i < NUM_PEOPLE; i++) {

    uthread_sem_wait(well->done);
  }

  printf ("Times with 1 little endian %d\n", occupancyHistogram [LITTLE]   [1]);
  printf ("Times with 2 little endian %d\n", occupancyHistogram [LITTLE]   [2]);
  printf ("Times with 3 little endian %d\n", occupancyHistogram [LITTLE]   [3]);
  printf ("Times with 1 big endian    %d\n", occupancyHistogram [BIG] [1]);
  printf ("Times with 2 big endian    %d\n", occupancyHistogram [BIG] [2]);
  printf ("Times with 3 big endian    %d\n", occupancyHistogram [BIG] [3]);
  printf ("Waiting Histogram\n");
  for (int i=0; i<WAITING_HISTOGRAM_SIZE; i++)
  if (waitingHistogram [i])
  printf ("  Number of times people waited for %d %s to enter: %d\n", i, i==1?"person":"people", waitingHistogram [i]);
  if (waitingHistogramOverflow)
  printf ("  Number of times people waited more than %d entries: %d\n", WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
}
