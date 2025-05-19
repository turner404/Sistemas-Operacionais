// Descrição: Programa que lê mensagens escritas por outro processo via FIFO.
// Autor: Luiz Guilherme Geron Manfrim Coelho.
// Data: 18-05-2025.
// Observação: O código tem como base o código fornecido pelo professor nos materiais: "Exemplos IPC: pipe, fifo, socket, mqueue, shm"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>

void detalhes(char mensagem[]){
	int total_consoantes = 0;
	int total_voigais = 0;
	int total_espacos = 0;
	int indice = 0;
	char c = mensagem[indice];
	while(c != '\0'){
		c = tolower(c);
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
			total_voigais ++;
		}else if (c == ' '){
			total_espacos ++;
		}else{
			total_consoantes ++;
		}
		indice ++;
		c = mensagem[indice];
	}
	printf("Total de consoantes: %d\n", total_consoantes);
	printf("Total de vogais: %d\n", total_voigais);
	printf("Total de espacos: %d\n", total_espacos);
}

int main(){
	printf("Ex1 leitor\n");

	int fd;
	char nome_fifo[] = "/tmp/um_fifo";
	char buffer[512];
	
	// Tenta criar o FIFO
	if(mkfifo(nome_fifo,0664) < 0 && errno != EEXIST){
		perror("Erro ao criar o FIFO.");
		exit(1);
	}
	
	// Tenta abrir o FIFO
	if((fd = open(nome_fifo, O_RDONLY)) < 0){
		perror("Erro ao abrir o FIFO.");
		exit(2);
	}
	
	// Tenta ler as mensagens do FIFO
	while(1){
		memset (buffer, '\0', sizeof(buffer));
		int total_lido = read(fd, buffer, sizeof(buffer));
		if(total_lido < 0){
			perror("Erro ao ler mensagem do FIFO.");
		}else if(total_lido > 0){
			printf("Mensagem recebida: %s\n", buffer);
			detalhes(buffer);
		}
	}
	
	// Tenta fechar o FIFO
	if(close(fd) < 0){
		perror("Erro ao fechar o FIFO.");
		exit(3);
	}	
}