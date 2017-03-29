#include <stdio.h>
#include <unistd.h>
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
  mkfifo("/tmp/fifo_req", 0660);

  int fifo_req, fifo_ans;
  do {
    fifo_req=open("/tmp/fifo_req",O_RDWR);
    if (fifo_req == -1) sleep(1);
  } while(fifo_req == -1);

  Pair pairToRead;
  Answer answer;

  int n;
  do {
    n = read(fifo_req,&pairToRead, sizeof(pairToRead));
    /* code */
    answer.adicao = pairToRead.left+pairToRead.right;
    answer.subtracao = pairToRead.left-pairToRead.right;
    answer.multiplicacao = pairToRead.left*pairToRead.right;
    if(pairToRead.right != 0){
      answer.divisao = (double) pairToRead.left/pairToRead.right;
    }
    else{
      answer.divisao = 0;
    }
    do {
      fifo_ans = open(pairToRead.fifo_name,O_WRONLY);
      if (fifo_ans == -1) sleep(1);
    } while(fifo_ans == -1);
    write(fifo_ans, &answer, sizeof(answer));
    if(pairToRead.left == 0 && pairToRead.right == 0){
      close(fifo_req);
      close(fifo_ans);
      return 0;
    }
  } while (n > 0);

  return 0;
}
