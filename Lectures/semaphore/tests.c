#include "semaphore.h"

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void RandomSleep() {
  sleep(rand() % 2);
}

void One() {
  Semaphore s;
  SemaphoreInit(&s, 1);
  printf("%d\n", SemaphoreGetValue(&s));
  SemaphoreWait(&s);
  printf("%d\n", SemaphoreGetValue(&s));
  SemaphorePost(&s);
  printf("%d\n", SemaphoreGetValue(&s));
  SemaphoreDestroy(&s);
}

void* Post(void* args) {
  Semaphore* s = args;
  for (int i = 0; i < 100; ++i) {
    RandomSleep();
    SemaphorePost(s);
  }
  return NULL;
}

void* Wait(void* args) {
  Semaphore* s = args;
  for (int i = 0; i < 100; ++i) {
    RandomSleep();
    SemaphoreWait(s);
  }
  return NULL;
}

void MultipleThreads() {
  Semaphore s;
  SemaphoreInit(&s, 0);
  pthread_t poster;
  pthread_create(&poster, NULL, Post, &s);
  pthread_t waiter;
  pthread_create(&waiter, NULL, Wait, &s);
  pthread_join(poster, NULL);
  pthread_join(waiter, NULL);
  SemaphoreDestroy(&s);
}

int main(int argc, char** argv) {
  // One();
  MultipleThreads();
  return 0;
}
