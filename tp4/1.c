// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
/*
struct sigaction {
  void     (*sa_handler)(int);
  void     (*sa_sigaction)(int, siginfo_t *, void *);
  sigset_t   sa_mask;
  int        sa_flags;
  void     (*sa_restorer)(void);
};
*/
void sigint_handler(int signo)
{
  printf("In SIGINT handler ...\n");
}
int main(void)
{
  struct sigaction action;
  action.sa_handler = sigint_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  if (sigaction(SIGINT,&action, NULL) < 0)
  {
    fprintf(stderr,"Unable to install SIGINT handler\n");
    exit(1);
  }
  printf("Sleeping for 30 seconds ...\n");
  int s = sleep(30);
  while(s != 0){
    s = sleep(s);
  }
  printf("Waking up ...\n");
  exit(0);
}
