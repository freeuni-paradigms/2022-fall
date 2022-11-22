#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_RACERS 10
#define DISTANCE 100

void RandomSleep() {
  int k = rand();
  if (k % 3 == 0) {
    usleep(100);
  }
}

typedef struct {
  int tId;
  int* place;
  sem_t* lock;
} dataT;

void* race(void* aux) {
  dataT* data = aux;

  for (int i = 0; i < DISTANCE; i++) {
    RandomSleep();
  }

  sem_wait(data->lock);
  int place = ++(*data->place);
  printf("%d's place is: %d\n", data->tId, place);
  sem_post(data->lock);
  // printf("%d's place is: %d\n", data->tId, place);
}

int main() {
  int place = 0;
  pthread_t racers[NUM_RACERS];
  sem_t lock;

  sem_init(&lock, 0, 1);

  for (int i = 0; i < NUM_RACERS; i++) {
    dataT data = { i, &place, &lock };
    dataT* dataPtr = malloc(sizeof(dataT));
    *dataPtr = data;
    pthread_create(&racers[i], NULL, race, dataPtr);
  }

  pthread_exit(NULL);
  // printf("DONE\n");
  // return 0;
}