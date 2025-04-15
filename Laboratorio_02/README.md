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
make tree
```

**Como executar:**
```bash
./main <profundidade>
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
make command
```

**Como executar:**
```bash
./main <comando> [argumentos...]
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
make array
```

**Como executar:**
```bash
./main
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
make shell
```

**Como executar:**
```bash
./main
```
