// Descrição: Programa que divide um array em n partes e cria n processos filhos para procurar um valor em cada parte
// Autor: Luiz Guilherme Geron
// Data: 2025-04-11


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argn, char** argv){
	printf("Ex 3:\n");
	
	int number_of_children = 3; // -noc
	int list_size = 20; // -ls
	int max_number = 10; // -mn
	int searched_number = 10; // -sn
	
	for(int argi = 0; argi < argn; argi ++){
		if(!strcmp(argv[argi],"-noc")){
			sscanf(argv[argi + 1], "%d", &number_of_children);
		}else if(!strcmp(argv[argi],"-ls")){
			sscanf(argv[argi + 1], "%d", &list_size);
		}else if(!strcmp(argv[argi],"-mn")){
			sscanf(argv[argi + 1], "%d", &max_number);
		}else if(!strcmp(argv[argi],"-sn")){
			sscanf(argv[argi + 1], "%d", &searched_number);
		}
	}
	
	if(number_of_children > list_size){
		number_of_children = list_size;
	}
	
	printf("Number of children (-noc) = %d\n", number_of_children);
	printf("List size (-ls) = %d\n", list_size);
	printf("Max number (-mn) = %d\n", max_number);
	printf("Searched number (-sn) = %d\n", searched_number);
	
	printf("List = { ");
	int *list = malloc(sizeof(int) * list_size);
	for(int i = 0; i < list_size; i ++){
		list[i] = rand() % max_number + 1;
		printf("%d ", list[i]);
	}
	printf("}\n");
	
	int block_size = list_size / number_of_children;
	
	int block_position = 0;
	int end_of_block = block_position + block_size;
	
	pid_t *children = malloc(sizeof(pid_t) * number_of_children);
	
	pid_t pid;
	for(int i = 0; i < number_of_children; i ++){
		children[i] = pid = fork();
		if(pid == 0){
			if(i + 1 == number_of_children){
				end_of_block = list_size;
			}
			break;
		}
		block_position += block_size;
		end_of_block = block_position + block_size;
	}
	
	if(pid == 0){ // Child process
		pid = getpid();
		int total_found = 0;
		for(int i = block_position; i < end_of_block; i ++){
			if(list[i] == searched_number){
				printf("Process %d found %d in position %d.\n", pid, searched_number, i);
				total_found ++;
			}
		}
		exit(total_found);
	}else if(pid > 0){ // Parent process
		int status;
		int total_found = 0;
		for(int i = 0; i < number_of_children; i ++){
			wait(&status);
			total_found += WEXITSTATUS(status);
		}
		free(list);
		free(children);
		if(total_found == 0){
			printf("%d not found.\n", searched_number);
		}
		printf("Done.\n");
	}else{ // Error creating child process
		printf("Error creating child process.\n");
		exit(1);
	}
}
