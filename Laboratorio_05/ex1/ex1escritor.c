// Descrição: Programa que lê entradas de texto do usuário e as envia para outro processo via fifo
// Autor: Luiz Guilherme Geron Manfrim Coelho
// Data: 18-05-2025
// Observação: O código tem como base o código fornecido pelo professor nos materiais: "Exemplos IPC: pipe, fifo, socket, mqueue, shm"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

// Abre um fifo, lê entradas de texto do usuário e as envia para o fifo
int main(){
	printf("Ex1 escritor\n");
	
	int fd;
	char nome_fifo[] = "/tmp/um_fifo";
	char buffer[512];
	
	// Tenta criar o fifo
	if(mkfifo(nome_fifo,0664) < 0 && errno != EEXIST){
		perror("Erro ao criar o fifo.");
		exit(1);
	}
	
	// Tenta abrir o fifo
	if((fd = open(nome_fifo, O_WRONLY)) < 0){
		perror("Erro ao abrir o fifo.");
		exit(2);
	}
	
	
	while(1){
		// Lê uma mensagem de texto do usuário
		scanf(" %[^\n]", buffer);
		// Tenta escrever as mensagens para o fifo
		int total_escrito = write(fd, buffer, sizeof(buffer));
		if(total_escrito < 0){
			perror("Erro ao escrever mensagem para o fifo.");
		}else if(total_escrito > 0){
			printf("Mensagem enviada: %s\n", buffer);
		}
	}
	
	// Tenta fechar o fifo
	if(close(fd) < 0){
		perror("Erro ao fechar o fifo.");
		exit(3);
	}
}