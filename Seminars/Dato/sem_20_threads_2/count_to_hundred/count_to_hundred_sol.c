#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define DESTINATION 100

typedef struct {
  int* counter;
  sem_t* evenLock;
  sem_t* oddLock;
} dataT;

void* oddCounter(void* aux) {
  dataT* data = aux;
  while (1) {
    sem_wait(data->oddLock);
    int counter = ++(*data->counter);
    printf("ODD: %d\n", counter);
    sem_post(data->evenLock);
    if (counter == 99) break;
  }
}


void* evenCounter(void* aux) {
  dataT* data = aux;
  while (1) {
    sem_wait(data->evenLock);
    int counter = ++(*data->counter);
    printf("EVEN: %d\n", counter);
    sem_post(data->oddLock);
    if (counter == 100) break;
  }
}


int main() {
  int counter = 0;
  pthread_t even, odd;
  sem_t evenLock, oddLock;
  dataT data = { &counter, &evenLock, &oddLock };

  sem_init(&evenLock, 0, 0);
  sem_init(&oddLock, 0, 1);

  pthread_create(&even, NULL, evenCounter, &data);
  pthread_create(&odd, NULL, oddCounter, &data);

  pthread_exit(NULL);
  // printf("DONE\n");
  // return 0;
}