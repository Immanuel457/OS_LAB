#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/unistd.h>
#include <sys/wait.h>

#define NUM_PHILOSOPHERS 5

sem_t mutex;
sem_t forks[NUM_PHILOSOPHERS];

void* philosopher(int *id) {
  while (1) {
    printf("Philosopher %d is thinking\n", *id);
    sleep(1);

    sem_wait(&mutex);
    sem_wait(&forks[*id]);
    printf("Philosopher %d picked up left fork %d\n", *id, *id);

    if (sem_trywait(&forks[(*id + 1) % NUM_PHILOSOPHERS]) != 0) {
      printf("Philosopher %d couldn't pick up right fork %d, putting down left fork\n", *id, (*id + 1) % NUM_PHILOSOPHERS);
      sem_post(&forks[*id]);
      sem_post(&mutex);
    } else {
      sem_post(&mutex);
      printf("Philosopher %d picked up right forks %d, eating\n", *id, (*id + 1) % NUM_PHILOSOPHERS);
      sleep(2);

      sem_post(&forks[*id]);
      sem_post(&forks[(*id + 1) % NUM_PHILOSOPHERS]);
      printf("Philosopher %d put down forks\n", *id);
    }
  }
}

int main() {
  sem_init(&mutex, 0, 1);
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_init(&forks[i], 0, 1);
  }

  pthread_t threads[NUM_PHILOSOPHERS];
  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    int philosopher_id = i;
    pthread_create(&threads[i], NULL, (void*)philosopher, &philosopher_id);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(threads[i], NULL);
  }

  for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
    sem_destroy(&forks[i]);
  }

  return 0;
}

