# Laboratório 05 - Exercício 4

---

# Comunicação entre processos via sockets UNIX

## client

Programa que permite uma entrada pelo terminal e envia através de socket o texto para processamento do servidor.
Caso receba uma resposta mostra a resposta fornecida pelo servidor.

**Bibliotecas utilizadas:**

- `stdlib.h` – para alocação dinâmica de memória
- `stdio.h` – para entrada e saída padrão
- `sys/un.h` – para endereçamento dos sockets UNIX
- `sys/socket.h` – para criação do socket
- `unistd.h` – definição de constantes e tipos padrões

---

**Compilar o código:**

```bash
make
```

**Como executar:**

1. Executar o servidor para aceitar conxões socket

```bash
./server
```

2. Em outro terminal executar o cliente que se conectará ao servidor

```bash
./client
```

**Exemplo de uso:**

- No terminal do cliente

```bash
>pt-en:cachorro
```

- É esperado o retorno da tradução da palavra informada para o idioma alvo, neste caso:

```bash
>pt-en:cachorro
<dog
```
