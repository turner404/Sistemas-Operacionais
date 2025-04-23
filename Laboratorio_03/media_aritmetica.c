// Descrição: Um programa com que recebe de entrada uma matriz M x N e cria M threads para calcular a média aritmética de cada linha da matriz.
// Autor: Augusto Maccagnan Mendes.
// Data: 20-04-2025.

#include <stdio.h>
#include <stdlib.h>     //atoi(), srand()
#include <time.h>       //time() 
#include <pthread.h>    //pthreads
#include <string.h>     //strcmp()
#include "matriz.h"

#define M 10
#define N 10

#define ARQUIVO_DE_SAIDA "media_aritmetica.out"

// Variáveis globais acessiveis a todas as threads
int r, c;
char caminhoDoArquivoMatriz[1000];

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

void escreverListaDeResultados(int* result){
    FILE *arquivo = fopen(ARQUIVO_DE_SAIDA, "w");  

    for (int i = 0; i < r; i++) {
        fprintf(arquivo, "%d\n", result[i]);
    }

    fclose(arquivo);
}


int main(int argc, char *argv[]) 
{ 
   r = M, c = N ;
    
   /* processa as dimensões da matriz se informadas por parâmetro */
   if (argc == 3) {        
      r = atoi(argv[1]);
      c = atoi(argv[2]);
   }
   caminhoDoArquivoMatriz[0] = '\0';

    for(int i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-am")){
            sscanf(argv[i + 1], "%d", &r);
        }else if(!strcmp(argv[i], "-cm")){
            sscanf(argv[i + 1], "%d", &c);
        }else if(!strcmp(argv[i], "-cam")){
            sscanf(argv[i + 1], "%s", &caminhoDoArquivoMatriz);
        }
    }
    int** matrix;
   /* lê a matriz a partir de um arquivo de entrada */   
   if(caminhoDoArquivoMatriz[0] != '\0'){
        printf("Gerando a matriz...\n");
        matrix = read_matrix_from_file(caminhoDoArquivoMatriz, &r, &c);
    } else{
        /* gera uma matrix rxc e popula com valores pseudoaleatorios */
        matrix = create_matrix(r, c);
        srand(time(NULL));   // inicializa o gerador com uma semente.
        generate_elements(matrix, r, c, 99);
    }
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
    printf("Gerando arquivo com resultados...\n");
    escreverListaDeResultados(results);

   return 0; 
}
