// PROGRAMA p7.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
   char prog[20];
   char progOut[20];
   sprintf(prog,"%s.c",argv[1]);
   sprintf(progOut,"%s.out",argv[1]);
   execlp("gcc","gcc",prog,"-Wall","-o",progOut,NULL);
   printf("Fail on execlp\n");
   exit(1);
}
