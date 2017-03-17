// PROGRAMA p03a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int step = 1;

void sigusr_handler(int signo)
{
  //printf("In SIGUSR handler ...\n");
  if(signo == SIGUSR1){
    step = 1;
  }
  else if (signo == SIGUSR2){
    step = -1;
  }
}

int main(void)
{
  struct sigaction action;
  action.sa_handler = sigusr_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  if (sigaction(SIGUSR1,&action, NULL) < 0)
  {
    fprintf(stderr,"Unable to install SIGUSR1 handler\n");
    exit(1);
  }

  if (sigaction(SIGUSR2,&action, NULL) < 0)
  {
    fprintf(stderr,"Unable to install SIGUSR2 handler\n");
    exit(1);
  }

  int pid = fork();
  if(pid == 0){ /* CHILD */
    int v = 0, count = 0;
    while(1){
      v += step;
      printf("%d\n", v);
      count++;
      if(count == 50){
        exit(0);
      }

      sleep(1);
    }
  }
  else { /* PARENT */
    int status;
    while (1) {
      if(waitpid(pid,&status, WNOHANG) == pid){
        exit(0);
      };
      kill(pid, rand()%2? SIGUSR1 : SIGUSR2);
      sleep(1);
    }
  }
  exit(0);
}
