#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define WRITE 1
#define READ 0
#define MAXLINE 256

int main(void){
  pid_t pid;
  int buff[2];
  if (pipe(buff) < 0){
    fprintf(stderr, "Pipe Error\n");
    exit(1);
  }
  if ((pid = fork()) < 0 ){
    fprintf(stderr, "Fork error\n");
    exit(1);
  }
  if(pid > 0) {  //PARENT
    char line[MAXLINE];
    close(buff[READ]);
    fgets(line, MAXLINE, stdin);
    write(buff[WRITE], line, MAXLINE);
  }
  else{  //CHILD
    char lineToRead[MAXLINE];
    int intToRead[2];
    close(buff[WRITE]);
    read(buff[READ], lineToRead, MAXLINE);
    sscanf(lineToRead, "%d %d", &intToRead[0], &intToRead[1]);
    printf("Adição: %d\n", (intToRead[0]+intToRead[1]));
    printf("Subtracao: %d\n", (intToRead[0]-intToRead[1]));
    printf("Multiplicacao: %d\n", (intToRead[0]*intToRead[1]));
    if(intToRead[1] == 0){
      printf("Divisao: Error divisao por 0\n");
    }
    else{
      printf("Divisao: %f\n", ((double)intToRead[0]/intToRead[1]));
    }
  }
  return 0;
}
