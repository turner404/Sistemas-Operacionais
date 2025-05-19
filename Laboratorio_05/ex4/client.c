// Descrição: Programa cliente para comunicação via socket UNIX, que envia texto e recebe uma resposta em texto do servidor.
// Autor: Augusto Maccagnan Mendes.
// Data: 18-05-2025.
// Observação: O código tem como base o código fornecido pelo professor nos materiais: "Exemplos IPC: pipe, fifo, socket, mqueue, shm"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/* especificar o path para mapear o socket */
// char *socket_path = "./mysocket";
char *socket_path = "\0myabstractsocket";

int main(int argc, char *argv[])
{
    int client_socket,       // descritor para o socket (file descriptor)
        sent_bytes,          // número de bytes enviados
        received_bytes;      // número de bytes recebidos
    struct sockaddr_un addr; // estrutura de endereço socket unix
    char buf[100];           // buffer para troca de mensagens

    /* socket_path por parâmetro */
    if (argc > 1)
        socket_path = argv[1];

    /* cria socket UNIX do tipo SOCK_STREAM */
    if ((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        exit(-1);
    }

    /* preenche estrutura de endereço */
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    if (*socket_path == '\0')
    { // socket não mapeado no sistema de arquivos (abstract)
        *addr.sun_path = '\0';
        strncpy(addr.sun_path + 1, socket_path + 1, sizeof(addr.sun_path) - 2);
    }
    else
    {
        strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
    }

    /* conecta com o processo servidor */
    if (connect(client_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("connect error");
        exit(-1);
    }
    /* lê dados do terminal e envia via sockets */
    // while ((sent_bytes = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
    // {
    while (1)
    {
        printf(">");
        fflush(stdout);

        if ((sent_bytes = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
        {
            if (write(client_socket, buf, sent_bytes) != sent_bytes)
            {
                if (sent_bytes > 0)
                    fprintf(stderr, "partial write");
                else
                {
                    perror("write error");
                    exit(-1);
                }
            }
            /* lê dados envidos pelos clientes */
            if ((received_bytes = read(client_socket, buf, sizeof(buf))) > 0)
            {
#ifdef DEBUG
                printf("read %u bytes\n", received_bytes);
#endif
                printf("<%.*s\n", received_bytes, buf);
            }
        }
    }

    return 0;
}
