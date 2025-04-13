// Descrição: Programa que cria uma árvore de processos de acordo com a profundidade informada pelo usuário.
// Autor: Rafael Augusto de Souza
// Data: 2025-04-09

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;
void criaArvore(int nivel, int max) {
    if (nivel >= max) 
        return; 

    pid_t pid1 = fork();

    if (pid1 == 0) {
        criaArvore(nivel + 1, max);
        return;
    }
    pid_t pid2 = fork();

    if (pid2 == 0) {
        criaArvore(nivel + 1, max);
        return;
    }
    wait(nullptr);
    wait(nullptr);
}

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    cout << "PID da raiz: " << getpid() << "\n";

    criaArvore(1, N);
    sleep(30);

    return;
}
