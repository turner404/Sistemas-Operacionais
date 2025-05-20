// Descrição: Programa que permite ao usuário ler e escrever em um arquivo texto por meio de um menu interativo.
//            Além disso, trata os sinais SIGINT e SIGTERM para realizar uma finalização limpa,
//            garantindo o fechamento do arquivo e a preservação dos dados.
// Autor: Victórya Carolina Guimarães da Luz
// Data: 18-05-2025.
// Observação: O arquivo é manipulado com abertura em modo leitura ("r") ou anexação ("a").
//             Ao receber SIGINT ou SIGTERM, o programa exibe uma mensagem e encerra de forma segura.


#include <stdio.h>
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

FILE *file;

/* função tratadora de sinais. */
void sig_handler(int signo) {
    if (signo == SIGINT) {
        printf("\n\nRecebi SIGINT\n");
    } else if (signo == SIGTERM) {
        printf("\n\nRecebi SIGTERM\n");
    }
    fclose(file);
    exit(0);
}

/* Função principal */
int main(){
    int op;
    char buffer[1024];

    /* Registra a função tratadora de sinais */
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    /* Manipular o arquivo */
    while (1) {
        printf("PID: %d\n", getpid());
        printf("Escolha uma opção:\n");
        printf("1 - Ler o arquivo\n");
        printf("2 - Escrever no arquivo\n");
        printf("3 - Finalizar\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                file = fopen("arquivo.txt", "r");
                if (file == NULL) {
                    printf("Erro ao abrir o arquivo\n");
                    exit(1);
                }
                printf("\n\nLendo o arquivo\n");
                printf("----- Inicio do arquivo -----\n");
                fseek(file, 0, SEEK_SET);
                while (fgets(buffer, 1024, file) != NULL) {
                    printf("%s", buffer);
                }
                printf("----- Fim do arquivo -----\n\n");
                break;
            case 2:
                file = fopen("arquivo.txt", "a");
                if (file == NULL) {
                    printf("Erro ao abrir o arquivo\n");
                    exit(1);
                }
                printf("\n\nEscrevendo no arquivo\n");
                fseek(file, 0, SEEK_END);
                while ( getchar() != '\n' );
                printf("Digite o texto a ser escrito no arquivo: ");
                fgets(buffer, 1024, stdin);
                fprintf(file, "%s", buffer);
                break;
            case 3:
                printf("\n\nFinalizando\n");
                fclose(file);
                exit(0);
                break;
            default:
                printf("\n\nOpção inválida\n");
                break;
        }
    }
}
