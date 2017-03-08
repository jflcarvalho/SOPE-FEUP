// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int checkStatus(int *status){
  if(WIFEXITED(status)){
    return WEXITSTATUS(status);
  }
  else if(WIFSIGNALED(status))
  {
    if(WCOREDUMP(status)){
      printf("the child  produced  a  core  dump.\n");
    }
    return WTERMSIG(status);
  }
  else if(WIFSTOPPED(status)){
    return WSTOPSIG(status);
  }
  else
    return -1;
}

int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;
  if (argc != 2)
  {
    printf("usage: %s dirname\n",argv[0]);
    exit(1);
  }
  pid=fork();
  if (pid > 0)
  {
    printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
    int status;
    waitpid(pid, &status, WUNTRACED);
    printf("Exit Code: %d\n", checkStatus(&status));
  }
  else if (pid == 0){
    /* a) */
    //execlp("ls", "ls", "-laR", argv[1], NULL);
    /* b) */
    //execl("/bin/ls", "ls", "-laR", argv[1], NULL);
    /* c) */
    char* const paramts[] = {"ls", "-laR", argv[1], NULL};
    //execvp("/bin/ls", paramts);
    /* d) */
    //char* path = "/bin/ls";
    //execv(path, paramts);
    /* e) */
    execve("ls", paramts, envp);
    printf("Command not executed !\n");
    exit(1);
  }
  exit(0);
}
