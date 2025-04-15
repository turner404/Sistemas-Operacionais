// Descrição: Programa que cria uma árvore de processos.
// Autor: Rafael Augusto de Souza
// Data: 2025-04-14

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
    printf("Exemplo 1:\n");
    
    int numNiveis = 3;         // Número de níveis de processos
    int duracaoSegundos = 20;  // Tempo de duração do processo (em segundos)
    int numFilhos = 2;         // Número de filhos por processo
    
    // Lê os argumentos passados pela linha de comando
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-n")) {
            sscanf(argv[i + 1], "%d", &numNiveis);
        }
        if (!strcmp(argv[i], "-t")) {
            sscanf(argv[i + 1], "%d", &duracaoSegundos);
        }
        if (!strcmp(argv[i], "-c")) {
            sscanf(argv[i + 1], "%d", &numFilhos);
        }
    }
    
    printf("Número de níveis (-n) = %d\n", numNiveis);
    printf("Duração (em segundos) (-t) = %d\n", duracaoSegundos);
    printf("Número de filhos (-c) = %d\n", numFilhos);
    
    printf("Meu PID = %d\n", getpid());
    printf("PID do meu pai = %d\n", getppid());
    
    int nivelAtual = 1;
    pid_t pid;
    
    for (int i = 0; i < numFilhos; i++) {
        pid = fork();
        if (pid == 0) {  // Processo filho
            nivelAtual++;
            if (nivelAtual < numNiveis) {
                i = -1; // Reinicia o loop para criar filhos no próximo nível
            } else {
                break;  // Último nível, para de criar filhos
            }
        }
    }
    
    sleep(duracaoSegundos);
}
