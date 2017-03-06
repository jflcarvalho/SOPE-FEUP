#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
  int status;
  int fathers_pid = getpid();
  if(fork() > 0) { // pai
    write(STDOUT_FILENO,"Hello ",6);
  } else { // filho
    waitpid(fathers_pid, &status, WNOHANG);
    write(STDOUT_FILENO,"World!\n",7);
  }
  return 0;
}
