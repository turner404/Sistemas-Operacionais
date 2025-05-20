CC = gcc -Wall

PROGS = manipulador

all: $(PROGS)

clean:
	rm -f $(PROGS)

manipulador: manipula_arquivo_graceful.c
	$(CC) manipula_arquivo_graceful.c -o manipulador
