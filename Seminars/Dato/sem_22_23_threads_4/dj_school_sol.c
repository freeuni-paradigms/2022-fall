#include "helper.h"

#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_TEACHERS 10
#define MAX_NUM_STUDENTS 100


int student_num, teacher_num, done_students;

bool evaluations[MAX_NUM_STUDENTS];

bool teacher_busy[MAX_NUM_TEACHERS];
sem_t teacher_busy_locks[MAX_NUM_TEACHERS];

sem_t teacher_locks[MAX_NUM_TEACHERS];
sem_t student_locks[MAX_NUM_STUDENTS];

sem_t teachers_free, student_done, teacher_done;

int curr_student_for_teacher[MAX_NUM_TEACHERS];


void init(int num_students, int num_teachers) {
  student_num = num_students;
  teacher_num = num_teachers;
  done_students = 0;

  sem_init(&teachers_free, 0, teacher_num);
  sem_init(&student_done, 0, 0);
  sem_init(&teacher_done, 0, 0);

  for (int i = 0; i < num_teachers; i++) {
    teacher_busy[i] = false;
    sem_init(&teacher_busy_locks[i], 0, 1);
    sem_init(&teacher_locks[i], 0, 0);
  }

  for (int i = 0; i < MAX_NUM_STUDENTS; i++) {
    evaluations[i] = false;
  }
}


void* Teacher(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    sem_wait(&teacher_locks[id]);
    if (done_students == student_num) {
      break;
    }
    evaluations[curr_student_for_teacher[id]] = TeacherEvaluateStudent(id, curr_student_for_teacher[id]);
    sem_post(&student_locks[curr_student_for_teacher[id]]);
  }
  TeacherDone(id);
  sem_post(&teacher_done);
  return NULL;
}

void* Student(void* args) {
  int id = *(int*)args;
  // IMPLEMENT
  while (true) {
    StudentRecordSet(id);
    sem_wait(&teachers_free);
    for (int i = 0; i < teacher_num; i++) {
      sem_wait(&teacher_busy_locks[i]);
      if (teacher_busy[i]) {
        sem_post(&teacher_busy_locks[i]);
        continue;
      }
      teacher_busy[i] = true;
      sem_post(&teacher_busy_locks[i]);
      curr_student_for_teacher[i] = id;
      sem_post(&teacher_locks[i]);
      sem_wait(&student_locks[id]);
      teacher_busy[i] = false;
      StudentWasEvaluatedByTeacher(id, i, evaluations[id]);
      break;
    }
    sem_post(&teachers_free);
    if (evaluations[id] == true) {
      break;
    }
  }
  StudentDone(id);
  sem_post(&student_done);
  return NULL;
}


void StartSchool(int num_students, int num_teachers) {
  // IMPLEMENT: Initialize semaphores and mutexes if needed.
  init(num_students, num_teachers);
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
  for (int i = 0; i < num_students; i++) {
    sem_wait(&student_done);
    done_students++;
  }

  for (int i = 0; i < num_teachers; i++) {
    sem_post(&teacher_locks[i]);
  }

  for (int i = 0; i < num_teachers; i++) {
    sem_wait(&teacher_done);
  }

  SchoolEnd();
}