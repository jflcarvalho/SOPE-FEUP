#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define WRITE 1
#define READ 0

int main(void){
  int buff1[2];
  int buff2[2];
  pid_t pid;
  if (pipe(buff1) < 0){
    fprintf(stderr, "Pipe Error (buff1)\n");
    exit(1);
  }
  if (pipe(buff2) < 0){
    fprintf(stderr, "Pipe Error (buff2)\n");
    exit(1);
  }
  if ((pid = fork()) < 0 ){
    fprintf(stderr, "Fork error\n");
    exit(1);
  }
  if(pid > 0) {  //PARENT
    int intR[2];
    close(buff1[READ]);
    close(buff2[WRITE]);
    scanf("%d %d", &intR[0], &intR[1]);
    write(buff1[WRITE], intR, 2*sizeof(int));
    char type[1];
    int number;
    read(buff2[READ], &number, sizeof(int));
    printf("Adicao: %d\n", number);
    read(buff2[READ], &number, sizeof(int));
    printf("Subtracao: %d\n", number);
    read(buff2[READ], &number, sizeof(int));
    printf("Multiplicacao: %d\n", number);
    read(buff2[READ], &type, 1);
    if(type[0] == 'f'){
      double number;
      read(buff2[READ], &number, sizeof(double));
      printf("Divisao: %f\n", number);
    }
    else if(type[0] == '#'){
      printf("Divisao: Error divisao por 0\n");
    }
  }
  else{  //CHILD
    int intToRead[2];
    char line[sizeof(int)];
    close(buff1[WRITE]);
    close(buff2[READ]);
    read(buff1[READ], &intToRead[0], sizeof(int));
    read(buff1[READ], &intToRead[1], sizeof(int));
    int adicao = intToRead[0]+intToRead[1];
    write(buff2[WRITE], &adicao, sizeof(int));
    int subtracao = intToRead[0]-intToRead[1];
    write(buff2[WRITE], &subtracao, sizeof(int));
    int multiplicacao = intToRead[0]*intToRead[1];
    write(buff2[WRITE], &multiplicacao, sizeof(int));
    if(intToRead[1] != 0){
      write(buff2[WRITE], "f", 1);
      double divisao = (double)intToRead[0]/intToRead[1];
      write(buff2[WRITE], &divisao, sizeof(double));
    }
    else{
      write(buff2[WRITE], "#", 1);
    }
  }
  return 0;
}
