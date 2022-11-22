#include <pthread.h>
#include <stdio.h>


#define ARRAY_SIZE 50
#define NUM_THREADS 10 


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


  int sum = 0;

  printf("\n ----------------- \n");
  printf("Correct sum is: %d\n", correct_sum);
  printf("Calculated sum is %d\n\n", sum);

  return 0;
}