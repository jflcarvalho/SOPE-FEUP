#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define WRITE 1
#define READ 0

int main(void){
  int buff[2];
  int intR[2];
  pid_t pid;
  if (pipe(buff) < 0){
    fprintf(stderr, "Pipe Error\n");
    exit(1);
  }
  if ((pid = fork()) < 0 ){
    fprintf(stderr, "Fork error\n");
    exit(1);
  }
  if(pid > 0) {  //PARENT
    close(buff[READ]);
    scanf("%d %d", &intR[0], &intR[1]);
    write(buff[WRITE], intR, 2*sizeof(int));
  }
  else{  //CHILD
    int intToRead[2];
    close(buff[WRITE]);
    read(buff[READ], &intToRead[0], sizeof(int));
    read(buff[READ], &intToRead[1], sizeof(int));
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
