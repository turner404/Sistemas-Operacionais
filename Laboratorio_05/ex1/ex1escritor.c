// Descrição: Programa que escreve mensagens para serem lidas por outro processo via FIFO.
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

int main(){
	printf("Ex1 escritor\n");
	
	int fd;
	char nome_fifo[] = "/tmp/um_fifo";
	char buffer[512];
	
	// Tenta criar o FIFO
	if(mkfifo(nome_fifo,0664) < 0 && errno != EEXIST){
		perror("Erro ao criar o FIFO.");
		exit(1);
	}
	
	// Tenta abrir o FIFO
	if((fd = open(nome_fifo, O_WRONLY)) < 0){
		perror("Erro ao abrir o FIFO.");
		exit(2);
	}
	
	// Tenta escrever as mensagens para o FIFO
	while(1){
		scanf(" %[^\n]", buffer);
		int total_escrito = write(fd, buffer, sizeof(buffer));
		if(total_escrito < 0){
			perror("Erro ao escrever mensagem para o FIFO.");
		}else if(total_escrito > 0){
			printf("Mensagem enviada: %s\n", buffer);
		}
	}
	
	// Tenta fechar o FIFO
	if(close(fd) < 0){
		perror("Erro ao fechar o FIFO.");
		exit(3);
	}
}