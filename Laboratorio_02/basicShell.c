// Descrição: Implementação de um shell básico que executa comandos do sistema operacional.
// Autor: Victórya Carolina Guimarães da Luz
// Data: 2025-04-13


/* Comandos testados
1. SISTEMA
# uname -a - obter a versão do kernel
# lsb_release -a - informação da distribuição Linux
# cat /etc/debian_version - informação da versão do debian
# uptime - tempo de sistema ativo e carga
# hostname - nome da máquina
# last - informações de login e outros
# last reboot - informações de login e outros
# dmesg - informações de detecção de hardware e mensagens de boot
# lscpu - informações de cpu
# lspci - informações de dispositivos pci
# lsusb - informações de dispositivos usb
# lshw - informações de hardware
# watch -n1 'cat /proc/interrupts' - monitoramento das interrupções
> ulimit -a - limites do sistema - Apresentou erro na execução
# sysctl -a - limites do sistema

2. PROCESSOS
# disown -h %1 - desacopla do terminal, não finaliza ao fechar o terminal (ignora a solicitação de finalização)
# nohup COMANDO > myoutput.log & - ignora sinais de HANGUP

ulimit -a apresentou erro "Exec failed: No such file or directory"
*/
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
