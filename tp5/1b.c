#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define WRITE 1
#define READ 0

typedef struct{
  int left, right;
} Pair;

int main(void){
  int buff[2];
  Pair intR;
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
    scanf("%d %d", &intR.left, &intR.right);
    write(buff[WRITE], &intR, sizeof(Pair));
  }
  else{  //CHILD
    Pair pairToRead;
    close(buff[WRITE]);
    read(buff[READ], &pairToRead, sizeof(Pair));
    printf("Adição: %d\n", (pairToRead.left+pairToRead.right));
    printf("Subtracao: %d\n", (pairToRead.left-pairToRead.right));
    printf("Multiplicacao: %d\n", (pairToRead.left*pairToRead.right));
    if(pairToRead.right == 0){
      printf("Divisao: Error divisao por 0\n");
    }
    else{
      printf("Divisao: %f\n", ((double)pairToRead.left/pairToRead.right));
    }
  }
  return 0;
}
