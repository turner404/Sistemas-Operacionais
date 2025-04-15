# Laboratório 02

---

## psTree

Informe a profundidade da árvore a ser criada.

**Bibliotecas utilizadas:**
- stdio.h  
- sys/types.h  
- unistd.h  
- sys/wait.h  

**Compilar o código:**
```bash
make tree
```

**Como executar:**
```bash
./main
```

Informe o número de galhos requeridos. Será criada uma sequência de `fork()` com o número de galhos desejado.

---

## CommandChild

Informe um comando, e o processo filho o executará.

**Bibliotecas utilizadas:**
- stdio.h  
- unistd.h  
- sys/types.h  
- string.h  
- sys/wait.h  

**Compilar o código:**
```bash
make command
```

**Como executar:**
```bash
./main <comando> [argumentos...]
```

**Exemplos:**
```bash
./main ls -lha
./main touch teste.txt
```

---

## ArrayDivision

Informe a quantidade de filhos, o tamanho do vetor e o valor a ser buscado.  
O programa retornará a posição no array onde o valor estiver (caso exista).

**Bibliotecas utilizadas:**
- stdio.h  
- unistd.h  
- sys/types.h  
- stdlib.h  

**Compilar o código:**
```bash
make array
```

**Como executar:**
```bash
./main
```

---

## shellBasic

Uma simples interface de shell feita para rodar o comando desejado.  
Pode ser usada como uma shell normal, com suporte a execução em segundo plano (`&`) e uso do operador pipe (`|`).

**Bibliotecas utilizadas:**
- stdio.h  
- unistd.h  
- string.h  
- sys/wait.h  

**Compilar o código:**
```bash
make shell
```

**Como executar:**
```bash
./main
```
```
