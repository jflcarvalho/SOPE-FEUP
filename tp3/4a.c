#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
  int status;
  if(fork() > 0) { // pai
    wait(&status);
    write(STDOUT_FILENO,"World!\n",7);
  } else { // filho
    write(STDOUT_FILENO,"Hello ",6);
  }
  return 0;
}
