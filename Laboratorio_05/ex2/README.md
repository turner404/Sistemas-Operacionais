# Manipulador de Arquivo com Finalização Limpa (Graceful Stop)

Este projeto em C implementa um programa de terminal interativo que permite ao usuário **ler** e **escrever** em um arquivo de texto. O programa também trata os sinais `SIGINT` (Ctrl+C) e `SIGTERM`, garantindo uma **finalização segura** do processo com o fechamento correto do arquivo aberto.

## Descrição

O programa oferece um menu simples com as seguintes opções:

1. **Ler o conteúdo do arquivo** (`arquivo.txt`)  
2. **Escrever no final do arquivo** (`arquivo.txt`)  
3. **Finalizar o programa normalmente**

Se o processo for interrompido externamente por um sinal (`SIGINT` ou `SIGTERM`), ele realiza uma finalização limpa, fechando o arquivo e saindo de forma segura.

## Funcionalidades

- Manipulação de arquivos (`fopen`, `fclose`, `fgets`, `fprintf`)
- Interação via terminal
- Tratamento de sinais (`signal`)
- Finalização limpa (graceful stop)

## Compilação

Para compilar o código, use o `gcc`:

```bash
gcc -o manipulador graceful_file_handler.c
