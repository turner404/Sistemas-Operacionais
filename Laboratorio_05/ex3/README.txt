# Soma de Vetores com Processos, Memória Compartilhada e Pipes

## Descrição
Este programa soma dois vetores de comprimento N, dividindo a carga entre P processos filhos. O pai distribui intervalos de índices via pipes e utiliza memória compartilhada para que todos acessem os vetores de entrada e escrevam no vetor de saída.

## Como compilar e executar
```bash
# Compile o programa
make all

# Exemplo de execução com 8 elementos e 3 processos
./vector_sum 8 3

# Valores para testes gerados para cada um dos vatores
Vetor A: [1 2 3 4 5 6 7 8]
Vetor B: [8 7 6 5 4 3 2 1]

# Resultado experado
Resultado: [9 9 9 9 9 9 9 9]