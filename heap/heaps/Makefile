#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: heap
	@gcc -o executable main.c heap.o -Wall

#	para compilar as estruturas necessárias
heap:
	@gcc -o heap.o -c heap.c -Wall

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
