// Descrição: Programa que calcula a quantidade de ocorrências de um elemento em uma lista por meio de vários processos.
// Autor: Luiz Guilherme Geron Manfrim Coelho
// Data: 2025-04-14

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int qtd_args, char** argumentos){
	printf("Exercício 3:\n");

	// Parâmetros de entrada (com valores padrão)
	int qtd_filhos = 3;       // -noc
	int tamanho_lista = 20;   // -ls
	int numero_maximo = 10;   // -mn
	int numero_buscado = 10;  // -sn

	// Lê os parâmetros de entrada fornecidos pela linha de comando
	for(int i = 0; i < qtd_args; i++){
		if(!strcmp(argumentos[i], "-noc")){
			sscanf(argumentos[i + 1], "%d", &qtd_filhos);
		}else if(!strcmp(argumentos[i], "-ls")){
			sscanf(argumentos[i + 1], "%d", &tamanho_lista);
		}else if(!strcmp(argumentos[i], "-mn")){
			sscanf(argumentos[i + 1], "%d", &numero_maximo);
		}else if(!strcmp(argumentos[i], "-sn")){
			sscanf(argumentos[i + 1], "%d", &numero_buscado);
		}
	}

	printf("Quantidade de filhos (-noc) = %d\n", qtd_filhos);
	printf("Tamanho da lista (-ls) = %d\n", tamanho_lista);
	printf("Número máximo (-mn) = %d\n", numero_maximo);
	printf("Número buscado (-sn) = %d\n", numero_buscado);

	// Cria a lista com números aleatórios e a imprime
	printf("Lista = { ");
	int *lista = malloc(sizeof(int) * tamanho_lista);
	for(int i = 0; i < tamanho_lista; i++){
		lista[i] = rand() % numero_maximo + 1;
		printf("%d ", lista[i]);
	}
	printf("}\n");

	// Cria processos filhos e divide a lista para que cada um analise um bloco
	int tamanho_bloco = tamanho_lista / qtd_filhos;
	int inicio_bloco = 0;
	int fim_bloco = inicio_bloco + tamanho_bloco;

	pid_t *filhos = malloc(sizeof(pid_t) * qtd_filhos);
	pid_t pid;

	for(int i = 0; i < qtd_filhos; i++){
		filhos[i] = pid = fork();
		if(pid == 0){ // Processo filho
			// O último bloco se estende até o final da lista
			if(i + 1 == qtd_filhos){
				fim_bloco = tamanho_lista;
			}
			break;
		}else{ // Processo pai
			// Define o próximo bloco da lista
			inicio_bloco += tamanho_bloco;
			fim_bloco = inicio_bloco + tamanho_bloco;
		}
	}

	if(pid == 0){ // Processo filho
		// Conta quantas vezes o número buscado aparece no bloco atribuído
		pid = getpid();
		int total_encontrado = 0;
		for(int i = inicio_bloco; i < fim_bloco; i++){
			if(lista[i] == numero_buscado){
				printf("Processo %d encontrou %d na posição %d.\n", pid, numero_buscado, i);
				total_encontrado++;
			}
		}
		free(lista);
		free(filhos);
		// Encerra com o total encontrado para que o pai colete com WEXITSTATUS
		exit(total_encontrado);
	}else if(pid > 0){ // Processo pai
		// Aguarda todos os filhos terminarem e soma os resultados
		int status;
		int total_encontrado = 0;
		for(int i = 0; i < qtd_filhos; i++){
			wait(&status);
			total_encontrado += WEXITSTATUS(status);
		}
		free(lista);
		free(filhos);
		if(total_encontrado == 0){
			printf("%d não foi encontrado.\n", numero_buscado);
		}else{
			printf("%d encontrado em %d posições.\n", numero_buscado, total_encontrado);
		}
		printf("Concluído.\n");
		exit(0);
	}else{ // Erro ao criar processo filho
		printf("Erro ao criar processo filho.\n");
		free(lista);
		free(filhos);
		exit(1);
	}
}
