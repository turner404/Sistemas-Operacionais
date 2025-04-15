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
		printf("Execute informando um comando.\n");
		exit(1);
	}
	
	// Gera uma lista contendo os argumentos para a execução do comando
	char **argv2 = malloc(sizeof(char*) * (argn));
	for(int i = 0; i < argn-1; i++){
		argv2[i] = argv[i+1];
	}

	argv2[argn-1] = NULL; // O último argumento deve ser NULL para o execvp funcionar

	// Gera um processo filho e executa nele o comando dado
	if(!fork()){ // Processo filho
		execvp(argv2[0], argv2);
		printf("Erro ao executar comando\n");
		exit(1);
	}

	free(argv2);
	
	// Espera pelo fim do processo filho
	wait(NULL);
	
	printf("Finalizado.\n");
}
