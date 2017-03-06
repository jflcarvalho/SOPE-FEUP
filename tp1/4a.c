#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i = 0;
	int pilas = atoi(argv[2]);
	for(i = 0; i < pilas; i++){
		printf("Hello %s !\n", argv[1]);
	}
	return 1;
}
