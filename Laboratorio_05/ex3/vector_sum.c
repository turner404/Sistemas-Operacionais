/*
 * Nome do arquivo: vector_sum.c
 * Descrição       : Soma elementos de dois vetores em paralelo usando processos.
 * Autor           : Rafael Augusto de Souza
 * Data de criação : 2025-05-19
 * Última atualização: 2025-05-19
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define SHM_NAME_A   "/shm_vector_a"
#define SHM_NAME_B   "/shm_vector_b"
#define SHM_NAME_C   "/shm_vector_c"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <numElementos> <numProcessos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int N = atoi(argv[1]);
    int P = atoi(argv[2]);
    if (N <= 0 || P <= 0 || P > N) {
        fprintf(stderr, "Parâmetros inválidos\n");
        exit(EXIT_FAILURE);
    }

    size_t bytes = N * sizeof(int);
    int shm_fd_a = shm_open(SHM_NAME_A, O_CREAT | O_RDWR, 0666);
    int shm_fd_b = shm_open(SHM_NAME_B, O_CREAT | O_RDWR, 0666);
    int shm_fd_c = shm_open(SHM_NAME_C, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd_a, bytes);
    ftruncate(shm_fd_b, bytes);
    ftruncate(shm_fd_c, bytes);

    int *A = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_a, 0);
    int *B = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_b, 0);
    int *C = mmap(NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_c, 0);

    // Inicializa vetores A e B
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;
        B[i] = N - i;
        C[i] = 0;
    }

    // Cria pipes
    int pipes[P][2];
    for (int i = 0; i < P; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe"); exit(EXIT_FAILURE);
        }
    }

    // Cria filhos
    for (int i = 0; i < P; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Processo filho
            close(pipes[i][1]); // fecha escrita
            int range[2];
            read(pipes[i][0], range, sizeof(range));
            int start = range[0], end = range[1];
            for (int j = start; j < end; j++) {
                C[j] = A[j] + B[j];
            }
            close(pipes[i][0]);
            munmap(A, bytes); munmap(B, bytes); munmap(C, bytes);
            exit(EXIT_SUCCESS);
        }
        // Pai fecha leitura
        close(pipes[i][0]);
    }

    // Pai envia intervalos
    int base = N / P;
    int extra = N % P;
    int offset = 0;
    for (int i = 0; i < P; i++) {
        int count = base + (i < extra ? 1 : 0);
        int range[2] = { offset, offset + count };
        write(pipes[i][1], range, sizeof(range));
        close(pipes[i][1]);
        offset += count;
    }

    // Pai aguarda filhos
    for (int i = 0; i < P; i++) wait(NULL);

    // Exibe resultado
    printf("Resultado: [");
    for (int i = 0; i < N; i++) printf("%d%s", C[i], (i+1 < N) ? " " : "");
    printf("]\n");

    // Limpeza
    munmap(A, bytes); munmap(B, bytes); munmap(C, bytes);
    close(shm_fd_a); close(shm_fd_b); close(shm_fd_c);
    shm_unlink(SHM_NAME_A); shm_unlink(SHM_NAME_B); shm_unlink(SHM_NAME_C);
    return 0;
}