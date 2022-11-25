#include <pthread.h>

typedef struct {
  int value;
  pthread_mutex_t lock;
  pthread_cond_t cond;
} Semaphore;

void SemaphoreInit(Semaphore* s, int value);
void SemaphoreDestroy(Semaphore* s);
int SemaphoreGetValue(Semaphore* s);
int SemaphorePost(Semaphore* s);
int SemaphoreWait(Semaphore* s);
