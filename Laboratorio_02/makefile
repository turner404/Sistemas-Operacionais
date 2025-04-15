# Recompilação e execução de todos os programas
all: clean run

# Executa todos os programas
run: tree command array shell

# Compilação e execução de psTree
tree: tree_clean tree_comp
	@echo "Executando psTree"
	./tree.o

# Compilação de psTree
tree_comp:
	gcc psTree.c -o tree.o

# Limpa programa compilado de psTree
tree_clean: 
	rm -f tree.o

# Compilação e execução de commandChild
command: command_clean command_comp
	@echo "Executando commandChild"
	./commandChild.o ping 8.8.8.8 -c 3

# Compilação de commandChild
command_comp:
	@gcc commandChild.c -o commandChild.o

# Limpa programa compilado de commandChild
command_clean:
	@rm -f commandChild.o

# Compilação e execução de arrayDivision
array: array_clean array_comp
	@echo "Executando arrayDivision"
	./arrayDivision.o

# Compilação de arrayDivision
array_comp:
	gcc arrayDivision.c -o arrayDivision.o

# Limpa programa compilado de arrayDivision
array_clean:
	@rm -f arrayDivision.o

# Compilação e execução de basicShell
shell: shell_clean shell_comp
	@echo "Executando basicShell"
	./basicShell.o

# Compilação de basicShell
shell_comp:
	gcc basicShell.c -o basicShell.o

# Limpa programa compilado de basicShell
shell_clean:
	@rm -f basicShell.o

# Limpa todos os programas compilados
clean: tree_clean array_clean command_clean shell_clean
	@echo "Limpando todos os arquivos"

