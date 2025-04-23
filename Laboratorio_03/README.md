# Laboratório 02

---

## busca_multithread

Programa que cria uma árvore de processos.

**Bibliotecas utilizadas:**

-

**Compilar o código:**

```bash
make
```

**Como executar:**

```bash
make
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
