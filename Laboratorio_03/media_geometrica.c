// Descrição: Programa que calcula a média geométrica das colunas de um matriz.
// Autor: Luiz Guilherme Geron Manfrim Coelho
// Data: 2025-04-21
#include <stdio.h> 
#include <string.h>
#include "matriz.h"
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

#define ARQUIVO_DE_SAIDA "resultados da matriz.out"

int alturaDaMatriz;
int comprimentoDaMatriz;
int **matriz;
double *resultadosDaMediaGeometrica;

void* calculoDaMediaGeometricaPorColuna(void* entrada){
	int coluna = *((int*) entrada); // coluna da matriz
	free(entrada); // liberar a memória


	double produto = 1; // multiplicação dos elementos da coluna
	double resultado; // resultado da média geométrica (a raiz enésima do produto)

	for(int i = 0; i < alturaDaMatriz; i++){
		produto *= matriz[i][coluna];
	}

	resultado = pow(produto, 1.0 / alturaDaMatriz);

	resultadosDaMediaGeometrica[coluna] = resultado;

	return NULL;
}

void exibirListaDeResultados(){
	printf("[");
	for(int i = 0; i < comprimentoDaMatriz; i++){
		printf(" %.4f,", resultadosDaMediaGeometrica[i]);
	}
	printf("\b ]\n");
}

void escreverListaDeResultados(){
	FILE *arquivo = fopen(ARQUIVO_DE_SAIDA, "w");  

	for (int i = 0; i < comprimentoDaMatriz; i++) {
		fprintf(arquivo, "%.4f\n", resultadosDaMediaGeometrica[i]);
	}

	fclose(arquivo);
}

int main(int numeroDeArgumentos, char *argumentos[]){
	printf("\nEx 2 b)\n\n");

	printf("\nENTRADAS:\n\n");

	alturaDaMatriz = 2;
	comprimentoDaMatriz = 4;
	char caminhoDoArquivoMatriz[1000];
	caminhoDoArquivoMatriz[0] = '\0';

	for(int i = 0; i < numeroDeArgumentos; i++){
		if(!strcmp(argumentos[i], "-am")){
			sscanf(argumentos[i + 1], "%d", &alturaDaMatriz);
		}else if(!strcmp(argumentos[i], "-cm")){
			sscanf(argumentos[i + 1], "%d", &comprimentoDaMatriz);
		}else if(!strcmp(argumentos[i], "-cam")){
			sscanf(argumentos[i + 1], "%s", &caminhoDoArquivoMatriz);
		}
	}

	printf("Altura da matriz (-am) = %d\n", alturaDaMatriz);
	printf("Comprimento da matriz (-cm) = %d\n", comprimentoDaMatriz);
	printf("Caminho do arquivo matriz (-cam) = %s\n", caminhoDoArquivoMatriz);
	printf("Caso o caminho do arquivo matriz seja fornecido, a matriz será lida do arquivo. Caso contrário, a matriz será gerada com base nas dimensões fornecidas ou padrões.\n");

	printf("\nPROCESSAMENTO:\n\n");

	pthread_t *pthreadsDaMediaGeometrica = malloc(sizeof(pthread_t) * comprimentoDaMatriz);
	resultadosDaMediaGeometrica = malloc(sizeof(double) * comprimentoDaMatriz);
	
	if(caminhoDoArquivoMatriz[0] == '\0'){

		printf("Gerando a matriz...\n");
		matriz = create_matrix(alturaDaMatriz, comprimentoDaMatriz);
		generate_elements(matriz, alturaDaMatriz, comprimentoDaMatriz, 100);
	}else{

		printf("Carregando a matriz...\n");
		matriz = read_matrix_from_file(caminhoDoArquivoMatriz, &alturaDaMatriz, &comprimentoDaMatriz);
		printf("Altura da matriz = %d\n", alturaDaMatriz);
		printf("Comprimento da matriz = %d\n", comprimentoDaMatriz);
	}

	if(comprimentoDaMatriz <= 20 && alturaDaMatriz <= 20) print_matrix(matriz, alturaDaMatriz, comprimentoDaMatriz);
	
	printf("Criando as pthreads (%d)...\n", comprimentoDaMatriz);
	for(int i = 0; i < comprimentoDaMatriz; i++){
		int *entradaDaPthread = malloc(sizeof(int));
		*entradaDaPthread = i;
		pthread_create(&pthreadsDaMediaGeometrica[i], NULL, calculoDaMediaGeometricaPorColuna, entradaDaPthread);
	}

	printf("Esperando as pthreads (%010d/%010d)...", comprimentoDaMatriz, comprimentoDaMatriz);
	for(int i = 0; i < comprimentoDaMatriz; i++){
		pthread_join(pthreadsDaMediaGeometrica[i], NULL);
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b%010d/%010d)...", comprimentoDaMatriz - i - 1, comprimentoDaMatriz);
	}
	printf("\n");

	if(comprimentoDaMatriz <= 20) exibirListaDeResultados();

	printf("Escrevendo os resultados (\"%s\")...\n", ARQUIVO_DE_SAIDA);
	escreverListaDeResultados();

	free(pthreadsDaMediaGeometrica);
	free(resultadosDaMediaGeometrica);
	// free_matrix(matriz, alturaDaMatriz);


}
