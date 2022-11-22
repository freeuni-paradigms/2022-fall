#include <pthread.h>
#include <stdio.h>


#define ARRAY_SIZE 50
#define NUM_THREADS 10 

typedef struct {
  int* arr;
  int* sum;
  int id;
  pthread_mutex_t* lock;
} dataT;


void* calculateSum(void* aux) {
  dataT* data = (dataT*)aux;
  int curr_sum = 0;
  int slice_size = ARRAY_SIZE / NUM_THREADS;
  for (int i = 0; i < slice_size; i++) {
    curr_sum += data->arr[data->id * slice_size + i];
  }
  printf("THREAD: %d - SUM: %d\n", data->id, curr_sum);
  pthread_mutex_lock(data->lock);
  *data->sum += curr_sum;
  pthread_mutex_unlock(data->lock);
}


int main() {
  int arr[ARRAY_SIZE];
  int correct_sum = 0;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    arr[i] = i / (ARRAY_SIZE / NUM_THREADS);
    correct_sum += arr[i];
  }

  printf("\n");
  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("%d", arr[i]);
  }
  printf("\n\n ----------------- \n");

  pthread_t threads[NUM_THREADS];
  pthread_mutex_t lock;
  pthread_mutex_init(&lock, NULL);

  int sum = 0;

  dataT datas[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    dataT data = { arr, &sum, i, &lock };
    datas[i] = data;
    pthread_create(&threads[i], NULL, calculateSum, &datas[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("\n ----------------- \n");
  printf("Correct sum is: %d\n", correct_sum);
  printf("Calculated sum is %d\n\n", sum);

  return 0;
}