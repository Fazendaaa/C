#   Autor: Lucas de Almeida Carotta

#	nome do arquivo: Makefile

#	para compilar as listas encadeadas junto com o programa de testes
all: ohtbl
	@gcc -o executable main.c ohtbl.o -Wall

#	para compilar apenas a tabela hashing de endereçamento livre
ohtbl:
	@gcc -o ohtbl.o -c ohtbl.c -Wall

#	para rodar o programa de testes
run:
	@./executable

#	para limpar o diretório do arquivo que contém as estruturas
clean:
	@rm -r *.o

.PHONY:
	clean
