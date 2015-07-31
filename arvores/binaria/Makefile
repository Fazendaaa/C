#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: bitree
	@gcc -o executable main.c bitree.o -Wall

#	para compilar apenas a árvore binária
bitree:
	@gcc -o bitree.o -c bitree.c -Wall

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
