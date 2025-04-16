// Descrição: Programa que divide um array em N partes e cria N threads para procurar um valor em cada parte
// Autor: Victórya Carolina Guimarães da Luz
// Data: 16-04-2025

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct ThreadData {
    int* array;
    int start;
    int end;
    int searchValue;
} ThreadData;

// Funções
int* generateArray(int size);
void printArray(int size, int* array);
void* searchValueFn(void* data);
ThreadData* createStruct();

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s <tamanho do vetor> <quantidade_threads>\n", argv[0]);
        return 1;
    }

    int searchValue;
    int threadCount = atoi(argv[2]);
    int arraySize = atoi(argv[1]);

    srand(time(NULL)); // Inicializa semente para números aleatórios
    int* array = generateArray(arraySize);
    printArray(arraySize, array);

    printf("Digite o valor a ser procurado: ");
    scanf("%d", &searchValue);

    int sizePartPerThread;
    if (arraySize > threadCount) {
        sizePartPerThread = arraySize / threadCount;
    } else {
        sizePartPerThread = 1;
        threadCount = arraySize;
    }

    // Vetor para guardar os IDs das threads
    pthread_t* threads = (pthread_t*) malloc(threadCount * sizeof(pthread_t));

    for (int i = 0; i < threadCount; i++) {
        ThreadData* data = createStruct();

        int start = i * sizePartPerThread;
        int end = (i == threadCount - 1) ? arraySize - 1 : (start + sizePartPerThread - 1);

        data->array = array;
        data->start = start;
        data->end = end;
        data->searchValue = searchValue;

        pthread_create(&threads[i], NULL, searchValueFn, (void*) data);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }

    free(array);
    free(threads);
    return 0;
}

// Função que aloca memória para a struct ThreadData.
ThreadData* createStruct() {
    return (ThreadData*) malloc(sizeof(ThreadData));
}

// Função que gera um vetor de inteiros com valores aleatórios.
int* generateArray(int size) {
    int* array = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10;
    }
    return array;
}

// Função que imprime o vetor.
void printArray(int size, int* array) {
    printf("Array: [");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// Função que procura um valor no vetor.
void* searchValueFn(void* data) {
    ThreadData* threadData = (ThreadData*) data;
    int foundValue = 0;

    for (int i = threadData->start; i <= threadData->end; i++) {
        if (threadData->array[i] == threadData->searchValue) {
            printf("Valor encontrado na posição %d - thread [%d...%d]\n", i, threadData->start, threadData->end);
            foundValue = 1;
        }
    }

    if (!foundValue) {
        printf("Valor não encontrado - thread [%d...%d]\n", threadData->start, threadData->end);
    }

    free(threadData);
    pthread_exit(NULL);
}
