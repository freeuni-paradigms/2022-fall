#include "semaphore.h"

#include <assert.h>
#include <stdio.h>

void SemaphoreInit(Semaphore* s, int value) {
  s->value = value;
  pthread_mutex_init(&s->lock, NULL);
  pthread_cond_init(&s->cond, NULL);
}

void SemaphoreDestroy(Semaphore* s) {
  pthread_mutex_destroy(&s->lock);
  pthread_cond_destroy(&s->cond);
}

int SemaphoreGetValue(Semaphore* s) {
  pthread_mutex_lock(&s->lock);
  int ret = s->value;
  pthread_mutex_unlock(&s->lock);
  return ret;
}

int SemaphorePost(Semaphore* s) {
  pthread_mutex_lock(&s->lock);
  s->value++;
  int ret = s->value;
  printf("Post %d\n", ret);
  pthread_cond_broadcast(&s->cond);
  pthread_mutex_unlock(&s->lock);
  return ret;
}

int SemaphoreWait(Semaphore* s) {
  pthread_mutex_lock(&s->lock);
  while (s->value == 0) {
    pthread_cond_wait(&s->cond, &s->lock);
  }
  s->value--;
  int ret = s->value;
  assert(ret >= 0);
  printf("Wait %d\n", ret);
  pthread_mutex_unlock(&s->lock);
  return ret;
}
