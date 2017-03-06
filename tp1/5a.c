#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	char** env = envp;
	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return 0;
}
