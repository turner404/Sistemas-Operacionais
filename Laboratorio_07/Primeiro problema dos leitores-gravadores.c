// Descrição: Primeiro problema dos leitores-gravadores implementado com semáforos
// Autores: Luiz Guilherme Geron Manfrim Coelho e Rafael Augusto de Souza
// Data: 05-06-2025
#include <stdio.h> // printf
#include <pthread.h> // pthreads
#include <semaphore.h> // semaforos


int dado = 0;
int leitores = 0;

sem_t mutex_leitores;
sem_t acesso_escritor;

// Atualiza o dado
void *escritor(void *arg){
	while(1){
        sem_wait(&acesso_escritor); // Espera leitores terminarem

        // Escrita
        dado++;

        sem_post(&acesso_escritor); // Libera para outros escritores ou leitores
    }
}


// Exibe o dado
void *leitor(void *arg){
	while(1){
        // Entrada da região crítica dos leitores
        sem_wait(&mutex_leitores);
        leitores++;
        if(leitores == 1)
            sem_wait(&acesso_escritor); // Primeiro leitor bloqueia escritores
        sem_post(&mutex_leitores);

        // Leitura
        printf("%d\n", dado);

        // Saída da região crítica dos leitores
        sem_wait(&mutex_leitores);
        leitores--;
        if(leitores == 0)
            sem_post(&acesso_escritor); // Último leitor libera escritores
        sem_post(&mutex_leitores);
    }
}

int main(){
	printf("Primeiro problema dos leitores-gravadores\n");
	
	
	sem_init(&mutex_leitores, 0, 1);
    	sem_init(&acesso_escritor, 0, 1);
	
	int n_escritores = 4;
	int n_leitores = 2;
	
	pthread_t t_leitor[2], t_escritor[4];
	
	for(int x=0; x<n_escritores; x++){
		pthread_create(&(t_escritor[x]), NULL, escritor, NULL);
	}
	
	for(int x=0; x<n_leitores; x++){
		pthread_create(&(t_leitor[x]), NULL, leitor, NULL);
	}
	
	for(int x=0; x<n_escritores; x++){
		pthread_join(t_escritor[x], NULL);
	}
	
	for(int x=0; x<n_leitores; x++){
		pthread_join(t_leitor[x], NULL);
	}	
}

// gcc "Primeiro problema dos leitores-gravadores.c" -o "Primeiro problema dos leitores-gravadores.o"
