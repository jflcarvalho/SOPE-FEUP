#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct{
  char fifo_name[100];
  int left;
  int right;
} Pair;

typedef struct{
  int adicao;
  int subtracao;
  int multiplicacao;
  double divisao;
} Answer;

int main(int argc, char const *argv[]) {
  /* code */
  char fifo_dir[100] = "/tmp/fifo_";
  int pid = getpid();
  char pidString[100];
  sprintf(pidString, "%d", pid);
  strcat(fifo_dir, pidString);
  mkfifo(fifo_dir, 0660);

  int fifo_req, fifo_ans;
  do {
    fifo_req=open("/tmp/fifo_req",O_WRONLY);
    if (fifo_req == -1) sleep(1);
  } while(fifo_req == -1);

  Pair pairToWrite;
  Answer answerToRead;

  printf("N1: ? && N2: ?\n");
  scanf("%d %d", &pairToWrite.left, &pairToWrite.right);
  strcpy(pairToWrite.fifo_name,fifo_dir);
  /*pairToWrite.left = argv[1];
  pairToWrite.right = argv[2];*/
  write(fifo_req, &pairToWrite, sizeof(pairToWrite));

  do {
    fifo_ans = open(fifo_dir,O_RDONLY);
    if (fifo_ans == -1) sleep(1);
  } while(fifo_ans == -1);

  read(fifo_ans, &answerToRead, sizeof(answerToRead));
  printf("Adicao: %d\n", answerToRead.adicao);
  printf("Subtracao: %d\n", answerToRead.subtracao);
  printf("Multiplicacao: %d\n", answerToRead.multiplicacao);
  printf("Divisao: %f\n", answerToRead.divisao);

  return 0;
}
