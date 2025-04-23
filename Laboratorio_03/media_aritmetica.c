// Descrição: Um programa com que recebe de entrada uma matriz M x N e cria M threads para calcular a média aritmética de cada linha da matriz.
// Autor: Augusto Maccagnan Mendes.
// Data: 20-04-2025.

#include <stdio.h>
#include <stdlib.h>     //atoi(), srand()
#include <time.h>       //time() 
#include <pthread.h>    //pthreads
#include "matriz.h"

#define M 10
#define N 10

// Variáveis globais acessiveis a todas as threads
int r, c;

void* avg_thread(void* arg){
    // linha da matriz sendo processada
    int* m_row = (int*) arg;
    int acc = 0;
    for(int i = 0; i < c; i++){
        acc += m_row[i];
    }
    acc = acc/c;
    int* result = malloc(sizeof(int));
    *result = acc;
    pthread_exit((void*) result);
}

void print_vector(int* v, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) 
{ 
   r = M, c = N ;
    
   /* processa as dimensões da matriz se informadas por parâmetro */
   if (argc == 3) {        
      r = atoi(argv[1]);
      c = atoi(argv[2]);
   }

   /* lê a matriz a partir de um arquivo de entrada */   
//    int **matrix = read_matrix_from_file("data_matriz_100_200.in", &r, &c);

   /* gera uma matrix rxc e popula com valores pseudoaleatorios */
   int **matrix = create_matrix(r, c);
   srand(time(NULL));   // inicializa o gerador com uma semente.
   generate_elements(matrix, r, c, 99);

//    printf("%dx%d\n", r, c);
//    print_matrix(matrix, r, c);

    // DIVISÃO DO PROBLEMA
    // Criar uma thread para processar cada linha da matriz
    /* ==========CRIAR 1 THREAD POR LINHA============================== */
    printf("Criando %d threads para processar %d linhas\n", r, r);
    pthread_t* threads;
    threads = malloc(sizeof(pthread_t) * r);
    int* results;
    results = malloc(sizeof(int) * r);
    for(int i = 0; i < r; i++){
        if(pthread_create(&threads[i], NULL, avg_thread, (void*) matrix[i]) != 0){
            printf("Erro ao criar thread %d\n", i);
            exit(1);
        }
    }
    // Espera a thread terminar e captura o resultado
    int* temp;
    for(int i = 0; i < r; i++){
        if(pthread_join(threads[i], (void**) &temp) != 0){
            printf("Erro ao esperar thread %d\n", i);
            exit(1);
        }
        results[i] = *temp;
        free(temp);
    }

    // Montar vetor com resultado de todas as threads
    printf("Resultado da media por linha:\n");
    print_vector(results, r);

   return 0; 
}
