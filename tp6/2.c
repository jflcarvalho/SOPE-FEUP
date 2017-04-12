// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define STDERR 2
int NUMITER = 50000;

typedef struct{
  int count;
  char *stringToWrite;
}Args;

void * thrfunc(void * arg)
{
while(NUMITER > 0){
  NUMITER--;
  write(STDERR,((Args *) arg)->stringToWrite,1);
  ((Args *) arg)->count++;
}
  return NULL;
}
int main()
{
  Args n1;
  n1.count = 0;
  n1.stringToWrite = "a";
  Args n2;
  n2.count = 0;
  n2.stringToWrite = "b";
  pthread_t ta, tb;
  pthread_create(&ta, NULL, thrfunc, &n1);
  pthread_create(&tb, NULL, thrfunc, &n2);
  pthread_join(ta, NULL);
  pthread_join(tb, NULL);
  printf("\n TA: %d; TB: %d; S: %d\n",n1.count,n2.count, n1.count + n2.count);
  return 0;
}
