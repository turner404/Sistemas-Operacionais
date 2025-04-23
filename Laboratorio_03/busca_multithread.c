// Descrição: Um programa com N threads que localiza um valor em um vetor de inteiros, sendo que o espaço de busca no vetor é distribuído entre as N threads.
// Autor: Rafael Augusto de Souza.
// Data: 21-04-2025.

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

volatile int found = 0;
int found_index = -1;
pthread_mutex_t mtx;

// Gerando o array de inteiros
int* generateArray(int size) {
    int* array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10;
    }
    return array;
}

void printArray(int size, int* array) {
    printf("Array: [");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void* searchValueFn(void* data) {
    ThreadData* d = (ThreadData*) data;
    for (int i = d->start; i < d->end; i++) {
        pthread_mutex_lock(&mtx);
        if (found) {
            pthread_mutex_unlock(&mtx);
            break;
        }
        pthread_mutex_unlock(&mtx);

        if (d->array[i] == d->searchValue) {
            pthread_mutex_lock(&mtx);
            if (!found) {
                found = 1;
                found_index = i;
                printf("Valor %d encontrado na posição %d pela thread [%d...%d)\n", d->searchValue, i, d->start, d->end);
            }
            pthread_mutex_unlock(&mtx);
            break;
        }
    }

    if (!found) {
        printf("Valor não encontrado na thread [%d...%d)\n", d->start, d->end);
    }

    free(d);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s <tamanho do vetor> <quantidade_threads>\n", argv[0]);
        return 1;
    }

    int arraySize = atoi(argv[1]);
    int threadCount = atoi(argv[2]);
    int searchValue;

    srand(time(NULL));
    int* array = generateArray(arraySize);
    printArray(arraySize, array);

    printf("Digite o valor a ser procurado: ");
    scanf("%d", &searchValue);

    if (arraySize < threadCount) {
        threadCount = arraySize;
    }

    pthread_t* threads = malloc(threadCount * sizeof(pthread_t));
    pthread_mutex_init(&mtx, NULL);

    int chunk = (arraySize + threadCount - 1) / threadCount;

    for (int i = 0; i < threadCount; i++) {
        ThreadData* data = malloc(sizeof(ThreadData));
        data->array = array;
        data->searchValue = searchValue;
        data->start = i * chunk;
        data->end = (data->start + chunk > arraySize) ? arraySize : data->start + chunk;

        if (pthread_create(&threads[i], NULL, searchValueFn, data) != 0) {
            perror("Erro ao criar thread");
            exit(1);
        }
    }

    for (int i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }

    if (!found) {
        printf("Valor %d não encontrado no array.\n", searchValue);
    }

    pthread_mutex_destroy(&mtx);
    free(array);
    free(threads);
    return 0;
}
