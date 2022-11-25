#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "vector.h"


typedef struct{
    vector vec;
    size_t elem_size;
    sem_t* write;
    sem_t* read;
    sem_t* vectorLock;
    VectorFreeFunction free_fn;
} Queue;

void init_queue(Queue *q, int elemSize, VectorFreeFunction freefn);

void enqueue(Queue *q, void *elem);

void dequeue(Queue *q, void **ptr);

void destroy_queue(Queue *q);