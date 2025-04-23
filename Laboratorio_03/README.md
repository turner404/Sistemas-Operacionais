# Laboratório 02

---

# busca_multithread

Programa que utiliza múltiplas *threads* para buscar um valor específico dentro de um vetor de inteiros.  
O vetor é dividido em partes iguais entre as threads, que realizam a busca em paralelo para acelerar o processo.

**Bibliotecas utilizadas:**

- `pthread.h` – para criação e manipulação de threads  
- `stdlib.h` – para alocação dinâmica de memória  
- `stdio.h` – para entrada e saída padrão  
- `time.h` – para geração de números aleatórios com base no tempo  

---

**Compilar o código:**

```bash
make
```
**Como executar:**

```bash
./busca <tamanho_do_vetor> <quantidade_de_threads>
```
Exemplo:

```bash
./busca 1000 4
```
---

## media_aritmetica

Programa que gera uma matriz com números pseudoaleatórios com tamanho padrão 10 x 10
ou tamanho informado por parâmetro, ou le uma matriz de um arquivo e calcula a média aritmética
dos valores de cada linha.

**Bibliotecas utilizadas:**

-   stdio.h
-   stdlib.h
-   time.h
-   pthread.h

**Compilar o código:**

```bash
make aritmetica
```

**Como executar:**

##### **1. Execução informando tamanho:**

```bash
./media_aritmetica.o [linhas] [colunas]
```

##### **2. Execução informando nome do arquivo:**

```bash
./media_aritmetica.o <nome_arquivo>
```

---

## media_geometrica

Programa que gera uma matriz com números pseudoaleatórios com tamanho padrão 10 x 10
ou tamanho informado por parâmetro, ou le uma matriz de um arquivo e calcula a média geométrica
dos valores de cada coluna.

**Bibliotecas utilizadas:**

-   stdio.h
-   string.h
-   pthread.h
-   math.h
-   stdlib.h

**Compilar o código:**

```bash
make geometrica
```

**Como executar:**

##### **1. Execução informando tamanho:**

```bash
./media_geometrica.o [linhas] [colunas]
```

##### **2. Execução informando nome do arquivo:**

```bash
./media_geometrica.o <nome_arquivo>
```
