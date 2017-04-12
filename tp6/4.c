// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_THREADS 10
void *PrintHello(void *threadnum)
{
  pid_t tid;
  tid = gettid();
  printf("Thread TID: %d!\n", tid);
  sleep(1);
  pthread_exit((int *)threadnum);
}
int main()
{
  pthread_t threads[NUM_THREADS];
  int t;
  for(t=0; t< NUM_THREADS; t++){
    int *copy = malloc(sizeof(int));
    *copy = t;
    printf("Creating thread %d\n", t);
    pthread_create(&threads[t], NULL, PrintHello, (void *)copy);
  }
  pthread_exit(0);
}
