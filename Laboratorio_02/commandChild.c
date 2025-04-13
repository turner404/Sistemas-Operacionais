// Descrição: Programa que executa um comando passado como argumento.
// Autor: Luiz Guilherme Geron
// Data: 2025-04-11


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argn, char** argv){
	printf("Ex 2:\n");
	
	if(argn < 2){
		printf("I need a command!\n");
		exit(1);
	}
	
	char **argv2 = malloc(sizeof(char) * (argn - 1));
	for(int argi = 2; argi < argn; argi ++){
		argv2[argi - 2] = argv[argi];
	}
	argv2[argn - 2] = (char *) 0;
	
	if(fork() == 0){
		execv(argv[1], argv2);
	}

	free(argv2);
	
	wait(NULL);
	
	printf("Done.\n");
}
