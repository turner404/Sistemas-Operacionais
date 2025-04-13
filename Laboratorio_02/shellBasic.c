// Descrição: Implementação de um shell básico que executa comandos do sistema operacional.
// Autor: Victórya Carolina Guimarães da Luz
// Data: 2025-04-13

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main() {
    char command[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("basicShell> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // Ctrl+D
        }

        // Remove a quebra de linha
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Verifica se o comando termina com '&'
        int background = 0;
        if (strchr(command, '&') != NULL) {
            background = 1;

            // Remove o '&' da string do comando
            char *amp = strchr(command, '&');
            *amp = '\0';
        }

        // Divide o comando em argumentos
        int i = 0;
        char *token = strtok(command, " \t");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue; // Comando vazio
        }

        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            continue;
        } else if (pid == 0) {
            // Processo filho
            execvp(args[0], args);
            perror("Exec failed");
            _exit(1);
        } else {
            // Processo pai
            if (!background) {
                waitpid(pid, &status, 0);
            }
        }
    }

    return 0;
}
