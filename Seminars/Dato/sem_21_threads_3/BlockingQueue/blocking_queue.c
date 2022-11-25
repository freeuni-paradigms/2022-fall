#include "blocking_queue.h"

#define QUEUESIZE 50


void init_queue(Queue* q, int elemSize, VectorFreeFunction freefn) {
    q->elem_size = elemSize;
    VectorNew(&q->vec, elemSize, freefn, 0);
    q->free_fn = freefn;
    q->vectorLock = malloc(sizeof(sem_t));
    sem_init(q->vectorLock, 0, 1);
    q->write = malloc(sizeof(sem_t));
    sem_init(q->write, 0, QUEUESIZE);
    q->read = malloc(sizeof(sem_t));
    sem_init(q->read, 0, 0);
}

void enqueue(Queue* q, void* elem) {
    sem_wait(q->write);
    sem_wait(q->vectorLock);
    VectorAppend(&q->vec, elem);
    sem_post(q->vectorLock);
    sem_post(q->read);
}

void dequeue(Queue* q, void** ptr) {
    sem_wait(q->read);
    sem_wait(q->vectorLock);
    void* elem = VectorNth(&q->vec, 0);
    void* newElem = malloc(q->elem_size);
    memcpy(newElem, elem, q->elem_size);
    *ptr = newElem;
    VectorDelete(&q->vec, 0);
    sem_post(q->vectorLock);
    sem_post(q->write);
}

void destroy_queue(Queue* q) {
    VectorDispose(&q->vec);
    sem_destroy(q->vectorLock);
    sem_destroy(q->read);
    sem_destroy(q->write);
    free(q->vectorLock);
    free(q->read);
    free(q->write);
}