# Troca de strings entre processos com fifo

## Descrição
Este programa é dividido em dois processos: o escritor e o leitor. O escritor requer ininterruptamente entradas de texto do usuário. As entradas serão repassadas para o leitor via fifo. O leitor informa o texto obtido, seu tamanho e os números de consoantes, vogais e espaços.

## Como compilar
```bash
# Compile o programa
make all