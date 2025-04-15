# Laboratório 02

---

## psTree

Programa que cria uma árvore de processos.

**Bibliotecas utilizadas:**
- stdio.h
- stdlib.h 
- sys/types.h  
- unistd.h
- string.h

**Compilar o código:**
```bash
make tree_comp
```

**Como executar:**
##### **1. Execução com profundidade 3, com 2 filhos por processo, aguardando 20 segundos ao final:**
```bash
make tree
```
##### **2. Execução informando parâmetros:**
```bash
./tree.o -n [profundidade] -t [segundos] -c [filhos]
```
###### É possível visualizar a hierarquia de processos utilizando:
```bash
pstree <pid_pai>
```
---

## CommandChild

Programa que executa um comando, passado como argumento, em um processo filho e aguarda sua finalização.

**Bibliotecas utilizadas:**
- stdio.h
- stdlib.h
- unistd.h  
- sys/types.h  
- sys/wait.h  

**Compilar o código:**
```bash
make command_comp
```

**Como executar:**
##### **1. Execução com comando ping:**
```bash
make command
```
##### **2. Execução informando comando:**
```bash
./commandChild.o <comando> [argumentos...]
```

---

## ArrayDivision

Programa que calcula a quantidade de ocorrências de um elemento em uma lista por meio de vários processos, imprimindo a posição de cada uma.

**Bibliotecas utilizadas:**
- stdio.h
- stdlib.h
- unistd.h  
- sys/types.h
- string.h  
- sys/wait.h

**Compilar o código:**
```bash
make array_comp
```

**Como executar:**
```bash
make array
```

---

## basicShell

Uma simples interface de shell feita para rodar o comando desejado.  
Pode ser usada como uma shell normal, com suporte a execução em segundo plano (`&`) e uso do operador pipe (`|`).

**Bibliotecas utilizadas:**
- stdio.h  
- unistd.h  
- string.h  
- sys/wait.h
- stdlib.h

**Compilar o código:**
```bash
make shell_comp
```

**Como executar:**
```bash
make shell
```
