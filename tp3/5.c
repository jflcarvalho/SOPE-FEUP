#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
  int status;
  pid_t fathers_pid = getpid();
  if(fork() > 0) { // pai
    write(STDOUT_FILENO,"Hello ",6);
  } else { // filho
    waitpid(fathers_pid, &status, WNOHANG);
    if(fork() > 0) { // pai
      pid_t fathers_pid = getpid();
      write(STDOUT_FILENO,"my ",3);
    } else { // filho
      waitpid(fathers_pid, &status, WNOHANG);
      write(STDOUT_FILENO,"Friends!\n",9);
    }
  }
  return 0;
}
