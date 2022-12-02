#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100

typedef struct {
  pthread_mutex_t lock;
  bool available;
  int student;
  sem_t signal;
  sem_t set_evaluated;
  bool good;
} TeacherArgs;

int g_num_teachers;
sem_t teachers_lock;
TeacherArgs teacher[MAX_NUM_TEACHERS];
sem_t student_done;
sem_t teacher_done;
bool quit;

void Init(int num_teachers){
  sem_init(&teacher_done, 0, 0);
  sem_init(&student_done, 0, 0);
  sem_init(&teachers_lock, 0, num_teachers);
  for (int i = 0; i < MAX_NUM_TEACHERS; i++){
    sem_init(&teacher[i].signal, 0, 0);
    sem_init(&teacher[i].set_evaluated, 0, 0);
    pthread_mutex_init(&teacher[i].lock, NULL);
    teacher[i].available = true;
    teacher[i].good = false;
  }
}

void* Teacher(void* args) {
  int id = *(int*)args;
  while (true) {
    sem_wait(&teacher[id].signal);
    if (quit) {
      break;
    }
    teacher[id].good = TeacherEvaluateStudent(id, teacher[id].student);
    sem_post(&teacher[id].set_evaluated);
  }
  TeacherDone(id);
  sem_post(&teacher_done);
  return NULL;
}

void* Student(void* args) {
  int id = *(int*)args;
  bool good = false;
  while (!good) {
    StudentRecordSet(id);
    sem_wait(&teachers_lock);
    for (int i = 0; i < g_num_teachers; ++i) {
      pthread_mutex_lock(&teacher[i].lock);
      if (!teacher[i].available) {
	pthread_mutex_unlock(&teacher[i].lock);
	continue;
      }
      teacher[i].available = false;
      teacher[i].student = id;
      pthread_mutex_unlock(&teacher[i].lock);
      sem_post(&teacher[i].signal);
      sem_wait(&teacher[i].set_evaluated);
      good = teacher[i].good;
      pthread_mutex_lock(&teacher[i].lock);
      teacher[i].available = true;
      pthread_mutex_unlock(&teacher[i].lock);
      StudentWasEvaluatedByTeacher(id, i, good);
      break;
    }
    sem_post(&teachers_lock);
  }
  StudentDone(id);
  sem_post(&student_done);
  return NULL;
}

void StartSchool(int num_students, int num_teachers) {
  // IMPLEMENT: initialize semaphores and mutexes if needed.
  Init(num_teachers);
  g_num_teachers = num_teachers;
  quit = false;
  int teacher_id[MAX_NUM_TEACHERS];
  int student_id[MAX_NUM_STUDENTS];
  for (int i = 0; i < num_teachers; ++i) {
    teacher_id[i] = i;
    pthread_t tid;
    pthread_create(&tid, NULL, Teacher, &teacher_id[i]);
    pthread_detach(tid);
  }
  for (int i = 0; i < num_students; ++i) {
    student_id[i] = i;
    pthread_t tid;
    pthread_create(&tid, NULL, Student, &student_id[i]);
    pthread_detach(tid);
  }
  // IMPLEMENT: Wait for the all students and teachers to finish.
  for (int i = 0; i < num_students; ++i) {
    sem_wait(&student_done);
  }
  quit = true;
  for (int i = 0; i < num_teachers; ++i) {
    sem_post(&teacher[i].signal);
  }
  for (int i = 0; i < num_teachers; ++i) {
    sem_wait(&teacher_done);
  }
  SchoolEnd();
}
