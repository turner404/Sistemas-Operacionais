```markdown
# 🧠 Atividades de Sistemas Operacionais

Repositório contendo os códigos da **Atividade 2** da disciplina de Sistemas Operacionais.

---

## 🌳 Tree

Cria uma árvore de processos com profundidade definida pelo usuário.

### 📚 Bibliotecas utilizadas
- `stdio.h`
- `sys/types.h`
- `unistd.h`
- `sys/wait.h`

### 🛠 Como compilar
```bash
make tree
```

### ▶️ Como executar
```bash
./main
```
Você será solicitado a informar:
- A profundidade da árvore
- O número de galhos desejados

O programa utilizará `fork()` para criar os processos.

---

## 💻 CommandChild

Executa um comando passado via terminal em um processo filho.

### 📚 Bibliotecas utilizadas
- `stdio.h`
- `unistd.h`
- `sys/types.h`
- `string.h`
- `sys/wait.h`

### 🛠 Como compilar
```bash
make command
```

### ▶️ Como executar
```bash
./main <comando> [argumentos...]
```

### 📌 Exemplos
```bash
./main ls -lha
./main touch teste.txt
```

---

## 📊 ArrayDivision

Divide a busca de um valor em um array entre processos filhos. Retorna a posição caso o valor seja encontrado.

### 📚 Bibliotecas utilizadas
- `stdio.h`
- `unistd.h`
- `sys/types.h`
- `stdlib.h`

### 🛠 Como compilar
```bash
make array
```

### ▶️ Como executar
```bash
./main
```
O programa solicitará:
- A quantidade de filhos
- O tamanho do vetor
- O valor a ser buscado

---

## 🐚 Simple Shell

Uma shell simples para execução de comandos, incluindo:
- Execução em segundo plano (`&`)
- Uso de pipe (`|`)

### 📚 Bibliotecas utilizadas
- `stdio.h`
- `unistd.h`
- `string.h`
- `sys/wait.h`

### 🛠 Como compilar
```bash
make shell
```

### ▶️ Como executar
```bash
./main
```

---
