// Descrição: Programa que executa um comando, passado como argumento, em um processo filho e aguarda sua finalização.
// Autor: Luiz Guilherme Geron Manfrim Coelho
// Data: 2025-04-14

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argn, char** argv){
	printf("Ex 2:\n");
	
	// Verifica se algo foi passado como argumento
	if(argn < 2){
		printf("Eu preciso de um comando, mestre.\n");
		exit(1);
	}
	
	// Gera uma lista contendo os argumentos para a execução do comando
	char **argv2 = malloc(sizeof(char*) * (argn - 1));
	for(int argi = 2; argi < argn; argi ++){
		argv2[argi - 2] = argv[argi];
	}
	argv2[argn - 2] = (char *) 0;
	
	// Gera um processo filho e executa nele o comando dado
	if(fork() == 0){ // Processo filho
		execv(argv[1], argv2);
		printf("Erro ao executar comando");
		exit(1);
	}

	free(argv2);
	
	// Espera pelo fim do processo filho
	wait(NULL);
	
	printf("Pronto, mestre.\n");
}
