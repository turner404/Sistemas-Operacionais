CC=gcc -Wall

PROGS=client server ex1leitor ex1escritor

all: $(PROGS)

clean:
	rm -f $(PROGS)

client:	client.c
	$(CC) client.c -o client

server:	server.c
	$(CC) server.c -o server

ex1leitor:	ex1leitor.c
	$(CC) ex1leitor.c -o ex1leitor

ex1escritor:	ex1escritor.c
	$(CC) ex1escritor.c -o ex1escritor
