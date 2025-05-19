// Descrição: Programa servidor para comunicação via socket UNIX, que esperar um envia uma resposta do texto traduzido para o cliente.
// Autor: Augusto Maccagnan Mendes.
// Data: 18-05-2025.
// Observação: O código tem como base o código fornecido pelo professor nos materiais: "Exemplos IPC: pipe, fifo, socket, mqueue, shm"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

// #define DEBUG

#define SIZE 20

typedef struct
{
    char *en;
    char *pt;
} DictionaryEntry;

// Dicionário de palavras
DictionaryEntry dictionary[SIZE] = {
    {"hello", "olá"},
    {"world", "mundo"},
    {"how", "como"},
    {"are", "está"},
    {"you", "você"},
    {"good", "bom"},
    {"morning", "manhã"},
    {"night", "noite"},
    {"friend", "amigo"},
    {"thanks", "obrigado"},
    {"dog", "cachorro"},
    {"cat", "gato"},
    {"car", "carro"},
    {"house", "casa"},
    {"computer", "computador"},
    {"book", "livro"},
    {"phone", "telefone"},
    {"table", "mesa"},
    {"chair", "cadeira"},
    {"water", "água"}};

char *translate(char *buf, int size, int *response_size)
{
    if (size < 7 || buf == NULL)
    {
        *response_size = 15;
        return "ERROR:UNKNOWN";
    }

    char languages[][3] = {"en", "pt"};              // idiomas suportados
    char lang_in[3] = "";                            // idioma de entrada
    char lang_out[3] = "";                           // idioma de saída
    char *input = malloc(sizeof(char) * (size - 7)); // buffer de entrada
    char *response;                                  // buffer de resposta
    int index = -1;                                  // índice da palavra no dicionário

    // input = NULL;

    // Busca idioma de entrada
    strncpy(lang_in, buf, 2);
    // Busca idioma de saída
    strncpy(lang_out, buf + 3, 2);
    // Busca palavra
    strncpy(input, buf + 6, size - 7);
#ifdef DEBUG
    printf("idioma de entrada: %s\n", lang_in);
    printf("input: %s\n", input);
    printf("len: %ld\n", strlen(input));
    printf("size - 7: %d\n", size - 7);
#endif
    if (strcmp(lang_in, languages[0]) == 0)
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (strcmp(input, dictionary[i].en) == 0)
            {
                index = i;
                break;
            }
        }
    }
    if (strcmp(lang_in, languages[1]) == 0)
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (strcmp(input, dictionary[i].pt) == 0)
            {
                index = i;
                break;
            }
        }
    }
    free(input);
#ifdef DEBUG
    printf("index: %d\n", index);
    printf("size: %d\n", size);
#endif
    if (index == -1)
    {
#ifdef DEBUG
        printf("INPUT ERROR:UNKNOWN\n");
#endif
        *response_size = 15;
        return "ERROR:UNKNOWN";
    }

    if (strcmp(lang_out, languages[0]) == 0)
    {
        *response_size = strlen(dictionary[index].en);
        response = malloc(sizeof(char) * (*response_size));
        response = dictionary[index].en;
    }
    else if (strcmp(lang_out, languages[1]) == 0)
    {
        *response_size = strlen(dictionary[index].pt);
        response = malloc(sizeof(char) * (*response_size));
        response = dictionary[index].pt;
    }
    else
    {
#ifdef DEBUG
        printf("OUTPUT ERROR:UNKNOWN\n");
#endif
        *response_size = 15;
        return "ERROR:UNKNOWN";
    }
#ifdef DEBUG
    printf("response: %s\n", response);
#endif
    return response;
}

// char *socket_path = "./mysocket";
char *socket_path = "\0myabstractsocket";

int main(int argc, char *argv[])
{
    int server_socket,       // descritor do socket
        client_socket,       // socket da conexao do cliente
        received_bytes;      // bytes recebidos
    struct sockaddr_un addr; // endereço socket
    char buf[100];           // buffer de comunicação
    char *response;          // buffer de resposta
    int size = 0;            // tamanho da resposta

    if (argc > 1)
        socket_path = argv[1];

    /* cria um socket AF_UNIX do tipo SOCK_STREAM */
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        exit(-1);
    }

    /* configura endereço do socket */
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;

    if (*socket_path == '\0')
    {
        *addr.sun_path = '\0';
        strncpy(addr.sun_path + 1, socket_path + 1, sizeof(addr.sun_path) - 2);
    }
    else
    {
        strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
        unlink(socket_path); // desvincular path se existe
    }

    /* mapeia o socket para o socket_path */
    if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("bind error");
        exit(-1);
    }

    /* configura para aguardar conexões */
    if (listen(server_socket, 5) == -1)
    {
        perror("listen error");
        exit(-1);
    }

    while (1)
    {
        /* aguarda conexões dos clientes */
        if ((client_socket = accept(server_socket, NULL, NULL)) == -1)
        {
            perror("accept error");
            continue;
        }

        /* lê dados envidos pelos clientes */
        while ((received_bytes = read(client_socket, buf, sizeof(buf))) > 0)
        {
#ifdef DEBUG
            printf("received %u bytes\n", received_bytes);
#endif
            response = translate(buf, received_bytes, &size);
#ifdef DEBUG
            printf("response: %s\n", response);
#endif
            if (write(client_socket, response, size) != size)
            {
                if (size > 0)
                    fprintf(stderr, "partial write");
                else
                {
                    perror("write error");
                    exit(-1);
                }
            }
            response = NULL;
        }

        /* trata erros */
        if (received_bytes == -1)
        {
            perror("read");
            exit(-1);
        }
        else if (received_bytes == 0)
        {
            printf("EOF\n");
            close(client_socket);
        }
    }

    return 0;
}