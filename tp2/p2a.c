#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> 
#include <string.h>

#define BUFFER_SIZE 512

int main(int argc,char *argv[]){
	//test valid args
	if (argc != 3) {
  		printf("Invalid number of args <source> <destination>\n");
  		return 1;  // value 1 especify error on args
 	}
	
	FILE *src, *dst;
	char buff[BUFFER_SIZE + 1];	

	src = fopen(argv[1], "r");
	if( src == NULL)
	{
		perror(argv[1]);
		fclose(src);
		return 2; // value 2 especify error on opening files
	}
	
	dst = fopen(argv[2], "a");
	if( dst == NULL)
	{
		perror(argv[2]);
		fclose(dst);
		return 2;
	}

	size_t nr, nw;

	while((nr = fread(buff, 1, BUFFER_SIZE, src)) > 0){
		if((nw = fwrite(buff, 1, BUFFER_SIZE, dst)) <= 0 || nr != nw){
			perror(argv[2]);
			fclose(src);
			fclose(dst);
			return 3; // value 3 especify error on copy data
		}
	}
	fclose(src);
	fclose(dst);
	
	return 0;
}








