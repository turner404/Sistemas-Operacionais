CC = gcc -Wall

PROGS = manipulador

all: $(PROGS)

clean:
	rm -f $(PROGS)

manipulador: graceful_file_handler.c
	$(CC) graceful_file_handler.c -o manipulador
